#include "main.h"

pros::Controller master(CONTROLLER_MASTER);

void initialize() {
	selector::init();

	chassis::init({-15, -18}, {17, 19}, // motors
	              600,                  // gearset
	              45, 4.75,             // TPU
	              12,                   // setle time
	              6, 5,                 // linear/angular thresholds
	              2, 2,                 // regular/arc slew
	              16,                   // imu port
	              {1, 3, 0},            // encoder ports
	              0,                    // expander port
	              10                    // joystick threshold
	);
	odom::init(false, // debug output
	           7.825, // left/right distance
	           7.825, // middle distance
	           69.44, // left/right tpi
	           69.44, // middle tpi
	           true,  // holonomic enabled
	           2      // exit error

	);
	pid::init(false,  // debug output
	          .3, .5, // linear constants
	          1.4, 3, // angular contants
	          4, 0,   // linear point constants
	          50, 0,  // angular point constants
	          .05,    // arc kp
	          .5,     // dif kp
	          10      // min error
	);

	chassis::init({-15, -18}, // Left motors
	              {17, 19},   // Right motors
	              200,        // gearset
	              45.0,       // distance constant
	              4.75,       // degree constant
	              3,          // acccel, step
	              2,          // arc step
	              .2, .75,    // linear kp, kd
	              1, 6,       // turn kp, kd
	              .05,        // arc kp
	              1,          // dif kp
	              0,          // IMU port
	              {1, 3, 0},  // encoder ports
	              0);         // expander port

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
