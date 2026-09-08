# Build + verification image for "Covek samo srcem dobro vidi".
#
#   docker build -t covek-steg .
#   docker run --rm covek-steg                 # runs the verification suite
#   docker run --rm -it covek-steg bash        # poke around
#
# Everything needed to compile and check the project is installed from the Ubuntu
# archive: no source builds, no extra package manager.

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        pkg-config \
        ca-certificates \
        python3 \
        qt6-base-dev \
        qt6-base-dev-tools \
        libgl1-mesa-dev \
        libopencv-dev \
        libexiv2-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build

# Default command: build smoke test + analyzer assertions.
CMD ["bash", "tests/verify.sh", "/app/build"]
