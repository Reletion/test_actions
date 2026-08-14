#----------------------------------------------------------------
# Generated CMake target import file for configuration "Releas".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libsim_shared" for configuration "Releas"
set_property(TARGET libsim_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEAS)
set_target_properties(libsim_shared PROPERTIES
  IMPORTED_LOCATION_RELEAS "${_IMPORT_PREFIX}/bin/libsim/liblibsim_shared.so"
  IMPORTED_SONAME_RELEAS "liblibsim_shared.so"
  )

list(APPEND _cmake_import_check_targets libsim_shared )
list(APPEND _cmake_import_check_files_for_libsim_shared "${_IMPORT_PREFIX}/bin/libsim/liblibsim_shared.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
