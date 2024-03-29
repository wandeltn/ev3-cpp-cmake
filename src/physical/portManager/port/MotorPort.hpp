#ifndef __MOTOR_PORT_HPP__
#define __MOTOR_PORT_HPP__

#include <physical/portManager/port/Port.hpp>
#include <filesystem>
#include <vector>

namespace finder
{
    namespace physical
    {
        enum class MotorCommand
        {
            STOP = 0,
            RESET = 1,
            RUN_FOREVER = 2,
            RUN_TO_ABS_POS = 3,
            RUN_TO_REL_POS = 4,
            RUN_TIMED = 5,
            RUN_DIRECT = 6,
        };

        enum class MotorStopAction
        {
            COAST = 0,
            BRAKE = 1,
            HOLD = 2,
        };

        enum class MotorPolarity
        {
            NORMAL = 0,
            INVERSED = 1,
        };

        enum class MotorState
        {
            STOPPED = 0,
            RUNNING = 1,
            RAMPING = 2,
            OVERLOADED = 3,
            STALLED = 4,
            HOLDING = 5,
        };

        class MotorPort : public Port {
            public:
                MotorPort();
                MotorPort(std::string port_name);
                MotorPort(std::shared_ptr<Port> port);

                path_speed_t getSpeedPath();
                path_position_sp_t getPositionSpPath();
                path_duty_cycle_t getDutyCyclePath();
                path_state_t getStatePath();
                path_polarity_t getPolarityPath();
                path_stop_action_t getStopActionPath();
                path_count_per_rotation_t getCountPerRotationPath();
                

                void setSpeed(int speed);
                void setPositionSp(int position_sp);
                void setDutyCycle(int duty_cycle);
                void setPolarity(MotorPolarity polarity);
                void setStopAction(MotorStopAction stop_action);
                void setCommand(MotorCommand command);

                std::vector<MotorState> getState();
                int getCountPerRotation();

                DeviceType getDeviceType() override;

            private:
                static ::finder::console::Logger _logger;

                std::shared_ptr<std::ofstream> _file_speed_path;
                std::shared_ptr<std::ofstream> _file_position_sp_path;
                std::shared_ptr<std::ofstream> _file_duty_cycle_path;
                std::shared_ptr<std::ifstream> _file_state_path;
                std::shared_ptr<std::ofstream> _file_polarity_path;
                std::shared_ptr<std::ofstream> _file_stop_action_path;
                std::shared_ptr<std::ifstream> _file_count_per_rotation_path;
                
                bool _is_initialized;

                void init();
        };
    } // namespace physical
} // namespace finder

#endif // __MOTOR_PORT_HPP__