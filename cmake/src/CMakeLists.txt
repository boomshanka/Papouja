# include the Papouja specific macros
#include(${CMAKE_SOURCE_DIR}/cmake/Macros.cmake)

# add the Papouja sources path
##include_directories(${CMAKE_SOURCE_DIR}/src/)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake//Modules/")

# set the output directory
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/")


# all source files
set(SRC
    ${SRCROOT}/Main.cpp
    ${SRCROOT}/Settings.hpp
    ${SRCROOT}/Settings.cpp
    ${SRCROOT}/iniManager.hpp
    ${SRCROOT}/iniManager.cpp
    ${SRCROOT}/GameManager.hpp
    ${SRCROOT}/GameManager.cpp
    ${SRCROOT}/GameState.hpp
    ${SRCROOT}/GSIntro.hpp
    ${SRCROOT}/GSIntro.cpp
    ${SRCROOT}/GSMenu.hpp
    ${SRCROOT}/GSMenu.cpp
    ${SRCROOT}/GSSettings.hpp
    ${SRCROOT}/GSSettings.cpp
    ${SRCROOT}/GSSingleplayerGame.hpp
    ${SRCROOT}/GSSingleplayerGame.cpp
    ${SRCROOT}/GSMultiplayerGame.hpp
    ${SRCROOT}/GSMultiplayerGame.cpp
    ${SRCROOT}/GSNetworkGame.hpp
    ${SRCROOT}/GSNetworkGame.cpp
    ${SRCROOT}/GSError.hpp
    ${SRCROOT}/GSError.cpp    
)

# add executable
add_executable(Papouja ${SRC})
target_link_libraries(Papouja ${DEPS})

