#include "main.h"

pros::Controller master(CONTROLLER_MASTER);

void initialize() {
	// autonomous selector library
	selector::init();

	chassis::init({-15, -18},  //Left motors
	          {17,20},  //Right motors
	          600, // gearset
						59,  //distance constant
	          4.75,  //degree constant
	          3, //acccel, step
						2, //arc step
	          .2, .75,  //linear kp, kd
	          2, 7,  //turn kp, kd
	          .05, //arc kp
						.05, //dif kp
						16,  //IMU port
	          {0, 0, 0},  //encoder ports
	          0);  //expander port

	// subsystems
	intake::init();
	ejector::init();
	indexer::init();
	flywheel::init();
	sensors::init();
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

		printf("%.2f \n", chassis::position());

		delay(20);
	}
}
