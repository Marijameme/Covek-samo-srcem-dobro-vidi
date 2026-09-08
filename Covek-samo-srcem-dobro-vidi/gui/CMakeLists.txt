# Qt front-end. All real work is delegated to stegcore.

set(GUI_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    cvqt.cpp
    cvqt.h
)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(Covek-samo-srcem-dobro-vidi MANUAL_FINALIZATION ${GUI_SOURCES})
else()
    add_executable(Covek-samo-srcem-dobro-vidi ${GUI_SOURCES})
endif()

target_link_libraries(Covek-samo-srcem-dobro-vidi
    PRIVATE
        stegcore
        Qt${QT_VERSION_MAJOR}::Widgets
)

set_target_properties(Covek-samo-srcem-dobro-vidi PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Covek-samo-srcem-dobro-vidi
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_finalize_executable(Covek-samo-srcem-dobro-vidi)
endif()
