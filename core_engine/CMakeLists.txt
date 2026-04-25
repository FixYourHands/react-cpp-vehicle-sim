cmake_minimum_required(VERSION 3.10)
project(CivicEngine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
	src/main.cpp
	src/Transmission.cpp
	src/FuelTank.cpp
	src/Wheel.cpp
	src/Speedometer.cpp
	src/Tachometer.cpp)

add_executable(CivicEngine ${SOURCES} "include/Transmission.h" "include/FuelTank.h" "include/Engine.h" "include/Wheel.h" "include/Speedometer.h" "include/Tachometer.h" "include/Car.h")

target_include_directories(CivicEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
