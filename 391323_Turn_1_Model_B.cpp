#include<iostream>
#include<cstdlib>
using namespace std;
// Constants for the game
const int GAME_WIDTH = 20;
const int GAME_HEIGHT = 20;
class SnakeSegment {
public:
    int x;
    int y;

    SnakeSegment(int x, int y) : x(x), y(y) {}
    // Add a destructor to deallocate memory automatically
    ~SnakeSegment() {}
};
class Snake {
private:
    int* snakeLength; // To store the length of the snake
    SnakeSegment** snakeBody; // Dynamic pointer to store snake segments

public:
    Snake() {
        // Initially the snake has length 1
        snakeLength = new int;
        *snakeLength = 1;

        snakeBody = new SnakeSegment*[1]; // Initializing snake body with length 1
        snakeBody[0] = new SnakeSegment(10, 10); // Creating the first segment
    }
   /*
    *  else if (direction == UP) {
            x = snakeBody->x;
            y = snakeBody->y - 1;
        } 
    */
    //    Function to grow the snake
    void grow() {
        // Allocate memory for an additional segment
        snakeBody = realloc(snakeBody, sizeof(SnakeSegment*) * (*snakeLength + 1));
        if (!snakeBody) {
            cout << "Memory allocation failed!" << endl;
            exit(EXIT_FAILURE);
        }
        
        // Create the new segment at the head of the snake (assume head is at snakeBody[0])
        // You'll update the new head position based on the snake's growth direction
        snakeBody[*snakeLength] = new SnakeSegment(snakeBody[0]->x, snakeBody[0]->y); // Decide the position here
 
        (*snakeLength)++;
    }
    //  Free dynamically allocated memory in the destructor
    ~Snake() {
      
        for (int i = 0; i < *snakeLength; i++) {
            delete snakeBody[i];
        }
        delete[] snakeBody;
        delete snakeLength;
    }

    void move() {
        // Implement the movement logic here
        // Move each segment according to the direction

        // Example: For simplicity, let's assume the snake grows in the UP direction
        for (int i = *snakeLength - 1; i > 0; i--) {
            snakeBody[i]->x = snakeBody[i - 1]->x;
            snakeBody[i]->y = snakeBody[i - 1]->y;
        }

        // Move the head of the snake (first element in snakeBody) in the current direction
        // Check for collisions and boundaries here
    }
    //Function to display the snake
    void display(){
    
        for (int i = 0; i < *snakeLength; i++) {
            cout << "* ";
        }
        cout << endl;
    }
};

int main() {
    Snake snake;
    bool gameOver = false;

    while (!gameOver) {
        snake.display();
        snake.move();

        // Handle user input and game logic here

        // Simulate growth for this example
        snake.grow();

        // Check for collisions and game over conditions
        // ...
    }

    // Game ends, free the memory

    return 0;
}
