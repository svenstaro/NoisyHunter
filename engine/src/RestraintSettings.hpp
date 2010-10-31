#ifndef RESTRAINTSETTINGS_HPP
#define RESTRAINTSETTINGS_HPP

namespace Engine {

struct RestraintSettings {
public:
	RestraintSettings(bool x = false, bool y = false, bool rot = false);

	bool RestrainX;
	bool RestrainY;
	bool RestrainRotation;
};

}

#endif
