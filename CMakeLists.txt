cmake_minimum_required(VERSION 3.16)


include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

project(libsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS_DIRECTORY "./include")
set(SRC_DIRECTORY "./src")
set(LIB_DIRECTORY "./lib")
set(BUILD_DIRECTORY "${CMAKE_INSTALL_LIBDIR}/libsim")

message(STATUS ${CMAKE_PREFIX_PATH})

set(SOURCE_FILES
  ${SRC_DIRECTORY}/core/base.cpp
  ${SRC_DIRECTORY}/core/input.cpp
  ${HEADERS_DIRECTORY}/object_template.h
 # ${SRC_DIRECTORY}/elements/and_gate.cpp
  #${SRC_DIRECTORY}/elements/or_gate.cpp
  #${SRC_DIRECTORY}/elements/not_gate.cpp
)

# add_library(libsim SHARED
#   ${SOURCE_FILES}
# )

add_library(libsim_shared SHARED ${SOURCE_FILES})
add_library(libsim_static STATIC ${SOURCE_FILES})

set(TARGETS libsim_shared libsim_static)

foreach(target IN LISTS TARGETS)

  target_include_directories( ${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${HEADERS_DIRECTORY}>
    $<INSTALL_INTERFACE:${HEADERS_DIRECTORY}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIRECTORY}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIB_DIRECTORY}>
    $<INSTALL_INTERFACE:${LIB_DIRECTORY}>
  )

  install(TARGETS ${target}
	EXPORT "${target}_lib"
	LIBRARY DESTINATION ${BUILD_DIRECTORY}
	ARCHIVE DESTINATION ${BUILD_DIRECTORY}
	RUNTIME DESTINATION ${BUILD_DIRECTORY}
	INCLUDES DESTINATION ${HEADERS_DIRECTORY}
	INCLUDES DESTINATION ${LIB_DIRECTORY}
  )

  install(DIRECTORY ${HEADERS_DIRECTORY}/ DESTINATION ${BUILD_DIRECTORY}/include)
  install(DIRECTORY ${LIB_DIRECTORY}/ DESTINATION ${BUILD_DIRECTORY}/lib)

  install(EXPORT "${target}_lib"
	FILE "${target}_lib.cmake"
	DESTINATION ${BUILD_DIRECTORY}
  )

  write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
	VERSION 0.0.1
	COMPATIBILITY SameMajorVersion
  )

   configure_package_config_file(
	"${target}_libConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/libsim
	PATH_VARS CMAKE_INSTALL_INCLUDEDIR
   )

   install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/libsim
   )

   target_compile_definitions(${target} PRIVATE LIBSIM_LIBRARY)

endforeach()
