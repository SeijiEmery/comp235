cmake_minimum_required (VERSION 2.6)
project (assignment_01)

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

add_executable(treadmill_calculator src/treadmill_calculator_driver.cpp src/treadmill_calculator.cpp)
add_custom_target(run_treadmill
	COMMAND ./treadmill_calculator
	DEPENDS treadmill_calculator)

add_executable(highscore src/highscore_driver.cpp src/highscore.cpp)
add_custom_target(run_highscore
	COMMAND ./run_highscore
	DEPENDS run_highscore)

add_custom_target(run
	DEPENDS run_highscore run_treadmill)
