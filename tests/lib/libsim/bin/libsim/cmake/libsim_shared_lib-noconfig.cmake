#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libsim_shared" for configuration ""
set_property(TARGET libsim_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(libsim_shared PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/libsim/liblibsim_shared.so"
  IMPORTED_SONAME_NOCONFIG "liblibsim_shared.so"
  )

list(APPEND _cmake_import_check_targets libsim_shared )
list(APPEND _cmake_import_check_files_for_libsim_shared "${_IMPORT_PREFIX}/bin/libsim/liblibsim_shared.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
