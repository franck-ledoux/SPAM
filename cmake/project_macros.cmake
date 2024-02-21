#==============================================================================
# The procedure is given for the component of this project with the component
# structure including subdirectories inc/ and src/
#==============================================================================
# COMP_NAME    component name
macro(prj_component_install COMP_NAME)
target_include_directories(${COMP_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_INSTALL_NAME}>)

install(TARGETS ${COMP_NAME}
        EXPORT ${PROJECT_NAME}-config
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/inc/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_INSTALL_NAME})
endmacro()
#==============================================================================
# Coverage activation environment
#==============================================================================
function(cover COVER_EXEC)
    set(CMAKE_CXX_FLAGS "-O0 -coverage -fprofile-arcs -ftest-coverage")
    # find required tools
    find_program(LCOV lcov REQUIRED)
    find_program(GENHTML genhtml REQUIRED)
    # add coverage target
    add_custom_target(coverage
            # Run tests
            COMMAND ${COVER_EXEC}
            # gather data
            COMMAND
            ${LCOV} --directory . --capture --exclude '*/tst/*' --exclude '/usr/*' --output-file coverage.info
            # generate report
            COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM)
endfunction()
#==============================================================================
# Conditional add of a subdirectory
#==============================================================================
# COMP_NAME    component name
# COND         Boolean value to add or not COMP_NAME
function(prj_add_subdirectory_if COMP_NAME COND)
    if(${COND})
        add_subdirectory(${COMP_NAME})
    endif()
endfunction()