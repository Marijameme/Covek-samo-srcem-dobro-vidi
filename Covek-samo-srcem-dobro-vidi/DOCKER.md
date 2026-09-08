# Building and verifying in Docker

The `Dockerfile` installs everything the project needs (GCC, CMake, Ninja, Qt 6,
OpenCV, Exiv2, Python 3), compiles all targets, and can run a verification suite.
All dependencies come from the Ubuntu archive - no package manager beyond apt.

## Quick start

```sh
cd Covek-samo-srcem-dobro-vidi

docker build -t covek-steg .        # ~5 min first time, seconds after
docker run --rm covek-steg          # build smoke test + analyzer assertions
```

Expected tail of the output:

```
PASS: stegcli and GUI binaries present
PASS: clean image: format detected, no trailing data
PASS: appended data + ZIP signature detected
PASS: Qt GUI constructs under the offscreen platform

ALL CHECKS PASSED
```

## What the verification does (`tests/verify.sh`)

1. Confirms `stegcli` and the GUI binary were produced.
2. `tests/make_samples.py` writes a clean PNG and a copy with a fake ZIP header
   appended after `IEND`.
3. Runs `stegcli` on both and checks: PNG format is detected (Exiv2), the clean
   file reports no trailing data, the tampered file gets a `positive` verdict and
   names the ZIP signature.
4. Runs the GUI with `--selftest` under `QT_QPA_PLATFORM=offscreen` to confirm it
   links and constructs without a display.

It is also wired into CTest:

```sh
docker run --rm covek-steg bash -c "ctest --test-dir build --output-on-failure"
```

## docker compose

```sh
docker compose run --rm verify                    # same as `docker run --rm covek-steg`
docker compose run --rm stegcli /work/some.png    # analyse a file in the project dir
```

## Running the GUI

The GUI needs an X server on the host.

Linux:

```sh
xhost +local:docker
docker compose run --rm gui
xhost -local:docker
```

macOS / Windows: run an X server (XQuartz / VcXsrv), set `DISPLAY` accordingly,
then `docker compose run --rm gui`.

## Building locally (without Docker)

Install the three libraries from your distro, then the normal CMake flow:

```sh
sudo apt install build-essential cmake ninja-build \
     qt6-base-dev qt6-base-dev-tools libopencv-dev libexiv2-dev

cd Covek-samo-srcem-dobro-vidi
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## Notes

- Ubuntu 24.04 packages Exiv2 0.27.6; the code also builds against 0.28.x.
  `core/CMakeLists.txt` detects whichever imported target is available.
- The image builds Release by default. For a debug build:
  `docker run --rm covek-steg bash -c "cmake -S . -B d -DCMAKE_BUILD_TYPE=Debug && cmake --build d"`.
