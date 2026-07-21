FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive
ARG VERILATOR_VERSION=7e7b6d7fb83defa29415fda2012f2f336fe534fa
ARG MILL_VERSION=0.12.17

ENV LANG=C.UTF-8 \
    LC_ALL=C.UTF-8 \
    MILL_VERSION=${MILL_VERSION} \
    MEMU_HOME=/workspace/YSYX/memu \
    AM_HOME=/workspace/YSYX/abstract-machine \
    AM_TEST_HOME=/workspace/YSYX/am-kernels \
    NVBOARD_HOME=/workspace/YSYX/nvboard \
    NPC_HOME=/workspace/YSYX/npc

# Install build, simulation, and RISC-V cross-compilation dependencies.
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        vim ca-certificates curl git gnupg make g++ flex scons \
        openjdk-17-jdk gtkwave autoconf bison help2man \
        python3 python3-pip python-is-python3 \
        g++-riscv64-linux-gnu binutils-riscv64-linux-gnu \
        device-tree-compiler libncurses-dev libsdl2-dev libreadline-dev \
        libfl-dev libtool libyaml-dev libudev-dev libusb-1.0-0-dev \
    && rm -rf /var/lib/apt/lists/*

# Install SBT from its Debian repository. The public key is
# retrieved from Ubuntu's keyserver and stored in a dedicated keyring.
RUN curl -fsSL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x2EE0EA64E40A89B84B2DF73499E82A75642AC823" \
        | gpg --dearmor -o /usr/share/keyrings/sbt-archive-keyring.gpg \
    && echo "deb [signed-by=/usr/share/keyrings/sbt-archive-keyring.gpg] https://repo.scala-sbt.org/scalasbt/debian all main" \
        > /etc/apt/sources.list.d/sbt.list \
    && apt-get update \
    && apt-get install -y --no-install-recommends sbt \
    && rm -rf /var/lib/apt/lists/*

# Build the pinned Verilator revision, then remove its source tree to keep the
# final image focused on the installed tools.
RUN git clone https://github.com/verilator/verilator.git /tmp/verilator \
    && cd /tmp/verilator \
    && git checkout --detach "${VERILATOR_VERSION}" \
    && autoconf \
    && ./configure \
    && make -j"$(nproc)" \
    && make install \
    && rm -rf /tmp/verilator

# Install Mill's versioned launcher and prefetch the pinned distribution.
RUN curl --fail --location \
        "https://raw.githubusercontent.com/com-lihaoyi/mill/${MILL_VERSION}/mill" \
        --output /usr/local/bin/mill \
    && chmod +x /usr/local/bin/mill \
    && mill --version

# Permit RV32 builds with Ubuntu 22.04's riscv64 cross libc. Its header layout
# differs from the older toolchain patch: define the word size instead of
# rejecting the ABI, then use the correct RV32 time ABI value.
RUN sed -i 's|^# error unsupported ABI$|# define __WORDSIZE __riscv_xlen|' \
        /usr/riscv64-linux-gnu/include/bits/wordsize.h \
    && sed -i 's|^#define __WORDSIZE_TIME64_COMPAT32  1$|#if __WORDSIZE == 32\n# define __WORDSIZE_TIME64_COMPAT32 0\n#else\n# define __WORDSIZE_TIME64_COMPAT32 1\n#endif|' \
        /usr/riscv64-linux-gnu/include/bits/wordsize.h \
    && sed -i 's|^# include <gnu/stubs-ilp32.h>$|//# include <gnu/stubs-ilp32.h>|' \
        /usr/riscv64-linux-gnu/include/gnu/stubs.h

# Configure Git for the WSL bind-mounted workspace and the container user.
RUN git config --global core.autocrlf input \
    && git config --global --add safe.directory '*' \
    && git config --global user.name "MoonGrt" \
    && git config --global user.email "1561145394@qq.com"

WORKDIR /workspace/YSYX

CMD ["bash"]
