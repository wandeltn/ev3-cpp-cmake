#include <iostream>
#include <string>

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

namespace finder
{
    namespace log
    {
        enum class LogLevel {
            DEBUG = 0,
            INFO = 1,
            POSITIVE = 2,
            WARN = 3,
            ERROR = 4,
            SILENT = 5
        };
        
        class Logger {
            public:


                Logger() : _minlLevel(LogLevel::DEBUG) {}
                Logger(LogLevel minLogLevel);

                LogLevel getMinLevel() {return _minlLevel;}
                LogLevel getActiveLogLevel();

                void setMinLevel(LogLevel level) {_minlLevel = level;}

                void log(LogLevel level, const std::string& message);
                void log(LogLevel level, const LogLevel& message);

                void error(const std::string& message);
                void error(const LogLevel& message);

                void warn(const std::string& message);
                void warn(const LogLevel& message);

                void info(const std::string& message);
                void info(const LogLevel& message);

                void debug(const std::string& message);
                void debug(const LogLevel& message);

                void positive(const std::string& message);
                void positive(const LogLevel& message);
                void success(const std::string& message) { this->positive(message); };

                static void enforceLogLevel(LogLevel level);
                static void removeLogLevelEnforcement() {_logLevelEnforced = false;}
                static bool isLogLevelEnforced() {return _logLevelEnforced;}

            private:
                LogLevel _minlLevel;
                static bool _logLevelEnforced;
                static LogLevel _enforcedLogLevel;
        };
    } // namespace log
} // namespace finder

#endif // __LOGGER_HPP__