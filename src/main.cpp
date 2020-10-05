#include "main.h"
#include "autoSelect/selection.h"

pros::Controller master(CONTROLLER_MASTER);

void initialize() {
	//autonomous selector library
	const char *selectorNames[] = {"Front","Back","Do Nothing",""};
	selector::init(
		360, // hue
		1, // default auton
		selectorNames
	);

	initDrive(
		{-15, -18}, // left motors
		{17, 20}, // right motors
		200, // motor rpm

		273, // ticks per distance unit (default = ft)
		2.3, // ticks per degree

		8, // acceleration slew
		200, // deceleration slew (default = disabled)
		2, // acceleration for arc turns

		.3, // drive kp
		.5, // drive kd
		.8, // turn kp
		3, // turn kd
		.05 // arc kp
	);

	//subsystems
	intake::init();
}

void disabled() {
}

void competition_initialize() {
}

void autonomous() {
	switch (selector::auton) {
	case 1:
		blue();
		break;
	case -1:
		red();
		break;
	case 0:
		skills();
		break;
	}
}

void opcontrol() {
	pros::Motor roller_one (12);
	pros::Motor roller_two (19);
	pros::Motor intake_left (11);
	pros::Motor intake_right (13);
	while (true) {
		// button to start autonomous for testing
		if (master.get_digital(DIGITAL_LEFT) && !competition::is_connected())
			autonomous();

		// intake
		intake::opcontrol();

		// chassis
		arcade(master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		       master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127);

		if (master.get_digital(DIGITAL_R1)) {
			intake_left.move(200);
			intake_right.move(-200);
		} else if (master.get_digital(DIGITAL_R2)) {
			intake_left.move(-200);
			intake_right.move(200);
		} else {
			intake_left.move(0);
			intake_right.move(0);
		}

		if (master.get_digital(DIGITAL_L1)) roller_two.move(200);
		else if (master.get_digital(DIGITAL_L2)) roller_two.move(-200);
		else roller_two.move(0);

		if (master.get_digital(DIGITAL_L1)) roller_one.move(-200);
		else if (master.get_digital(DIGITAL_R1)) roller_one.move(-50);
		else if (master.get_digital(DIGITAL_L2)) roller_one.move(200);
		else roller_one.move(0);


		delay(20);
	}
}
