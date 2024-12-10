#include <iostream>
#include <vector>

class GameObject {
public:
    GameObject(int id) : id(id) {
        std::cout << "GameObject " << id << " created.\n";
    }
    
    ~GameObject() {
        std::cout << "GameObject " << id << " destroyed.\n";
    }

    void update() {
        // Update logic for the game object
        std::cout << "Updating GameObject " << id << ".\n";
    }

private:
    int id;
};

class Game {
public:
    Game() {}
    
    void addGameObject(int id) {
        // Dynamically allocate a new GameObject and store the pointer
        GameObject* obj = new GameObject(id);
        gameObjects.push_back(obj);
    }
    
    void updateGameObjects() {
        for (auto obj : gameObjects) {
            obj->update();
        }
    }
    
    ~Game() {
        // Clean up dynamically allocated memory
        for (auto obj : gameObjects) {
            delete obj; // Free allocated memory for each GameObject
        }
    }

private:
    std::vector<GameObject*> gameObjects;
};

int main() {
    Game game;

    // Add some game objects
    game.addGameObject(1);
    game.addGameObject(2);
    game.addGameObject(3);
    
    // Update game objects
    game.updateGameObjects();

    // Game destructor will clean up allocated memory for gameObjects
    return 0;
}
