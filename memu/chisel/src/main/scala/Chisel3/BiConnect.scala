// SPDX-License-Identifier: Apache-2.0

package chisel3.internal

import chisel3._
import chisel3.experimental.dataview.{isView, reify, reifyIdentityView}
import chisel3.experimental.{attach, Analog, BaseModule, SourceInfo}
import chisel3.properties.Property
import chisel3.internal.binding._
import chisel3.internal.Builder.pushCommand
import chisel3.internal.firrtl.ir.{Connect, DefInvalid}
import chisel3.internal.firrtl.Converter
import chisel3.internal.MonoConnect.reportIfReadOnly
import scala.annotation.nowarn

import _root_.firrtl.passes.CheckTypes

/**
  * BiConnectSmart.connect executes a bidirectional connection element-wise.
  *
  * Note that the arguments are left and right (not source and sink) so the
  * intent is for the operation to be commutative.
  *
  * The connect operation will recurse down the left Data (with the right Data).
  * An exception will be thrown if a movement through the left cannot be matched
  * in the right (or if the right side has extra fields).
  *
  * See elemConnect for details on how the root connections are issued.
  */

object BiConnectSmart {

  object DebugConfig {
    // var enableConnectPrint: Boolean = true
    var enableConnectPrint: Boolean = false
  }

  sealed trait ConnectMode
  case object WireMode extends ConnectMode
  case object RegMode  extends ConnectMode

  // These are all the possible exceptions that can be thrown.
  // These are from element-level connection
  def BothDriversException =
    BiConnectException(": Both Left and Right are drivers")
  def NeitherDriverException =
    BiConnectException(": Neither Left nor Right is a driver")
  def UnknownDriverException =
    BiConnectException(": Locally unclear whether Left or Right (both internal)")
  def UnknownRelationException =
    BiConnectException(": Left or Right unavailable to current module.")
  // These are when recursing down aggregate types
  def MismatchedVecException =
    BiConnectException(": Left and Right are different length Vecs.")
  def MissingLeftFieldException(field: String) =
    BiConnectException(s".$field: Left Record missing field ($field).")
  def MissingRightFieldException(field: String) =
    BiConnectException(s": Right Record missing field ($field).")
  def MismatchedException(left: String, right: String) =
    BiConnectException(s": Left ($left) and Right ($right) have different types.")
  def AttachAlreadyBulkConnectedException(
    analog:         String,
    prevConnection: String,
    newConnection:  String,
    sourceInfo:     SourceInfo
  ) = BiConnectException(
      sourceInfo.makeMessage(
        s": Analog $analog previously bulk to $prevConnection is connected to $newConnection at " + _
      )
    )
  def DontCareCantBeSink =
    BiConnectException(": DontCare cannot be a connection sink (LHS)")
  def LeftProbeBiConnectionException(left: Data) =
    BiConnectException(s"Left of Probed type cannot participate in a bi connection (<>)")
  def RightProbeBiConnectionException(right: Data) =
    BiConnectException(s"Right of Probed type cannot participate in a bi connection (<>)")

  private def collectNotReadOnly[T <: Data](x: Option[(T, ViewWriteability)]): Option[T] = {
    x.collect { case (z, ViewWriteability.Default) => z }
  }

  /** This function is what recursively tries to connect a left and right together
    *
    * There is some cleverness in the use of internal try-catch to catch exceptions
    * during the recursive descent and then rethrow them with extra information added.
    * This gives the user a 'path' to where in the connections things went wrong.
    *
    * == Chisel Semantics and how they emit to firrtl ==
    *
    * 1. FIRRTL Connect (all fields as seen by firrtl must match exactly)
    *   `a <= b`
    * 2. FIRRTL Connect (implemented as being field-blasted because we know all firrtl fields would not match exactly)
    *   `a.foo <= b.foo, b.bar <= a.bar`
    *
    * - The decision on 1 vs 2 is based on structural type -- if same type once emitted to firrtl, emit 1, otherwise emit 2
    */
  def connect(
    left: Data,
    right: Data,
    mode: ConnectMode,
    context_mod: RawModule = Builder.referenceUserModule
  )(implicit sourceInfo: SourceInfo): Unit = {
    (left, right) match {
      // Disallow monoconnecting Probe types
      case (left_e: Data, _) if containsProbe(left_e) =>
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(left_e: Data, _)")
        }
        throw LeftProbeBiConnectionException(left_e)
      case (_, right_e: Data) if containsProbe(right_e) =>
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(_, right_e: Data)")
        }
        throw RightProbeBiConnectionException(right_e)

      // Handle element case (root case)
      case (left_a: Analog, right_a: Analog) =>
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(left_a: Analog, right_a: Analog)")
        }
        try {
          markAnalogConnected(sourceInfo, left_a, right_a, context_mod)
          markAnalogConnected(sourceInfo, right_a, left_a, context_mod)
        } catch { // convert attach exceptions to BiConnectExceptions
          case attach.AttachException(message) => throw BiConnectException(message)
        }
        attach.impl(Seq(left_a, right_a), context_mod)(sourceInfo)
      case (left_a: Analog, DontCare) =>
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(left_a: Analog, DontCare)")
        }
        try {
          markAnalogConnected(sourceInfo, left_a, DontCare, context_mod)
        } catch { // convert attach exceptions to BiConnectExceptions
          case attach.AttachException(message) => throw BiConnectException(message)
        }
        pushCommand(DefInvalid(sourceInfo, left_a.lref(sourceInfo)))
      case (DontCare, right_a: Analog) =>
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(DontCare, right_a: Analog)")
        }
        connect(right, left, mode, context_mod)
      case (left_e: Element, right_e: Element) => {
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(left_e: Element, right_e: Element)")
        }
        elemConnect(sourceInfo, left_e, right_e, mode, context_mod)
        // TODO(twigg): Verify the element-level classes are connectable
      }
      // Handle Vec case
      case (left_v: Vec[Data @unchecked], right_v: Vec[Data @unchecked]) => {
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(left_v: Vec[Data @unchecked], right_v: Vec[Data @unchecked])")
        }
        if (left_v.length != right_v.length) throw MismatchedVecException

        // Filter out read-only because we don't know if it's actually an error until we inspect the elements.
        val leftReified: Option[Vec[Data @unchecked]] =
          if (isView(left_v)) collectNotReadOnly(reifyIdentityView(left_v)) else Some(left_v)
        val rightReified: Option[Vec[Data @unchecked]] =
          if (isView(right_v)) collectNotReadOnly(reifyIdentityView(right_v)) else Some(right_v)

        for (idx <- 0 until left_v.length) {
          try {
            connect(left_v(idx), right_v(idx), mode, context_mod)
          } catch {
            case BiConnectException(message) => throw BiConnectException(s"($idx)$message")
          }
        }
      }
      // Handle Vec connected to DontCare
      case (left_v: Vec[Data @unchecked], DontCare) => {
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(left_v: Vec[Data @unchecked], DontCare)")
        }
        for (idx <- 0 until left_v.length) {
          try {
            connect(left_v(idx), right, mode, context_mod)
          } catch {
            case BiConnectException(message) => throw BiConnectException(s"($idx)$message")
          }
        }
      }
      // Handle DontCare connected to Vec
      case (DontCare, right_v: Vec[Data @unchecked]) => {
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(DontCare, right_v: Vec[Data @unchecked])")
        }
        for (idx <- 0 until right_v.length) {
          try {
            connect(left, right_v(idx), mode, context_mod)
          } catch {
            case BiConnectException(message) => throw BiConnectException(s"($idx)$message")
          }
        }
      }
      // Handle Records defined in Chisel._ code by emitting a FIRRTL bulk
      // connect when possible and a partial connect otherwise
      case pair @ (left_r: Record, right_r: Record) =>
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(left_r: Record, right_r: Record)")
        }
        // chisel3 <> is commutative but FIRRTL <- is not
        val flipConnection =
          !MonoConnect.canBeSink(left_r, context_mod) || !MonoConnect.canBeSource(right_r, context_mod)
        val (newLeft, newRight) = if (flipConnection) (right_r, left_r) else (left_r, right_r)

        // Filter out read-only because we don't know if it's actually an error until we inspect the elements.
        val leftReified: Option[Record] =
          if (isView(newLeft)) collectNotReadOnly(reifyIdentityView(newLeft)) else Some(newLeft)
        val rightReified: Option[Record] =
          if (isView(newRight)) collectNotReadOnly(reifyIdentityView(newRight)) else Some(newRight)

        recordConnect(sourceInfo, left_r, right_r, mode, context_mod)

      // Handle Records connected to DontCare
      case (left_r: Record, DontCare) =>
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(left_r: Record, DontCare)")
        }
        // For each field in left, descend with right
        for ((field, left_sub) <- left_r._elements) {
          try {
            connect(left_sub, right, mode, context_mod)
          } catch {
            case BiConnectException(message) => throw BiConnectException(s".$field$message")
          }
        }
      case (DontCare, right_r: Record) =>
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(DontCare, right_r: Record)")
        }
        // For each field in left, descend with right
        for ((field, right_sub) <- right_r._elements) {
          try {
            connect(left, right_sub, mode, context_mod)
          } catch {
            case BiConnectException(message) => throw BiConnectException(s".$field$message")
          }
        }

      // Left and right are different subtypes of Data so fail
      case (left, right) =>
        if (DebugConfig.enableConnectPrint) {
          println(left, right)
          println("(left, right)")
        }
        throw MismatchedException(left.toString, right.toString)
    }
  }

  // Do connection of two Records
  def recordConnect(
    sourceInfo:  SourceInfo,
    left_r:      Record,
    right_r:     Record,
    mode:        ConnectMode,
    context_mod: RawModule
  ): Unit = {
    // Verify right has no extra fields that left doesn't have

    // For each field in left, descend with right.
    // Don't bother doing this check if we don't expect it to necessarily pass.
    for ((field, right_sub) <- right_r._elements) {
      if (!left_r._elements.isDefinedAt(field)) throw MissingLeftFieldException(field)
    }
    // For each field in left, descend with right
    for ((field, left_sub) <- left_r._elements) {
      try {
        right_r._elements.get(field) match {
          case Some(right_sub) => connect(left_sub, right_sub, mode, context_mod)
          case None            => throw MissingRightFieldException(field)
        }
      } catch {
        case BiConnectException(message) => throw BiConnectException(s".$field$message")
      }
    }
  }

  // This function checks if element-level connection operation allowed.
  // Then it either issues it or throws the appropriate exception.
  def elemConnect(
    implicit sourceInfo: SourceInfo,
    _left: Element,
    _right: Element,
    mode: ConnectMode,
    context_mod: RawModule
  ): Unit = {
    import BindingDirection.{Input, Internal, Output} // Using extensively so import these

    val (left, lwr) = reify(_left)
    val (right, rwr) = reify(_right)
    // If left or right have no location, assume in context module
    // This can occur if one of them is a literal, unbound will error previously
    val left_mod:  BaseModule = left.topBinding.location.getOrElse(context_mod)
    val right_mod: BaseModule = right.topBinding.location.getOrElse(context_mod)
    val left_parent_opt = Builder.retrieveParent(left_mod, context_mod)
    val right_parent_opt = Builder.retrieveParent(right_mod, context_mod)
    val context_mod_opt = Some(context_mod)
    val left_direction = BindingDirection.from(left.topBinding, left.direction)
    val right_direction = BindingDirection.from(right.topBinding, right.direction)

    val m = mode match {
      case WireMode => WireMode
      case RegMode  => RegMode
      case _ => throw new IllegalArgumentException(s"Unknown mode: $mode")
    }

    // CASE: Context is same module as left node and right node is in a child module
    if ((left_mod == context_mod) && (right_parent_opt == context_mod_opt)) {
      // Thus, right node better be a port node and thus have a direction hint
      ((left_direction, right_direction): @unchecked) match {
        //    CURRENT MOD   CHILD MOD
        case (Input, Input)     => doConnect(_right, _left, mode)
        case (Internal, Input)  => doConnect(_right, _left, mode)
        case (Output, Output)   => doConnect(_left, _right, mode)
        case (Internal, Output) => doConnect(_left, _right, mode)

        case (Input, Output) => throw BothDriversException
        case (Output, Input) => throw NeitherDriverException
        case (_, Internal)   => throw UnknownRelationException
      }
    }

    // CASE: Context is same module as right node and left node is in child module
    else if ((right_mod == context_mod) && (left_parent_opt == context_mod_opt)) {
      // Thus, left node better be a port node and thus have a direction hint
      ((left_direction, right_direction): @unchecked) match {
        //    CHILD MOD     CURRENT MOD
        case (Input, Input)     => doConnect(_left, _right, mode)
        case (Input, Internal)  => doConnect(_left, _right, mode)
        case (Output, Output)   => doConnect(_right, _left, mode)
        case (Output, Internal) => doConnect(_right, _left, mode)

        case (Input, Output) => throw NeitherDriverException
        case (Output, Input) => throw BothDriversException
        case (Internal, _)   => throw UnknownRelationException
      }
    }

    // CASE: Context is same module that both left node and right node are in
    else if ((context_mod == left_mod) && (context_mod == right_mod)) {
      ((left_direction, right_direction): @unchecked) match {
        //    CURRENT MOD   CURRENT MOD
        case (Input, Output)    => doConnect(_right, _left, mode)
        case (Input, Internal)  => doConnect(_right, _left, mode)
        case (Internal, Output) => doConnect(_right, _left, mode)
        case (Output, Input)    => doConnect(_left, _right, mode)
        case (Output, Internal) => doConnect(_left, _right, mode)
        case (Internal, Input)  => doConnect(_left, _right, mode)

        case (Input, Input)       => throw BothDriversException
        case (Output, Output)     => throw BothDriversException
        case (Internal, Internal) => throw UnknownDriverException
      }
    }

    // CASE: Context is the parent module of both the module containing left node
    //                                        and the module containing right node
    //   Note: This includes case when left and right in same module but in parent
    else if ((left_parent_opt == context_mod_opt) && (right_parent_opt == context_mod_opt)) {
      // Thus both nodes must be ports and have a direction hint
      ((left_direction, right_direction): @unchecked) match {
        //    CHILD MOD     CHILD MOD
        case (Input, Output) => doConnect(_left, _right, mode)
        case (Output, Input) => doConnect(_right, _left, mode)

        case (Input, Input)   => throw NeitherDriverException
        case (Output, Output) => throw BothDriversException
        case (_, Internal)    => throw UnknownRelationException
        case (Internal, _)    => throw UnknownRelationException
      }
    }

    // Not quite sure where left and right are compared to current module
    // so just error out
    else throw UnknownRelationException
  }

  // This function checks if analog element-level attaching is allowed, then marks the Analog as connected
  def markAnalogConnected(sourceInfo: SourceInfo, analog: Analog, otherAnalog: Data, contextModule: RawModule): Unit = {
    analog.biConnectLocs.get(contextModule) match {
      case Some((si, data)) if data != otherAnalog =>
        throw AttachAlreadyBulkConnectedException(analog.toString, data.toString, otherAnalog.toString, si)
      case _ => // Do nothing
    }
    // Mark bulk connected
    analog.biConnectLocs(contextModule) = (sourceInfo, otherAnalog)
  }

  def doConnect(lhs: Element, rhs: Element, mode: ConnectMode): Unit = {
    mode match {
      case WireMode =>
        lhs := rhs
      case RegMode =>
        val reg = RegNext(rhs)
        lhs := reg
    }
  }
}
