#ifndef PORT_HPP
#define PORT_HPP
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>
#include <vector>
#ifdef ENABLE_LOGGING
#include <Logger.hpp>
#include <FileLogger.hpp>
#endif
namespace finder
{
    namespace physical
    {
        typedef std::string path_port_t;
        typedef std::string path_address_t;
        typedef std::string path_value_t;
        typedef std::string path_mode_t;
        typedef std::string path_modes_t;
        typedef std::string path_command_t;
        typedef std::string path_commands_t;
        typedef std::string path_position_t;
        typedef std::string path_position_sp_t;
        typedef std::string path_speed_t;
        typedef std::string path_speed_sp_t;
        typedef std::string path_count_per_rotation_t;
        typedef std::string path_duty_cycle_t;
        typedef std::string path_stop_action_t;
        typedef std::string path_polarity_t;
        typedef std::string path_state_t;
        typedef std::string path_num_values_t;
        typedef std::string path_poll_ms_t;

        enum struct DeviceType {
            SENSOR = 0,
            MOTOR = 1,
            UNKNOWN = 2,
            DISABLED = 3,
            ANY = 4
        };
#ifdef ENABLE_LOGGING
        struct Port : public log::FileLogger
#else
        struct Port
#endif
        {
            public:
                // Port();
                Port(const path_port_t& port);
                Port(std::shared_ptr<Port> port);
                Port(Port&) = delete;
                ~Port() = default;

                virtual void setBasePath(const path_port_t& path);
                
                inline char getPortKey() {
                    if (isEnabled())
                    {
                        return _path.back();
                    }
                    return -1;
                };
                path_port_t getBasePath();
                path_address_t getAddressPath();
                static path_address_t getAddressPath(const path_port_t& path);
                path_command_t getCommandPath();
                path_commands_t getCommandsPath();

                /**
                 * @brief Get the address of the port.
                 * 
                 * @return The address of the port as a string.
                 */
                std::string getAddress();
                
                /**
                 * Sets the command for the port.
                 *
                 * @param command The command to set.
                 * @return True if the command was set successfully, false otherwise.
                 */
                bool setCommand(std::string command);

                /// @brief get the commands that the port can execute from file 
                /// @return vector of strings of the commands that the port can execute
                std::vector<std::string> getCommands();

                /// @brief gets the device type of the port
                /// @return the device type of the port, SENSOR, MOTOR, UNKNOWN, or DISABLED
                virtual DeviceType getDeviceType();

            
                /// @brief return the enabled status of the port
                /// @return true if the port is enabled, false otherwise
                bool isEnabled();

                /// @brief This is a testing function to override the enabled status of the port
                /// @warning NOT TO BE USED IN PRODUCTION! ONLY FOR TESTING PURPOSES!
                /// @param enabled the new enabled status
                void overrideEnabled(bool enabled) { _f_enabled = enabled; };

            protected:  
                /**
                 * Initializes the files for the port.
                 * 
                 * @return true if the files were successfully initialized, false otherwise.
                 */
                bool initFiles();
                std::shared_ptr<std::ifstream> _file_address_path;
                std::shared_ptr<std::ofstream> _file_command_path;
                std::shared_ptr<std::ifstream> _file_commands_path;
                path_port_t _path;
            private:
                bool _f_enabled;
                // bool _enabled;
#ifdef ENABLE_LOGGING
                static ::finder::log::Logger _logger;
#endif

        };

    } // namespace physical
    
} // namespace finder

#endif // PORT_HPP