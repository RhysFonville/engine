#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Engine::engine" for configuration ""
set_property(TARGET Engine::engine APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Engine::engine PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libengine.a"
  )

list(APPEND _cmake_import_check_targets Engine::engine )
list(APPEND _cmake_import_check_files_for_Engine::engine "${_IMPORT_PREFIX}/lib/libengine.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
