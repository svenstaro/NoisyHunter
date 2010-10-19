#ifndef LOGMANAGER_HPP
#define LOGMANAGER_HPP

#include <string>
#include <iostream>

#include "LogCommand.hpp"

const std::string RED = "\033[22;31m";
const std::string GREEN = "\033[22;32m";
const std::string YELLOW = "\033[01;33m";
const std::string NO_COLOR = "\033[0m";

namespace Engine {

class LogManager {
public:
	LogManager();
	~LogManager();

	void Log(enum LogLevel log_level, enum LogOrigin log_origin, const std::string& text);

private:
};

}

#endif
