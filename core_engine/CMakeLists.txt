cmake_minimum_required(VERSION 3.10)
if(POLICY CMP0177)
	cmake_policy(SET CMP0177 NEW)
endif()
project(CivicEngine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
	src/main.cpp
	src/Transmission.cpp
	src/FuelTank.cpp
	src/Wheel.cpp
	src/Speedometer.cpp
	src/Tachometer.cpp
	src/Car.cpp
	src/Engine.cpp)

add_executable(CivicEngine ${SOURCES} "include/Transmission.h" "include/FuelTank.h" "include/Engine.h" "include/Wheel.h" "include/Speedometer.h" "include/Tachometer.h" "include/Car.h")

target_include_directories(CivicEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(EMSCRIPTEN)
	target_link_options(CivicEngine PRIVATE
		"--bind"
		"-sMODULARIZE=1"
		"-sEXPORT_ES6=1"
		"-sALLOW_MEMORY_GROWTH=1"
		)
		set_target_properties(CivicEngine PROPERTIES SUFFIX ".js")
endif()

install(TARGETS CivicEngine DESTINATION "${CMAKE_SOURCE_DIR}/../dashboard_ui/src/wasm")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/CivicEngine.wasm" DESTINATION "${CMAKE_SOURCE_DIR}/../dashboard_ui/src/wasm")