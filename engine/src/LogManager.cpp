#include "LogManager.hpp"

namespace Engine {

LogManager::LogManager() {}

LogManager::~LogManager() {}

void LogManager::Log(enum LogLevel log_level, enum LogOrigin log_origin, const std::string& text) {
	std::string log_message;
	if(log_level == LOGLEVEL_URGENT) {
		log_message = "[URGENT: "+YELLOW;
		if(log_origin == LOGORIGIN_NETWORK)
			log_message += "NETWORK] ";
		else if(log_origin == LOGORIGIN_ENTITY)
			log_message += "ENTITY] ";
		else if(log_origin == LOGORIGIN_STATE)
			log_message += "STATE] ";
	}

	else if(log_level == LOGLEVEL_VERBOSE) {
		if(mIsVerbose) {
			if(log_origin == LOGORIGIN_NETWORK)
				std::cout << YELLOW << "[VERBOSE: NETWORK] " << NO_COLOR << text << std::endl;
			else if(log_origin == LOGORIGIN_ENTITY)
				std::cout << YELLOW << "[VERBOSE: ENTITY] " << NO_COLOR << text << std::endl;
		}
	}

	else if(log_level == LOGLEVEL_ERROR) {
		if(log_origin == LOGORIGIN_NETWORK)
			std::cerr << RED << "[URGENT: NETWORK] " << text << NO_COLOR << std::endl;
		else if(log_origin == LOGORIGIN_ENTITY)
			std::cerr << RED << "[ERROR: ENTITY] " << text << NO_COLOR << std::endl;
	}
	log_message += text;
	std::cout << log_message << std::endl;
}

}
