# Firmware build environment matching CI (build-firmware.yaml)
# ARM GNU Toolchain 14.2.Rel1 (official ARM release, same as CI)
# Base: ubuntu:24.04 (ubuntu-latest at time of writing)
#
# Build the image:
#   docker build -t rusefi-build misc/docker/
#
# Build a board (mount repo root, pass meta-info path):
#   docker run --rm -v "$(pwd):/rusefi" rusefi-build config/boards/proteus/meta-info-proteus_f4.env
#
# Outputs land in firmware/deliver/ and artifacts/ as usual.

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Install tools matching misc/actions/ubuntu-install-tools.sh
RUN apt-get update && apt-get install -y \
    make \
    gcc-multilib \
    g++-multilib \
    g++-mingw-w64 \
    gcc-mingw-w64 \
    sshpass \
    mtools \
    zip \
    dosfstools \
    colordiff \
    wget \
    xz-utils \
    git \
    xxd \
    python3 \
    bc \
    curl \
    gnupg \
    && rm -rf /var/lib/apt/lists/*

# Install Zulu JDK 17 (matches CI actions/setup-java distribution: 'zulu', java-version: '17')
RUN curl -fsSL https://repos.azul.com/azul-repo.key | gpg --dearmor -o /usr/share/keyrings/azul.gpg \
    && echo "deb [signed-by=/usr/share/keyrings/azul.gpg] https://repos.azul.com/zulu/deb stable main" > /etc/apt/sources.list.d/zulu.list \
    && apt-get update && apt-get install -y zulu17-jdk \
    && rm -rf /var/lib/apt/lists/*

# Install official ARM GNU Toolchain 14.2.Rel1 (matches CI carlosperate/arm-none-eabi-gcc-action release: '14.2.Rel1')
ARG ARM_TOOLCHAIN_VERSION=14.2.rel1
ARG ARM_TOOLCHAIN_URL=https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_TOOLCHAIN_VERSION}/binrel/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz

RUN wget -q "${ARM_TOOLCHAIN_URL}" -O /tmp/arm-toolchain.tar.xz \
    && mkdir -p /opt/arm-toolchain \
    && tar -xf /tmp/arm-toolchain.tar.xz -C /opt/arm-toolchain --strip-components=1 \
    && rm /tmp/arm-toolchain.tar.xz

ENV PATH="/opt/arm-toolchain/bin:${PATH}"

# Verify toolchain
RUN arm-none-eabi-gcc --version

COPY build.sh /build.sh
RUN chmod +x /build.sh

WORKDIR /rusefi

# Usage: docker run --rm -v "$(pwd):/rusefi" rusefi-build <meta-info-path> [make-target]
# e.g.   docker run --rm -v "$(pwd):/rusefi" rusefi-build config/boards/proteus/meta-info-proteus_f4.env
# e.g.   docker run --rm -v "$(pwd):/rusefi" rusefi-build config/boards/proteus/meta-info-proteus_f4.env build_both_bundles
ENTRYPOINT ["/build.sh"]
