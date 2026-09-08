# Wires tests/verify.sh into CTest so `ctest --test-dir build` runs it.
find_program(BASH_EXECUTABLE bash)

if(BASH_EXECUTABLE)
    add_test(
        NAME verify
        COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/verify.sh ${CMAKE_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    set_tests_properties(verify PROPERTIES
        FAIL_REGULAR_EXPRESSION "FAIL:"
        PASS_REGULAR_EXPRESSION "ALL CHECKS PASSED"
    )
else()
    message(STATUS "bash not found - skipping the 'verify' test")
endif()
