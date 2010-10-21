#ifndef INTERACTION_HPP
#define INTERACTION_HPP

enum Interaction {
	// The player sets a new target for HIS submarine.
	// Additional data:
	// [float(target_x), float(target_y)]
	INTERACTION_SETSUBMARINETARGET = 0x0101
};

#endif // INTERACTION_HPP
