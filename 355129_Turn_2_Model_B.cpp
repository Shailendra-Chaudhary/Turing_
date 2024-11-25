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
                            wheel_->spin();
                            motor_->powerOn();
                        }
                        void sense() {
                            sensor_->detect();
                        }

                        Robot(std::unique_ptr<Wheel> wheel, std::unique_ptr<Motor> motor, std::unique_ptr<Sensor> sensor) 
                            : wheel_(std::move(wheel)), motor_(std::move(motor)), sensor_(std::move(sensor)) {}

                    private:
                        std::unique_ptr<Wheel> wheel_;
                        std::unique_ptr<Motor> motor_;
                        std::unique_ptr<Sensor> sensor_;
                    };

                    using WheelCreator = std::function<std::unique_ptr<Wheel>()>;
                    using MotorCreator = std::function<std::unique_ptr<Motor>()>;
                    using SensorCreator = std::function<std::unique_ptr<Sensor>()>;
                    using RobotCreator = std::function<std::unique_ptr<Robot>()>;

                    class ComponentFactory {
                    public:
                        void registerWheel(WheelCreator creator) { wheelFactories_["Basic"] = creator; wheelFactories_["Advanced"] = creator; }
                        void registerMotor(MotorCreator creator) { motorFactories_["Basic"] = creator; motorFactories_["Advanced"] = creator; }
                        void registerSensor(SensorCreator creator, const std::string& name) { sensorFactories_[name] = creator; }

                        std::unique_ptr<Wheel> createWheel(const std::string& type) {
                            auto it = wheelFactories_.find(type);
                            if (it == wheelFactories_.end()) {
                                throw std::runtime_error("Invalid Wheel Type");
                            }
                            return it->second();
                        }

                        std::unique_ptr<Motor> createMotor(const std::string& type) {
                            auto it = motorFactories_.find(type);
                            if (it == motorFactories_.end()) {
                                throw std::runtime_error("Invalid Motor Type");
                            }
                            return it->second();
                        }

                        std::unique_ptr<Sensor> createSensor(const std::string& name) {
                            auto it = sensorFactories_.find(name);
                            if (it == sensorFactories_.end()) {
                                throw std::runtime_error("Invalid Sensor Type");
                            }
                            return it->second();
                        }

                    private:
                        std::map<std::string, WheelCreator> wheelFactories_;
                        std::map<std::string, MotorCreator> motorFactories_;
