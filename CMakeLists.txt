cmake_minimum_required(VERSION 2.8)

# set a default build type if none was provided
# this has to be done before the project() instruction!
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# project name
project(Papouja)

# include the configuration file
include(${CMAKE_SOURCE_DIR}/cmake/Config.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules/)

# dependencies
find_package(SFML 2 REQUIRED WINDOW GRAPHICS SYSTEM AUDIO NETWORK)

set(DEPS ${SFML_LIBRARIES})


# set error flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wshadow -pedantic -pedantic-errors")

# setup version numbers
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# disable the rpath stuff
set(CMAKE_SKIP_BUILD_RPATH TRUE)


# add the subdirectories
add_subdirectory(${CMAKE_SOURCE_DIR}/cmake/src/)


# setup the install rules
#install(DIRECTORY include
#        DESTINATION .
#        COMPONENT devel
#        PATTERN ".git" EXCLUDE)
#install(FILES cmake/Modules/FindSfPhysics.cmake DESTINATION ${CMAKE_ROOT}/Modules)
#install(FILES LICENSE DESTINATION ${INSTALL_MISC_DIR})

