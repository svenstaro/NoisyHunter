#ifndef LOGCOMMAND_HPP
#define LOGCOMMAND_HPP

namespace Engine {

namespace LogLevel {
	enum LogLevel {
		CRITICAL	= 0x00010000,
		URGENT		= 0x00001000,
		WARNING		= 0x00000100,
		MESSAGE		= 0x00000010,
		DEBUG		= 0x00000001
	};
}

namespace LogOrigin {
	enum LogOrigin {
		NETWORK,
		ENTITY,
		STATE,
		VECTOR,
		RESOURCEMANAGER,
		GUI,
		IDMANAGER,
		CLIENTMANAGER,
		ROOT,
		PARTICLE,
		WORLD,
		MUSICMANAGER
	};
}

}

#endif
