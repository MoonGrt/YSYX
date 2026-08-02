package soc.riscv

import chisel3._
import chisel3.util._
import soc.perip.mem._

object Parameters {
  object SoCDevices {
    private def address(name: String, default: String): BigInt =
      BigInt(sys.env.get(name).filter(_.nonEmpty).getOrElse(default).stripPrefix("0x"), 16)

    val sramBase  = address("MEMU_SOC_SRAM_BASE",  "0f000000")
    val sramSize  = address("MEMU_SOC_SRAM_SIZE",  "2000")
    val mromBase  = address("MEMU_SOC_MROM_BASE",  "20000000")
    val mromSize  = address("MEMU_SOC_MROM_SIZE",  "1000")
    val uartBase  = address("MEMU_SOC_UART_BASE",  "10000000")
    val uartSize  = address("MEMU_SOC_UART_SIZE",  "1000")
    val spiBase   = address("MEMU_SOC_SPI_BASE",   "10001000")
    val spiSize   = address("MEMU_SOC_SPI_SIZE",   "1000")
    val gpioBase  = address("MEMU_SOC_GPIO_BASE",  "10002000")
    val gpioSize  = address("MEMU_SOC_GPIO_SIZE",  "10")
    val ps2Base   = address("MEMU_SOC_PS2_BASE",   "10011000")
    val ps2Size   = address("MEMU_SOC_PS2_SIZE",   "8")
    val vgaBase   = address("MEMU_SOC_VGA_BASE",   "21000000")
    val vgaSize   = address("MEMU_SOC_VGA_SIZE",   "200000")
    val flashBase = address("MEMU_SOC_FLASH_BASE", "30000000")
    val flashSize = address("MEMU_SOC_FLASH_SIZE", "1000000")
    val psramBase = address("MEMU_SOC_PSRAM_BASE", "80000000")
    val psramSize = address("MEMU_SOC_PSRAM_SIZE", "400000")
    val sdramBase = address("MEMU_SOC_SDRAM_BASE", "a0000000")
    val sdramSize = address("MEMU_SOC_SDRAM_SIZE", "2000000")
  }
  object AxiPackage extends Enumeration {
    val Custom, RocketChip = Value
  }
  object BootSource extends Enumeration {
    val MROM, Flash = Value
  }
  // MiniRV Parameters
  object MiniRV {
    // Basic
    val DataWidth = 32
    val GPRNum    = 16
    val CSRNum    = 8
    val CSRWidth  = 12
  }
  // Riscv32E Parameters
  object Riscv32E {
    // Basic
    val DataWidth = 32
    val GPRNum    = 16
    val CSRNum    = 8
    val CSRWidth  = 12
    // Mem
    val memBusType  = BusType.AXI
    // Custom: standalone MEMU/NPC top; RocketChip: diplomacy-based SoC.
    val axiPackage  = AxiPackage.RocketChip
    // rtl.mk derives this environment variable from menuconfig so that the
    // RTL reset vector and the simulator memory map always change together.
    val bootSource = sys.env.get("MEMU_SOC_BOOT") match {
      case Some("mrom")  => BootSource.MROM
      case Some("flash") | None => BootSource.Flash
      case Some(value) =>
        throw new IllegalArgumentException(s"unknown MEMU_SOC_BOOT=$value")
    }
    val bootAddress = bootSource match {
      case BootSource.MROM  => SoCDevices.mromBase
      case BootSource.Flash => SoCDevices.flashBase
    }
    val memUseDpi   = true
    val memDelayCfg = MemDelayConfig(
      enable = false,
      delayWidth = 8,
      delaySeed = 2,
      delayTaps = 0x9
    )
  }
}

object Constants {
  // MiniRV Constants
  object MiniRV {
    object OP2 extends ChiselEnum {
      val NONE, RS2, IMI, IMS, IMU = Value
    }
    object EX extends ChiselEnum {
      val NONE, ADD, JAL = Value
    }
    object GPR extends ChiselEnum {
      val NONE, PC, EX, MEM = Value
    }
    object MEM extends ChiselEnum {
      val NONE, RW, RBU, WW, WB = Value
    }
  }
  // Riscv32E Constants
  object Riscv32E {
    object OP1 extends ChiselEnum {
      val NONE, RS1, PC, IMZ = Value
    }
    object OP2 extends ChiselEnum {
      val NONE, RS2, CSR, IMI, IMS, IMJ, IMU = Value
    }
    object EX extends ChiselEnum {
      val NONE, ADD, SUB, AND, OR, XOR, SLL, SRL, SRA, SLT, SLTU, 
          BEQ, BNE, BLT, BGE, BLTU, BGEU, JAL, CSR = Value
    }
    object GPR extends ChiselEnum {
      val NONE, PC, EX, LS, CSR = Value
    }
    object LS extends ChiselEnum {
      val NONE, RW, RH, RB, RHU, RBU, WW, WH, WB = Value
    }
    object CSR extends ChiselEnum {
      val NONE, W, S, C, B, E, MRET = Value
    }
  }
}
