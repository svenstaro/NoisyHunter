#ifndef INTERACTION_HPP
#define INTERACTION_HPP

enum Interaction {
	// The player sets a new target for HIS submarine.
	// Additional data:
	// [float(target_x), float(target_y)]
	INTERACTION_SETSUBMARINETARGET = 0x0101,

	// The player fires a torpedo to the target point.
	// Additional data:
	// [float(target_x), float(target_y), float(time_to_live)]
	INTERACTION_FIRETORPEDO = 0x0102,

	// The player fires a sonar ping to the target point.
	// Additional data:
	// [float(target_x), float(target_y), float(time_to_live)]
	INTERACTION_FIRESONARPING = 0x0103
};

#endif // INTERACTION_HPP
