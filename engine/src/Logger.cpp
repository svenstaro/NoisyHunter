#include "Logger.hpp"
#include "Root.hpp"

namespace Engine {

Logger::Logger(int show_levels) {
	mShowLevels = show_levels;
}

Logger::~Logger() {}

void Logger::Log(enum LogLevel::LogLevel log_level, enum LogOrigin::LogOrigin log_origin, const std::string& text) {
	if((int(log_level) & mShowLevels) != 0) {

		std::string color = "";
		std::string level = "";
		std::string orig = "";

		// Output log level
		if(log_level == LogLevel::CRITICAL) {
			color = RED;
			level = "CRITICAL";
		} else if(log_level == LogLevel::URGENT) {
			color = YELLOW;
			level = "URGENT";
		} else if(log_level == LogLevel::WARNING) {
			color = PURPLE;
			level = "WARNING";
		} else if(log_level == LogLevel::MESSAGE) {
			color = BLUE;
			level = "MESSAGE";
		} else if(log_level == LogLevel::DEBUG) {
			color = GREEN;
			level = "DEBUG";
		}

		// Output log origin
		if(log_origin == LogOrigin::NETWORK)
			orig = "NETWORK";
		else if(log_origin == LogOrigin::ENTITY)
			orig = "ENTITY";
		else if(log_origin == LogOrigin::STATE)
			orig = "STATE";
		else if(log_origin == LogOrigin::VECTOR)
			orig = "VECTOR";
		else if(log_origin == LogOrigin::RESOURCEMANAGER)
			orig = "RESOURCEMANAGER";
		else if(log_origin == LogOrigin::GUI)
			orig = "GUI";
		else if(log_origin == LogOrigin::IDMANAGER)
			orig = "IDMANAGER";
		else if(log_origin == LogOrigin::CLIENTMANAGER)
			orig = "CLIENTMANAGER";
		else if(log_origin == LogOrigin::ROOT)
			orig = "ROOT";
		else if(log_origin == LogOrigin::WORLD)
			orig = "WORLD";
		else if(log_origin == LogOrigin::MUSICMANAGER)
			orig = "MUSICMANAGER";

		level = "[" + level + ": ";
		orig += "] ";

		if(log_level == LogLevel::CRITICAL)
			std::cerr << color << std::setw(11) << std::left << level << std::setw(17) << std::setfill('-') << std::left << orig << " " << std::setfill(' ') << NO_COLOR << text << NO_COLOR << std::endl;
		else
			std::cout << color << std::setw(11) << std::left << level << std::setw(17) << std::setfill('-') << std::left << orig << " " << std::setfill(' ') << NO_COLOR << text << NO_COLOR << std::endl;
	}
}

void Logger::SetShowLevels(int show_levels) {
	mShowLevels = show_levels;
}

int Logger::GetShowLevels() const {
	return mShowLevels;
}


// --------------- Shortcuts ---------------

void Logger::Critical(enum LogOrigin::LogOrigin origin, const std::string& text) {
	Root::get_mutable_instance().GetLoggerPtr()->Log(LogLevel::CRITICAL, origin, text);
}

void Logger::Urgent(enum LogOrigin::LogOrigin origin, const std::string& text) {
	Root::get_mutable_instance().GetLoggerPtr()->Log(LogLevel::URGENT, origin, text);
}

void Logger::Warning(enum LogOrigin::LogOrigin origin, const std::string& text) {
	Root::get_mutable_instance().GetLoggerPtr()->Log(LogLevel::WARNING, origin, text);
}

void Logger::Message(enum LogOrigin::LogOrigin origin, const std::string& text) {
	Root::get_mutable_instance().GetLoggerPtr()->Log(LogLevel::MESSAGE, origin, text);
}

void Logger::Debug(enum LogOrigin::LogOrigin origin, const std::string& text) {
	Root::get_mutable_instance().GetLoggerPtr()->Log(LogLevel::DEBUG, origin, text);
}

}

