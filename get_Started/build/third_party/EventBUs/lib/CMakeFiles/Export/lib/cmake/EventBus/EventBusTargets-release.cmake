#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Dexode::EventBus" for configuration "Release"
set_property(TARGET Dexode::EventBus APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Dexode::EventBus PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libEventBus.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Dexode::EventBus )
list(APPEND _IMPORT_CHECK_FILES_FOR_Dexode::EventBus "${_IMPORT_PREFIX}/lib/libEventBus.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
