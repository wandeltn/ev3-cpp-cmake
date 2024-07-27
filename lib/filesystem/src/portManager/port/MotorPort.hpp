#ifndef __MOTOR_PORT_HPP__
#define __MOTOR_PORT_HPP__

#include <portManager/port/Port.hpp>
#include <filesystem>
#include <vector>

namespace finder
{
    namespace physical
    {

        // The command to send to the motor
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

        // How to stop the motor after completing a command
        enum class MotorStopAction
        {
            COAST = 0,
            BRAKE = 1,
            HOLD = 2,
        };

        // What direction all motors should turn. Not specific to one motor.
        enum class MotorPolarity
        {
            NORMAL = 0,
            INVERSED = 1,
        };

        // What state a motor is in
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
                // MotorPort();


                /// @brief Initialize a motor
                /// @param port_name The internal path to the motor directory on the system. This is not to be hardcoded, as this changes frequently.
                MotorPort(std::string port_name);
                
                /// @brief Initialize a motor using a existing initialized port. This will not remove the access of the old port and create a new port with the same directory.
                /// @param port Existing port to initialize a new MotorPort.
                MotorPort(std::shared_ptr<Port> port);

                /// @brief Get the path for reading the speed of the motor using the initialized path.
                /// @return The Path for reading the speed of the motor.
                path_speed_t getSpeedPath();

                /// @brief Get the path for reading the current position of the motor, or setting the target position to move to. Use run-to-rel-pos to move to set position.
                /// @return Path to set or read the position.
                path_position_sp_t getPositionSpPath();

                /// @brief Get the path to set the duty cycle of the motor to turn at. Start the motor using run-direct. Else this value is ignored.
                /// @return Path to set the duty cycle to turn at.
                path_duty_cycle_t getDutyCyclePath();

                /// @brief Get the path to read the state of the motor from. Multiple stated possible and seperated by spaces. 
                /// @return Path to read the state of the motor from. 
                path_state_t getStatePath();

                /// @brief Path to set the polarity of the motor. This will apply to all motors, therefore should not be used for turning in place.
                /// @return Path to set the polarity of all motors.
                path_polarity_t getPolarityPath();

                /// @brief Path to set the action to use after completing a task. 
                /// @return Path to set the stop action.
                path_stop_action_t getStopActionPath();

                /// @brief Get the motor pulses per rotation of the motor. Represents the pulses of the rotary encoder. Defaults to 360.
                /// @return Path to read the encoder pulses from.
                path_count_per_rotation_t getCountPerRotationPath();
                
                /// @brief Set the speed the motor should move at, max ca. 800.
                /// @param speed Speed in pulses per second.
                void setSpeed(int speed);

                /// @brief Set the destination position for the run-to-rel-pos and run-to-abs-pos motor commands. 
                /// @param position_sp Pulses for the motor to move.
                void setPositionSp(int position_sp);

                /// @brief Set the duty cycle (speed) to move at when using run-direct command. 
                /// @param duty_cycle Speed in % for the motor to move at. 
                void setDutyCycle(int duty_cycle);

                /// @brief Set the polarity for all motors. Can reverse the direction the motors are running.
                /// @param polarity 
                void setPolarity(MotorPolarity polarity);

                /// @brief Set the way to stop the motor after completing an action. Most useful ist hold, as it holds the target position
                /// @param stop_action Stop action to use to stop the motor
                void setStopAction(MotorStopAction stop_action);

                /// @brief Send a specific movement command to the motor. Some params might have to be set first for some command. See the official documentation for more.
                /// @param command Command to send to the motor.
                void setCommand(MotorCommand command);

                /// @brief shorthand for setting the command to "stop".
                void stop();

                /// @brief Get the current states of the motor a vector
                /// @return Vector of current motor states.
                std::vector<MotorState> getState();

                /// @brief Get the motor pulses per revolution of the motor. Read from MotorCommand::getCountPerRotationPath()
                /// @return Number of motor pulses per rotation of the motor.
                int getCountPerRotation();

                /// @brief Get the type of device registered in the constructor, as there are no checks for the correct device beforehand.
                /// @return Type of device registered by constructor.
                DeviceType getDeviceType() override;

            private:
#ifdef ENABLE_LOGGING
                static ::finder::log::Logger _logger;
#endif
                std::shared_ptr<std::ofstream> _file_speed_path;
                std::shared_ptr<std::ofstream> _file_position_sp_path;
                std::shared_ptr<std::ofstream> _file_duty_cycle_path;
                std::shared_ptr<std::ifstream> _file_state_path;
                std::shared_ptr<std::ofstream> _file_polarity_path;
                std::shared_ptr<std::ofstream> _file_stop_action_path;
                std::shared_ptr<std::ifstream> _file_count_per_rotation_path;
                
                bool _is_initialized;

                /// @brief Inititalize the motor class by checking if files exist and opening file streams.
                void init();
        };
    } // namespace physical
} // namespace finder

#endif // __MOTOR_PORT_HPP__