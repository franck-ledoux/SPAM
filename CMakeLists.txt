#===============================================================================
cmake_minimum_required(VERSION 3.20)
#===============================================================================
project(spam VERSION 1.0.0 LANGUAGES CXX)
#===============================================================================
# Standard options
set(CMAKE_CXX_STANDARD 14)
#===============================================================================
# LIBRARIES ARE INSTALLED USING THE VERSION NUMBER OF OUR PROJECT
set(PROJECT_INSTALL_NAME ${PROJECT_NAME}-${PROJECT_VERSION})
#===============================================================================
# specific macros are given in this file
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")
include(GNUInstallDirs)
include(project_macros)

#===============================================================================
add_subdirectory(mcts)
add_subdirectory(takuzu)
#===============================================================================
# INSTALLATION PROCEDURE
#===============================================================================
# DESTINATION directory is the project name + version number
set(DESTINATION_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_INSTALL_NAME})

# Do not modify below!
install(EXPORT ${PROJECT_NAME}-config
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${DESTINATION_DIR})

configure_file(${PROJECT_NAME}-config.cmake.in
        ${PROJECT_NAME}-config.cmake
        @ONLY)
#===============================================================================
