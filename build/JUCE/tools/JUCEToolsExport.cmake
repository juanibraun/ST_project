# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8)
   message(FATAL_ERROR "CMake >= 2.8.0 required")
endif()
if(CMAKE_VERSION VERSION_LESS "2.8.3")
   message(FATAL_ERROR "CMake >= 2.8.3 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.8.3...3.23)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_cmake_targets_defined "")
set(_cmake_targets_not_defined "")
set(_cmake_expected_targets "")
foreach(_cmake_expected_target IN ITEMS juce_tools::juceaide)
  list(APPEND _cmake_expected_targets "${_cmake_expected_target}")
  if(TARGET "${_cmake_expected_target}")
    list(APPEND _cmake_targets_defined "${_cmake_expected_target}")
  else()
    list(APPEND _cmake_targets_not_defined "${_cmake_expected_target}")
  endif()
endforeach()
unset(_cmake_expected_target)
if(_cmake_targets_defined STREQUAL _cmake_expected_targets)
  unset(_cmake_targets_defined)
  unset(_cmake_targets_not_defined)
  unset(_cmake_expected_targets)
  unset(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT _cmake_targets_defined STREQUAL "")
  string(REPLACE ";" ", " _cmake_targets_defined_text "${_cmake_targets_defined}")
  string(REPLACE ";" ", " _cmake_targets_not_defined_text "${_cmake_targets_not_defined}")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_cmake_targets_defined_text}\nTargets not yet defined: ${_cmake_targets_not_defined_text}\n")
endif()
unset(_cmake_targets_defined)
unset(_cmake_targets_not_defined)
unset(_cmake_expected_targets)


# Create imported target juce_tools::juceaide
add_executable(juce_tools::juceaide IMPORTED)

# Import target "juce_tools::juceaide" for configuration "Debug"
set_property(TARGET juce_tools::juceaide APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(juce_tools::juceaide PROPERTIES
  IMPORTED_LOCATION_DEBUG "/Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide"
  )

# Import target "juce_tools::juceaide" for configuration "Release"
set_property(TARGET juce_tools::juceaide APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(juce_tools::juceaide PROPERTIES
  IMPORTED_LOCATION_RELEASE "/Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Release/juceaide"
  )

# Import target "juce_tools::juceaide" for configuration "MinSizeRel"
set_property(TARGET juce_tools::juceaide APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(juce_tools::juceaide PROPERTIES
  IMPORTED_LOCATION_MINSIZEREL "/Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/MinSizeRel/juceaide"
  )

# Import target "juce_tools::juceaide" for configuration "RelWithDebInfo"
set_property(TARGET juce_tools::juceaide APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(juce_tools::juceaide PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "/Users/juanbraun/dev/ST_project/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/RelWithDebInfo/juceaide"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
