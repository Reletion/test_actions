cmake_minimum_required(VERSION 3.16)
project(libsim_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS_DIRECTORY "./include")
set(SRC_DIRECTORY "./src")
set(UNIT_DIRECTORY "${SRC_DIRECTORY}/unit")
set(BENCHMARK_DIRECTORY "${SRC_DIRECTORY}/benchmark")

include(FetchContent)
enable_testing()
list(APPEND CMAKE_PREFIX_PATH "./lib/libsim/bin/libsim/cmake")

find_package(libsim_shared REQUIRED)

set(BENCHMARK_ENABLE_TESTING off CACHE BOOL "" FORCE)

#BENCHMARKS

FetchContent_Declare(
	benchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG main
)

FetchContent_MakeAvailable(benchmark)

#GTEST
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
	gtest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(gtest)

include(GoogleTest)

#COMPILING TESTS

file(GLOB UNIT_TESTS "${UNIT_DIRECTORY}/*.cpp")
file(GLOB BENCHMARK_TESTS "${BENCHMARK_DIRECTORY}/*.cpp")

set(TARGETS test_base test_tt stupid_test_tt)

foreach(target IN LISTS UNIT_TESTS)

	get_filename_component(SOURCE ${target} NAME_WE)

	add_executable(${SOURCE} ${target})
	set_target_properties(${SOURCE} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/unit"
	)

	target_link_libraries(${SOURCE} PRIVATE libsim_shared GTest::gtest_main)

	gtest_discover_tests(${SOURCE})

endforeach()

foreach(target IN LISTS BENCHMARK_TESTS)

	get_filename_component(SOURCE ${target} NAME_WE)

	add_executable(${SOURCE} ${target})
	set_target_properties(${SOURCE} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/benchmarks"
	)

	target_link_libraries(${SOURCE} PRIVATE libsim_shared benchmark::benchmark)

endforeach()
