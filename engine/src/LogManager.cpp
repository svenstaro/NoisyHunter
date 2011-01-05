#include "LogManager.hpp"

namespace Engine {

LogManager::LogManager(bool is_verbose) {
	mIsVerbose = is_verbose;
}

LogManager::~LogManager() {}

void LogManager::Log(enum LogLevel log_level, enum LogOrigin log_origin, const std::string& text) {
	std::string log_message;
	
	if(log_level == LOGLEVEL_URGENT)
		log_message = YELLOW+"[URGENT:  ";
	else if(log_level == LOGLEVEL_VERBOSE and !mIsVerbose)
		return;
	else if(log_level == LOGLEVEL_VERBOSE and mIsVerbose)
		log_message = GREEN+"[VERBOSE: ";
	else if(log_level == LOGLEVEL_ERROR)
		log_message = RED+"[ERROR:   ";
	

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
	else if(log_origin == LOGORIGIN_IDMANAGER)
		log_message += "IDMANAGER] ";
	else if(log_origin == LOGORIGIN_CLIENTMANAGER)
		log_message += "CLIENTMANAGER] ";
	else if(log_origin == LOGORIGIN_ROOT)
		log_message += "ROOT] ";
	else if(log_origin == LOGORIGIN_WORLD)
		log_message += "WORLD] ";
	else if(log_origin == LOGORIGIN_MUSICMANAGER)
		log_message += "MUSICMANAGER] ";

	log_message += NO_COLOR + text;
	if(log_level == LOGLEVEL_ERROR)
		std::cerr << log_message << std::endl;
	else
		std::cout << log_message << std::endl;
}

void LogManager::SetVerbose(bool is_verbose) {
	mIsVerbose = is_verbose;
}

bool LogManager::GetVerbose() {
	return mIsVerbose;
}

}
