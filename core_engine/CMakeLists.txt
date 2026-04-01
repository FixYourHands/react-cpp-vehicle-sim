cmake_minimum_required(VERSION 3.10)
project(CivicEngine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
	src/main.cpp
	)

add_executable(CivicEngine ${SOURCES})

target_include_directories(CivicEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
