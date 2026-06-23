cmake_minimum_required(VERSION 3.16)

project(libsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS_DIRECTORY "./include")
set(SRC_DIRECTORY "./src/core")

set(SOURCE_FILES
  ${HEADERS_DIRECTORY}/libsim_global.h
  ${SRC_DIRECTORY}/libsim.cpp
  ${HEADERS_DIRECTORY}/libsim.h
)

# add_library(libsim SHARED
#   ${SOURCE_FILES}
# )

add_library(libsim_shared SHARED ${SOURCE_FILES})
add_library(libsim_static STATIC ${SOURCE_FILES})

set(TARGETS libsim_shared libsim_static)

foreach(target IN LISTS TARGETS)

  target_include_directories( ${target} PRIVATE
    ${HEADERS_DIRECTORY}
    ${SRC_DIRECTORY}
  )

  target_compile_definitions(${target} PRIVATE LIBSIM_LIBRARY)

endforeach()
