#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libsim_static" for configuration ""
set_property(TARGET libsim_static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(libsim_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/libsim/liblibsim_static.a"
  )

list(APPEND _cmake_import_check_targets libsim_static )
list(APPEND _cmake_import_check_files_for_libsim_static "${_IMPORT_PREFIX}/bin/libsim/liblibsim_static.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
