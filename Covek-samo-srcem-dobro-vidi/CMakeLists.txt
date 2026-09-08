cmake_minimum_required(VERSION 3.16)

project(Covek-samo-srcem-dobro-vidi VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options($<$<CONFIG:Debug>:-Wall> $<$<CONFIG:Debug>:-Wextra>)
endif()

# --- Dependencies -----------------------------------------------------------
find_package(OpenCV REQUIRED)
find_package(exiv2 REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# --- Targets --------------------------------------------------------------
add_subdirectory(core)   # stegcore : analysis engine, no Qt
add_subdirectory(gui)    # Covek-samo-srcem-dobro-vidi : Qt front-end
add_subdirectory(tools)  # stegcli : headless runner for the engine

enable_testing()
add_subdirectory(tests)  # ctest -> tests/verify.sh
