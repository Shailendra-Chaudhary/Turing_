#include <iostream>
#include <string>
#include <functional>
#include <map>

enum class RobotType {
    BASIC,
    ADVANCED,
    SENSOR
};

class Robot {
public:
    virtual ~Robot() = default;
    virtual void move() = 0;
    virtual void sense() = 0;
    virtual void interact() = 0;
    std::string getType() const {
        switch (type) {
            case RobotType::BASIC:
                return "Basic Robot";
            case RobotType::ADVANCED:
                return "Advanced Robot";
            case RobotType::SENSOR:
                return "Sensor Robot";
        }
    }

protected:
    RobotType type;
    Robot(RobotType t) : type(t) {}
};

class BasicRobot : public Robot {
public:
    BasicRobot() : Robot(RobotType::BASIC) {}
    void move() override { std::cout << "Basic Robot moving." << std::endl; }
    void sense() override { std::cout << "Basic Robot sensing." << std::endl; }
    void interact() override { std::cout << "Basic Robot interacting." << std::endl; }
};

class AdvancedRobot : public Robot {
public:
    AdvancedRobot() : Robot(RobotType::ADVANCED) {}
    void move() override { std::cout << "Advanced Robot moving with precision." << std::endl; }
    void sense() override { std::cout << "Advanced Robot sensing with high accuracy." << std::endl; }
    void interact() override { std::cout << "Advanced Robot interacting intelligently." << std::endl; }
};

class SensorRobot : public Robot {
public:
    SensorRobot() : Robot(RobotType::SENSOR) {}
    void move() override { std::cout << "Sensor Robot moving slowly." << std::endl; }
    void sense() override { std::cout << "Sensor Robot providing detailed data." << std::endl; }
    void interact() override { std::cout << "Sensor Robot interacting with specialized tools." << std::endl; }
};

using RobotCreator = std::function<std::unique_ptr<Robot>()>;

class RobotFactory {
public:
    void registerRobot(RobotType type, RobotCreator creator) {
        robotFactories[type] = creator;
    }

    std::unique_ptr<Robot> createRobot(RobotType type) {
        auto it = robotFactories.find(type);
        if (it == robotFactories.end()) {
            throw std::runtime_error("Invalid Robot Type");
        }
        return it->second();
    }

private:
    std::map<RobotType, RobotCreator> robotFactories;
};

int main() {
    RobotFactory robotFactory;

    robotFactory.registerRobot(RobotType::BASIC, []{ return std::make_unique<BasicRobot>(); });
    robotFactory.registerRobot(RobotType::ADVANCED, []{ return std::make_unique<AdvancedRobot>(); });
    robotFactory.registerRobot(RobotType::SENSOR, []{ return std::make_unique<SensorRobot>(); });

    try {
        {
            auto robot = robotFactory.createRobot(RobotType::BASIC);
            std::cout << "Created: " << robot->getType() << std::endl;
            robot->move();
            robot->sense();
            robot->interact();
        }

        {
            auto robot = robotFactory.createRobot(RobotType::ADVANCED);
            std::cout << "Created: " << robot->getType() << std::endl;
            robot->move();
            robot->sense();
            robot->interact();
        }

        {
            auto robot = robotFactory.createRobot(RobotType::SENSOR);
            std::cout << "Created: " << robot->getType() << std::endl;
            robot->move();
            robot->sense();
