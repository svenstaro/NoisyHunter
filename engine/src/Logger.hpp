#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>
#include <iomanip>

#include "LogCommand.hpp"

const std::string RED = "\033[22;31m";		// critical error
const std::string GREEN = "\033[22;32m";	// debug
const std::string YELLOW = "\033[01;33m";	// urgent
const std::string BLUE = "\033[01;34m";		// message
const std::string PURPLE = "\033[22;35m";	// warning
const std::string CYAN = "\033[22;36m";		// no use -- yet
const std::string NO_COLOR = "\033[0m";

namespace Engine {

class Logger {
public:
	Logger(int show_levels = 0x00011111);
	~Logger();

	void Log(enum LogLevel::LogLevel log_level, enum LogOrigin::LogOrigin log_origin, const std::string& text);

	void SetShowLevels(int show_levels);
	int GetShowLevels() const;

	// Shortcuts
	static void Critical(enum LogOrigin::LogOrigin origin, const std::string& text);
	static void Urgent(enum LogOrigin::LogOrigin origin, const std::string& text);
	static void Warning(enum LogOrigin::LogOrigin origin, const std::string& text);
	static void Message(enum LogOrigin::LogOrigin origin, const std::string& text);
	static void Debug(enum LogOrigin::LogOrigin origin, const std::string& text);

private:
	int mShowLevels;
};

}

#endif // LOGGER
