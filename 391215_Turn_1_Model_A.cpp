// Legacy component - utility function to calculate factorial
int factorial(int n) {
    if (n < 0) throw std::invalid_argument("Factorial is not defined for negative numbers.");
    return n == 0 ? 1 : n * factorial(n - 1);
}

// Catch2 test cases for factorial function
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Factorial function") {
    SECTION("Handles zero") {
        REQUIRE(factorial(0) == 1);
    }

    SECTION("Handles positive numbers") {
        REQUIRE(factorial(3) == 6);
        REQUIRE(factorial(5) == 120);
        REQUIRE(factorial(7) == 5040);
    }

    SECTION("Throws an exception for negative numbers") {
        REQUIRE_THROWS(factorial(-1));
        REQUIRE_THROWS(factorial(-5));
    }
}

int main() {
    return Catch::RunAllTests();
}
