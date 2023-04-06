#include "add.h"

#include <catch2/catch_test_macros.hpp>

// Demonstrate some basic assertions.
TEST_CASE("AddTest", "BasicAssertions") {
    REQUIRE(add(6, 7) == 13);
}
