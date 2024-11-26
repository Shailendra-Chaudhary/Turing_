

```c++
#include <iostream>
#include <string>
#include <deque>
#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

class MenuSystem : public QMainWindow {
    Q_OBJECT

public:
    MenuSystem();

private slots:
    void onMenuItemTriggered(QAction* action);

private:
    QMenu* fileMenu;
    QAction* openFileAction;
    QAction* saveFileAction;
    QAction* closeFileAction;
    QAction* exitAction;

    std::deque<QAction*> dynamicMenuItems;
};

MenuSystem::MenuSystem() {
    // Set up the main window
    setWindowTitle("Responsive Menu System");
    resize(400, 300);

    // Create the menu bar and file menu
    QMenuBar* menuBar = new QMenuBar(this);
    fileMenu = new QMenu("File", this);
    menuBar->addMenu(fileMenu);

    // Initialize the static menu items
    openFileAction = fileMenu->addAction("Open File");
    saveFileAction = fileMenu->addAction("Save File");
    closeFileAction = fileMenu->addAction("Close File");
    closeFileAction->setEnabled(false); // Disable "Close File" initially
    exitAction = fileMenu->addAction("Exit");

    // Connect the signal-slot for menu item triggers
    connect(fileMenu, &QMenu::triggered, this, &MenuSystem::onMenuItemTriggered);

    setMenuBar(menuBar);
}

void MenuSystem::onMenuItemTriggered(QAction* action) {
    if (action == openFileAction) {
        std::cout << "Opening file..." << std::endl;
        // Update the menu based on the user action
        closeFileAction->setEnabled(true);
        // Add a dynamic menu item for "Save As"
        QAction* saveAsAction = fileMenu->addAction("Save As");
        dynamicMenuItems.push_back(saveAsAction);
    } else if (action == closeFileAction) {
        std::cout << "Closing file..." << std::endl;
        closeFileAction->setEnabled(false);
        // Remove the dynamic "Save As" menu item
        for (const auto& item : dynamicMenuItems) {
            fileMenu->removeAction(item);
            delete item;
        }
        dynamicMenuItems.clear();
    } else if (action == exitAction) {
        qApp->quit();
    } else {
        // Handle other dynamic menu items if needed
        std::cout << "Triggered: " << action->text().toStdString() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MenuSystem menuSystem;
    menuSystem.show();
    return app.exec();
}
