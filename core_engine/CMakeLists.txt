cmake_minimum_required(VERSION 3.10)
if(POLICY CMP0177)
	cmake_policy(SET CMP0177 NEW)
endif()
project(CivicEngine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
	src/Transmission.cpp
	src/FuelTank.cpp
	src/Wheel.cpp
	src/Speedometer.cpp
	src/Tachometer.cpp
	src/Car.cpp
	src/Engine.cpp)

set(HEADERS
	include/Transmission.h
	include/FuelTank.h
	include/Engine.h
	include/Wheel.h
	include/Speedometer.h
	include/Tachometer.h
	include/Car.h)

add_executable(CivicEngine ${SOURCES} ${HEADERS})

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

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES
	tests/TransmissionTests.cpp
	tests/FuelTankTests.cpp
	tests/EngineTests.cpp
	tests/WheelTests.cpp
	tests/SpeedometerTests.cpp
	tests/TachometerTests.cpp
	tests/CarTests.cpp
)
add_executable(
	CivicEngineTests
	${TEST_SOURCES}
)
target_link_libraries(
	CivicEngineTests
	gtest_main
)
target_include_directories(CivicEngineTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(CivicEngineTests PRIVATE ${SOURCES})