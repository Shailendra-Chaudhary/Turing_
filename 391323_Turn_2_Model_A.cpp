#include <iostream>
#include <memory>
#include <vector>

// Define the GameObject class
class GameObject {
public:
    GameObject(int id) : id(id) {
        std::cout << "GameObject " << id << " created.\n";
    }
    
    ~GameObject() {
        std::cout << "GameObject " << id << " destroyed.\n";
    }

    void update() {
        // Logic to update the game object
        std::cout << "Updating GameObject " << id << ".\n";
    }

private:
    int id;
};

// Define the Game class that manages GameObjects
class Game {
public:
    Game() {}
    
    void addGameObject(int id) {
        // Smart pointer to manage GameObject's lifetime
        auto obj = std::make_shared<GameObject>(id);
        gameObjects.push_back(obj);
    }
    
    void updateGameObjects() {
        for (auto& obj : gameObjects) {
            obj->update();
        }
    }

private:
    std::vector<std::shared_ptr<GameObject>> gameObjects; // Vector of smart pointers
};

// Main function to demonstrate functionality
int main() {
    Game game;
    
    // Add some game objects
    game.addGameObject(1);
    game.addGameObject(2);
    game.addGameObject(3);
    
    // Update game objects
    game.updateGameObjects();

    // No explicit delete is needed; smart pointers handle memory management.
    return 0;
}
