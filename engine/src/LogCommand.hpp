#ifndef LOGCOMMAND_HPP
#define LOGCOMMAND_HPP

namespace Engine {

enum LogLevel {

	LOGLEVEL_URGENT = 0x00,

	LOGLEVEL_VERBOSE = 0x01,

	LOGLEVEL_ERROR = 0x02

};

enum LogOrigin {

	LOGORIGIN_NETWORK = 0x00,

	LOGORIGIN_ENTITY = 0x01

};

}

#endif
