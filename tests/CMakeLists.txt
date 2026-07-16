cmake_minimum_required(VERSION 3.16)
project(libsim_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS_DIRECTORY "./include")
set(SRC_DIRECTORY "./src")
set(INTERFACE_DIRECTORY "./lib/libsim/include")
set(LIB_DIRECTORY "../lib")

#COMPILING TESTS
set(SOURCE_FILES
	${SRC_DIRECTORY}/test_base.cpp
)
list(APPEND CMAKE_PREFIX_PATH "./lib/libsim/bin/libsim/cmake")

add_executable(test_base ${SOURCE_FILES})

set(TARGETS test_base)

foreach(target IN LISTS TARGETS)

	find_package(libsim_shared REQUIRED)
	target_link_libraries(test_base PRIVATE libsim_shared)
	get_target_property(mpth libsim_shared INTERFACE_INCLUDE_DIRECTORIES)

endforeach()
