cmake_minimum_required (VERSION 2.6)
project (lab_12)

# Require c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include_directories(..)
add_executable(d1 src/driver1.cpp src/base.cpp src/d1.cpp)
add_custom_target(part1
	COMMAND ./d1
	DEPENDS d1)

add_executable(d2 src/driver2.cpp src/base.cpp src/d1.cpp)
add_custom_target(part2
    COMMAND ./d2
    DEPENDS d2)

add_custom_target(run
    DEPENDS d1 d2)