# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER i586-mingw32msvc-gcc)
SET(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)
SET(CMAKE_RC_COMPILER i586-mingw32msvc-windres)

include_directories(/usr/local/include) 

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH /usr/i586-mingw32msvc /usr/local/ /usr/local/include ${CMAKE_SOURCE_DIR}/lib)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE /usr/local/include)

