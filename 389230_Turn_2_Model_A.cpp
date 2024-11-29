#include <iostream>
#include <vector>
#include <string>

// Model
class TodoListModel {
private:
    std::vector<std::string> tasks;

public:
    void addTask(const std::string& task) {
        tasks.push_back(task);
    }

    void removeTask(const std::string& task) {
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (*it == task) {
                tasks.erase(it);
                return;
            }
        }
        std::cerr << "Task not found." << std::endl;
    }

    const std::vector<std::string>& getTasks() const {
        return tasks;
    }
};

// View
class TodoListView {
private:
    TodoListModel* model;

public:
    TodoListView(TodoListModel* model) : model(model) {}

    void displayTasks() const {
        if (model->getTasks().empty()) {
            std::cout << "No tasks available." << std::endl;
            return;
        }

        std::cout << "Current Tasks:" << std::endl;
        for (size_t i = 0; i < model->getTasks().size(); ++i) {
            std::cout << (i + 1) << ". " << model->getTasks()[i] << std::endl;
        }
    }

    void promptForTask() {
        std::string task;
        std::cout << "Enter task: ";
        std::getline(std::cin, task);

        if (!task.empty()) {
            model->addTask(task);
        }
    }

    void promptToRemoveTask() {
        int taskNumber;
        std::cout << "Enter the number of the task to remove: ";
        if (std::cin >> taskNumber && taskNumber > 0 && taskNumber <= model->getTasks().size()) {
            std::string task = model->getTasks()[taskNumber - 1];
            model->removeTask(task);
        } else {
            std::cerr << "Invalid task number." << std::endl;
        }
    }
};

// Controller
class TodoListController {
private:
    TodoListModel* model;
    TodoListView* view;

public:
    TodoListController(TodoListModel* model, TodoListView* view) : model(model), view(view) {}

    void handleInput() {
        char input;
        while (true) {
            view->displayTasks();
            std::cout << "Enter 'a' to add task, 'r' to remove task, 'q' to quit: ";
            std::cin >> input;

            if (input == 'q') {
                std::cout << "Goodbye!" << std::endl;
                break;
            } else if (input == 'a') {
                view->promptForTask();
            } else if (input == 'r') {
                view->promptToRemoveTask();
            } else {
                std::cout << "Invalid input, please try again." << std::endl;
            }
        }
    }
};

// Main function
int main() {
    TodoListModel model;
    TodoListView view(&model);
    TodoListController controller(&model, &view);

    controller.handleInput();

    return 0;
}
