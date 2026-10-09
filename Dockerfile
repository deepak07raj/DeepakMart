FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
ENV VCPKG_MAX_CONCURRENCY=1
ENV CMAKE_BUILD_PARALLEL_LEVEL=1
ENV PGSSLMODE=require

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        cmake \
        ninja-build \
        git \
        curl \
        zip \
        unzip \
        tar \
        pkg-config \
        ca-certificates \
        bison \
        flex \
        autoconf \
        automake \
        libtool \
        python3 \
        python3-setuptools \
        python3-venv && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /opt

RUN git clone --depth 1 https://github.com/microsoft/vcpkg.git

RUN /opt/vcpkg/bootstrap-vcpkg.sh -disableMetrics

WORKDIR /app

COPY . .

RUN /opt/vcpkg/vcpkg install \
    --triplet x64-linux

RUN cmake \
    -S . \
    -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake

RUN cmake --build build --config Release -j 1

EXPOSE 10000

CMD ["./build/deepakmart"]