# stegcore - steganalysis engine. No Qt: depends only on OpenCV and Exiv2 so it
# stays unit-testable and reusable outside the GUI.

add_library(stegcore STATIC
    src/Finding.cpp
    src/ImageContext.cpp
    src/Metadata.cpp
    src/BitPlane.cpp
    src/AnalyzerRegistry.cpp
    src/analyzers/MetadataAnalyzer.cpp
    src/analyzers/TrailingDataAnalyzer.cpp
)

set_target_properties(stegcore PROPERTIES AUTOMOC OFF AUTOUIC OFF AUTORCC OFF)

target_include_directories(stegcore
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(stegcore PUBLIC cxx_std_17)

# OpenCV appears in public headers (cv::Mat), so it is a PUBLIC dependency.
target_include_directories(stegcore SYSTEM PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(stegcore PUBLIC ${OpenCV_LIBS})

# Exiv2 is used only inside .cpp files -> PRIVATE. The imported target name varies:
#   Exiv2::exiv2   upstream CMake package (>= 0.27.99)
#   exiv2::exiv2   some third-party packages
#   exiv2lib       Debian / Ubuntu libexiv2-dev (0.27.x)
set(_exiv2_target "")
foreach(_candidate Exiv2::exiv2 exiv2::exiv2 exiv2lib exiv2)
    if(TARGET ${_candidate})
        set(_exiv2_target ${_candidate})
        break()
    endif()
endforeach()

if(_exiv2_target)
    target_link_libraries(stegcore PRIVATE ${_exiv2_target})
    message(STATUS "stegcore: using exiv2 target '${_exiv2_target}'")
else()
    # Fall back to pkg-config (Debian ships exiv2.pc).
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(EXIV2 REQUIRED IMPORTED_TARGET exiv2)
    target_link_libraries(stegcore PRIVATE PkgConfig::EXIV2)
    message(STATUS "stegcore: using exiv2 via pkg-config")
endif()
