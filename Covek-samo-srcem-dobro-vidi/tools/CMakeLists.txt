add_executable(stegcli stegcli.cpp)
set_target_properties(stegcli PROPERTIES AUTOMOC OFF AUTOUIC OFF AUTORCC OFF)
target_link_libraries(stegcli PRIVATE stegcore)

include(GNUInstallDirs)
install(TARGETS stegcli RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
