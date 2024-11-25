#include <iostream>
#include <string>
#include <functional>
#include <map>

enum class RobotType {
    ARM,
    LEG,
    WHEEL
};

class Robot {
public:
    virtual ~Robot() = default;
    virtual std::string getType() const = 0;
};

class ArmRobot : public Robot {
public:
    std::string getType() const override {
        return "ArmRobot";
    }
};

class LegRobot : public Robot {
public:
    std::string getType() const override {
        return "LegRobot";
    }
};

class WheelRobot : public Robot {
public:
    std::string getType() const override {
        return "WheelRobot";
    }
};

using RobotCreator = std::function<std::unique_ptr<Robot>()>;

class RobotFactory {
public:
    static void registerRobotCreator(RobotType type, RobotCreator creator) {
        robotCreators[type] = creator;
    }

    static std::unique_ptr<Robot> createRobot(RobotType type) {
        auto it = robotCreators.find(type);
        if (it == robotCreators.end()) {
            throw std::runtime_error("Invalid robot type");
        }
        return it->second();
    }

private:
    static std::map<RobotType, RobotCreator> robotCreators;
};

std::map<RobotType, RobotCreator> RobotFactory::robotCreators;

// Function to create ArmRobot
std::unique_ptr<Robot> createArmRobot() {
    return std::make_unique<ArmRobot>();
}

// Function to create LegRobot
std::unique_ptr<Robot> createLegRobot() {
    return std::make_unique<LegRobot>();
}

// Function to create WheelRobot
std::unique_ptr<Robot> createWheelRobot() {
    return std::make_unique<WheelRobot>();
}

int main() {
    // Register robot creators
    RobotFactory::registerRobotCreator(RobotType::ARM, createArmRobot);
    RobotFactory::registerRobotCreator(RobotType::LEG, createLegRobot);
    RobotFactory::registerRobotCreator(RobotType::WHEEL, createWheelRobot);

    try {
        // Create robots using the factory
        std::unique_ptr<Robot> arm = RobotFactory::createRobot(RobotType::ARM);
        std::unique_ptr<Robot> leg = RobotFactory::createRobot(RobotType::LEG);
        std::unique_ptr<Robot> wheel = RobotFactory::createRobot(RobotType::WHEEL);

        // Display the type of robots
        std::cout << "Created Arm Robot: " << arm->getType() << std::endl;
        std::cout << "Created Leg Robot: " << leg->getType() << std::endl;
        std::cout << "Created Wheel Robot: " << wheel->getType() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
