// Legacy component: a simple calculator class
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
    int multiply(int a, int b) { return a * b; }
    int divide(int a, int b) {
        if (b == 0) throw std::invalid_argument("Division by zero");
        return a / b;
    }
};

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Calculator operations", "[calculator]") {
    Calculator calc;

    SECTION("Addition") {
        REQUIRE(calc.add(2, 3) == 5);
        REQUIRE(calc.add(-1, 1) == 0);
        REQUIRE(calc.add(-3, -3) == -6);
    }

    SECTION("Subtraction") {
        REQUIRE(calc.subtract(5, 3) == 2);
        REQUIRE(calc.subtract(-1, 1) == -2);
        REQUIRE(calc.subtract(-3, -3) == 0);
    }

    SECTION("Multiplication") {
        REQUIRE(calc.multiply(2, 3) == 6);
        REQUIRE(calc.multiply(-1, 1) == -1);
        REQUIRE(calc.multiply(-3, -3) == 9);
    }

    SECTION("Division") {
        REQUIRE(calc.divide(6, 3) == 2);
        REQUIRE_THROWS_AS(calc.divide(1, 0), std::invalid_argument);
    }
}

int main() {
    return Catch::RunAllTests();
}
