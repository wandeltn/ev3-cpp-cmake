#include <physical/DeviceManager.hpp>

namespace finder
{
    namespace physical
    {
        std::shared_ptr<PortManager> DeviceManager::_portManager;
        std::shared_ptr<SensorPort> DeviceManager::_gyroSensor;
        std::shared_ptr<SensorPort> DeviceManager::_colorSensorLeft;
        std::shared_ptr<SensorPort> DeviceManager::_colorSensorRight;
        std::shared_ptr<SensorPort> DeviceManager::_colorSensorFront;
        std::shared_ptr<MotorPort> DeviceManager::_motorLeft;
        std::shared_ptr<MotorPort> DeviceManager::_motorRight;
        std::shared_ptr<MotorPort> DeviceManager::_motorShift;
        std::shared_ptr<MotorPort> DeviceManager::_motorTool;
        bool DeviceManager::_initialized = false;



        DeviceManager::DeviceManager(std::string portBasePath)
        {
            if (!_initialized)
            {
                init(portBasePath);
            }
        }

        DeviceManager::~DeviceManager()
        {
        }

        void DeviceManager::init(std::string portBasePath)
        {
            _portManager = std::make_shared<PortManager>(portBasePath);
            _portManager->readPorts();

            // is it possible to borrow a port that is not connected?
            // can stay like this for now, but should be changed in the future
            _gyroSensor = _portManager->borrowSensor(_portManager->adresses[0]);
            _colorSensorLeft = _portManager->borrowSensor(_portManager->adresses[1]);
            _colorSensorRight = _portManager->borrowSensor(_portManager->adresses[2]);
            _colorSensorFront = _portManager->borrowSensor(_portManager->adresses[3]);
            _motorLeft = _portManager->borrowMotor(_portManager->adresses[4]);
            _motorRight = _portManager->borrowMotor(_portManager->adresses[5]);
            _motorShift = _portManager->borrowMotor(_portManager->adresses[6]);
            _motorTool = _portManager->borrowMotor(_portManager->adresses[7]);

            _initialized = true;
        }
    } // namespace physical
    
} // namespace finder

