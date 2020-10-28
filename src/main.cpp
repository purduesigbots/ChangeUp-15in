#include "main.h"

pros::Controller master(CONTROLLER_MASTER);

void initialize() {
	// autonomous selector library
	const char* selectorNames[] = {"Front", "Back", "Do Nothing", ""};
	selector::init(360, // hue
	               1,   // default auton
	               selectorNames);

	chassis::init();

	// subsystems
	intake::init();
	ejector::init();
	indexer::init();
	flywheel::init();
}

void disabled() {
}

void competition_initialize() {
}

void autonomous() {
	switch (selector::auton) {
	case -1:
		blue();
		break;
	case 1:
		red();
		break;
	case 0:
		skills();
		break;
	}
}

void opcontrol() {
	while (true) {
		// button to start autonomous for testing
		if (master.get_digital(DIGITAL_LEFT) && !competition::is_connected())
			autonomous();

		// intake
		intake::opcontrol();

		// ejector
		ejector::opcontrol();

		// indexer
		indexer::opcontrol();

		// flywheel
		flywheel::opcontrol();

		// chassis
		chassis::arcade(master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		       master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127);

		delay(20);
	}
}
