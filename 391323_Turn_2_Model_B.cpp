#ifndef SNAKESEGMENT_H
#define SNAKESEGMENT_H

class SnakeSegment {
public:
    SnakeSegment(int x, int y);
    ~SnakeSegment();

    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x;
    int y;
};

#endif // SNAKESEGMENT_H
#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(int x, int y) : x(x), y(y) {}

SnakeSegment::~SnakeSegment() = default;
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "SnakeSegment.h"

class SnakeGame {
public:
    SnakeGame();
    ~SnakeGame();

    void growSnake();
    void moveSnake();

private:
    int headX;
    int headY;
    SnakeSegment* tail;
    SnakeSegment* head;
    int numSegments;
};

#endif // SNAKEGAME_H
#include "SnakeGame.h"

SnakeGame::SnakeGame() : headX(5), headY(5), tail(nullptr), head(nullptr), numSegments(0) {
    // Initialize the snake with a default length of 3 segments
    for (int i = 0; i < 3; ++i) {
        growSnake();
    }
}

SnakeGame::~SnakeGame() {
    clearSnake();
}

void SnakeGame::growSnake() {
    SnakeSegment* newSegment = new SnakeSegment(headX, headY);
    if (!tail) {
        head = tail = newSegment;
    } else {
        tail->x = headX;
        tail->y = headY;
        tail = newSegment;
    }
    ++numSegments;
}

void SnakeGame::clearSnake() {
    while (head) {
        SnakeSegment* temp = head;
        head = head->x;
        delete temp;
    }
    tail = nullptr;
    numSegments = 0;
}
#include "catch.hpp"
#include "SnakeGame.h"

TEST_CASE("SnakeGame test") {
    SnakeGame game;

    SECTION("Snake initial length") {
        REQUIRE(game.numSegments == 3);
    }

    SECTION("Grow snake and check length") {
        game.growSnake();
        REQUIRE(game.numSegments == 4);
        game.growSnake();
        game.growSnake();
        REQUIRE(game.numSegments == 7);
    }

    SECTION("Clear snake and check length") {
        game.growSnake();
        game.clearSnake();
        REQUIRE(game.numSegments == 0);
    }
}
#include "catch.hpp"
#include "SnakeGame.h"

int main() {
    return Catch::Session().run();
}
