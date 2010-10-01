#include "LogManager.hpp"

namespace Engine {

LogManager::LogManager() {}

LogManager::~LogManager() {}

void LogManager::Log(enum LogLevel log_level, enum LogOrigin log_origin, const std::string& text) {
	std::string log_message;
	
	if(log_level == LOGLEVEL_URGENT)
		log_message = YELLOW+"[URGENT: ";
	else if(log_level == LOGLEVEL_VERBOSE)
		log_message = GREEN+"[VERBOSE: ";
	else if(log_level == LOGLEVEL_ERROR)
		log_message = RED+"[VERBOSE: ";
	

	if(log_origin == LOGORIGIN_NETWORK)
		log_message += "NETWORK] ";
	else if(log_origin == LOGORIGIN_ENTITY)
		log_message += "ENTITY] ";
	else if(log_origin == LOGORIGIN_STATE)
		log_message += "STATE] ";
	else if(log_origin == LOGORIGIN_VECTOR)
		log_message += "VECTOR] ";
	else if(log_origin == LOGORIGIN_RESOURCEMANAGER)
		log_message += "RESOURCEMANAGER] ";
	else if(log_origin == LOGORIGIN_GUI)
		log_message += "GUI] ";
	

	log_message += NO_COLOR + text;
	std::cout << log_message << std::endl;
}

}
