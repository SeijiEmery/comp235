cmake_minimum_required (VERSION 2.6)
project (lab_16)

SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# Require c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX0x)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0x)
if(COMPILER_SUPPORTS_CXX0x)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0x)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include_directories(..)

add_executable(exercise1 src/exercise_1.cpp)
add_custom_target(ex1
    COMMAND ./exercise1
    DEPENDS exercise1)

add_executable(exercise2 src/exercise_2.cpp)
add_custom_target(ex2
    COMMAND ./exercise2
    DEPENDS exercise2)

add_executable(exercise3 src/exercise_3.cpp)
add_custom_target(ex3
    COMMAND ./exercise3
    DEPENDS exercise3)

add_custom_target(run
    DEPENDS ex1 ex2 ex3)
