cmake_minimum_required(VERSION 3.5)

project(Covek-samo-srcem-dobro-vidi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall -Wextra")

# ZA QT PAKETE
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ZA OPENCV BIBLIOTEKU
find_package(OpenCV REQUIRED)
message(STATUS "Include dirs: ${OpenCV_INCLUDE_DIRS}")

# ZA EXIV2 BIBLIOTEKU
find_package(exiv2 REQUIRED)
message(STATUS "Include dirs: ${Exiv2_INCLUDE_DIRS}")

# ZA EXIFTOOL INTERFACE
set(EXIFTOOL_DIR "/home/marijana/Downloads/cpp_exiftool")
include_directories(${EXIFTOOL_DIR}/inc)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${EXIFTOOL_DIR}/src/ExifTool.cpp
        ${EXIFTOOL_DIR}/src/ExifToolPipe.cpp
        ${EXIFTOOL_DIR}/src/TagInfo.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Covek-samo-srcem-dobro-vidi
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        colorfilter.h colorfilter.cpp
        metadata.h metadata.cpp
        ImageFormats.h

    )
else()
    if(ANDROID)
        add_library(Covek-samo-srcem-dobro-vidi SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Covek-samo-srcem-dobro-vidi
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Covek-samo-srcem-dobro-vidi PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PUBLIC exiv2::exiv2)

target_include_directories(${PROJECT_NAME} PRIVATE ${EXIFTOOL_DIR}/inc)


if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Covek-samo-srcem-dobro-vidi)
endif()
set_target_properties(Covek-samo-srcem-dobro-vidi PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Covek-samo-srcem-dobro-vidi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Covek-samo-srcem-dobro-vidi)
endif()