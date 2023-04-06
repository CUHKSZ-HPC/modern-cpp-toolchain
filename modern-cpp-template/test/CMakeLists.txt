add_executable(
  tests
  ${CMAKE_SOURCE_DIR}/src/add.cpp
  add_test.cpp
)

if (MSVC)
    # warning level 4
    target_compile_options(main PRIVATE /W4)
else()
    # lots of warnings
    target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(
  tests
  Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(tests)
