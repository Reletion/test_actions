cmake_minimum_required(VERSION 3.16)
project(libsim_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS_DIRECTORY "./include")
set(SRC_DIRECTORY "./src")
set(INTERFACE_DIRECTORY "../include")
set(LIB_DIRECTORY "../lib")

#COMPILING TESTS
set(SOURCE_FILES
	${SRC_DIRECTORY}/test_base.cpp
)

add_executable(test_base ${SOURCE_FILES})

set(TARGETS test_base)

foreach(target IN LISTS TARGETS)

	target_include_directories(${target} PRIVATE
		${INTERFACE_DIRECTORY}
	)

	#ADD_LIBRARIES
	add_library(libsim SHARED IMPORTED)
	set_target_properties(libsim PROPERTIES
		IMPORTED_LOCATION ../liblibsim_shared.so
		$<BUILD_INTERFACE:INTERFACE_INCLUDE_DIRECTORIES ../include>
	)
	target_link_libraries(test_base PRIVATE libsim)

endforeach()
