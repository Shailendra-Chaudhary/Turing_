#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <memory>

// Robot Components
class Wheel {
public:
    virtual ~Wheel() = default;
    virtual void spin() = 0;
};

class BasicWheel : public Wheel {
public:
    void spin() override { std::cout << "Basic Wheel spinning." << std::endl; }
};

class AdvancedWheel : public Wheel {
public:
    void spin() override { std::cout << "Advanced Wheel spinning with precision." << std::endl; }
};

class Motor {
public:
    virtual ~Motor() = default;
    virtual void powerOn() = 0;
};

class BasicMotor : public Motor {
public:
    void powerOn() override { std::cout << "Basic Motor powering on." << std::endl; }
};

class AdvancedMotor : public Motor {
public:
    void powerOn() override { std::cout << "Advanced Motor powering on with high torque." << std::endl; }
};

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual void detect() = 0;
};

class UltrasonicSensor : public Sensor {
public:
    void detect() override { std::cout << "Ultrasonic Sensor detecting obstacles." << std::endl; }
};

class CameraSensor : public Sensor {
public:
    void detect() override { std::cout << "Camera Sensor capturing images." << std::endl; }
};

// Robot Class using Components
class Robot {
public:
    virtual ~Robot() = default;
    void move() {
        wheel->spin();
        motor->powerOn();
    }
    void sense() {
        sensor->detect();
    }

protected:
    std::unique_ptr<Wheel> wheel;
    std::unique_ptr<Motor> motor;
    std::unique_ptr<Sensor> sensor;

    Robot(std::unique_ptr<Wheel> wheel, std::unique_ptr<Motor> motor, std::unique_ptr<Sensor> sensor)
        : wheel(std::move(wheel)), motor(std::move(motor)), sensor(std::move(sensor)) {}

    friend class RobotFactory;
};

// Component Creators
using WheelCreator = std::function<std::unique_ptr<Wheel>()>;
using MotorCreator = std::function<std::unique_ptr<Motor>()>;
using SensorCreator = std::function<std::unique_ptr<Sensor>()>;

// Robot Factory
class RobotFactory {
public:
    void registerWheel(WheelCreator wheelCreator) { wheelFactory = wheelCreator; }
    void registerMotor(MotorCreator motorCreator) { motorFactory = motorCreator; }
    void registerSensor(SensorCreator sensorCreator) { sensorFactory = sensorCreator; }

    std::unique_ptr<Robot> createRobot() {
        return std::make_unique<Robot>(
            wheelFactory(),
            motorFactory(),
            sensorFactory()
        );
    }

private:
    WheelCreator wheelFactory;
    MotorCreator motorFactory;
    SensorCreator sensorFactory;
};

int main() {
    RobotFactory robotFactory;

    // Register Component Creators
    robotFactory.registerWheel([]{ return std::make_unique<BasicWheel>(); });
    robotFactory.registerMotor([]{ return std::make_unique<BasicMotor>(); });
    robotFactory.registerSensor([]{ return std::make_unique<UltrasonicSensor>(); });

    {
        auto robot = robotFactory.createRobot();
        std::cout << "Created Robot with Basic Components." << std::endl;
        robot->move();
        robot->sense();
    }

    // Change Component Creators for Advanced Components
    robotFactory.registerWheel([]{ return std::make_unique<AdvancedWheel>(); });
    robotFactory.registerMotor([]{ return std::make_unique<AdvancedMotor>(); });
    robotFactory.registerSensor([]{ return std::make_unique<CameraSensor>(); });

    {
