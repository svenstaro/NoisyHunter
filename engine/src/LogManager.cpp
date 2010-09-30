#include "LogManager.hpp"

namespace Engine {

	LogManager::LogManager() {}
	LogManager::LogManager(bool is_verbose, bool is_server) {
		mIsVerbose = is_verbose;
		mIsServer = is_server;
	}
	
	LogManager::~LogManager() {}

	void LogManager::Log(enum LogLevel log_level, enum LogOrigin log_origin, const std::string& text) {
	
		if(mIsServer) {
			if(log_level == LOGLEVEL_URGENT) {
				if(log_origin == LOGORIGIN_NETWORK)
					std::cout << GREEN << "[URGENT: NETWORK] " << NO_COLOR << text << std::endl;
				else if(log_origin == LOGORIGIN_ENTITY)
					std::cout << GREEN << "[URGENT: ENTITY] " << NO_COLOR << text << std::endl;
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
		}
	
	}
	
	
}
