cmake_minimum_required(VERSION 3.13.4)

project(cmake-clang-template)

# This C++ standard is required to build this project.
set(PROJECT_REQUIRED_CXX_STANDARD 17)

# If we find that the cache contains CMAKE_CXX_STANDARD it means that it's a old CMakeCache.txt
# and we can just inform the user and then reset it.
if($CACHE{CMAKE_CXX_STANDARD} AND $CACHE{CMAKE_CXX_STANDARD} LESS ${PROJECT_REQUIRED_CXX_STANDARD})
  message(WARNING "Resetting cache value for CMAKE_CXX_STANDARD to ${PROJECT_REQUIRED_CXX_STANDARD}")
  unset(CMAKE_CXX_STANDARD CACHE)
endif()

# if CMAKE_CXX_STANDARD is still set after the cache unset above it means that the user requested it
# and we allow it to be set to something newer than the required standard but otherwise we fail.
if(DEFINED CMAKE_CXX_STANDARD AND CMAKE_CXX_STANDARD LESS ${PROJECT_REQUIRED_CXX_STANDARD})
  message(FATAL_ERROR "Requested CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} which is less than the required ${PROJECT_REQUIRED_CXX_STANDARD}.")
endif()

set(CMAKE_CXX_STANDARD ${PROJECT_REQUIRED_CXX_STANDARD} CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Generate a CompilationDatabase (compile_commands.json file) for our build,
# for use by clang_complete, YouCompleteMe, etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/lib)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
cmake_policy(SET CMP0135 NEW)
endif()

enable_testing()

# Add google test
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.2
)
FetchContent_MakeAvailable(Catch2)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

# Use the CMakeLists.txt in the src directory.
add_subdirectory(src)
add_subdirectory(test)
