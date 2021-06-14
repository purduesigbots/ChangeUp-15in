#include "main.h"
#include "subsystems/sensors.hpp"

pros::Controller master(CONTROLLER_MASTER);
const double tpu = 59;
void initialize() {
	selector::init(360, 1);

	chassis::init({-1, -4, 7}, {3, -8, 9}, // motors
	              600,                     // gearset
	              tpu, 4.75,               // TPU
	              12,                      // setle time
	              .5, 1,                   // linear/angular thresholds
	              2, 2,                    // regular/arc slew
	              5,                       // imu port
	              {0, 0, 0},               // encoder ports
	              0,                       // expander port
	              10                       // joystick threshold
	);

	pid::init(false,      // debug output
	          .08, 0, .1, // linear constants
	          1, 0, 6,    // angular contants
	          0, 0, 0,    // linear point constants
	          0, 0, 0,    // angular point constants
	          .05,        // arc kp
	          0,          // dif kp
	          10          // min error
	);
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
		// scale turnSpeed with a parabolic function
		double turnInput = master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127.0;
		double turnSpeed = turnInput * 0.09;
		turnSpeed *= turnSpeed;
		turnSpeed += 10;
		if (turnInput < 0)
			turnSpeed *= -1;
		chassis::arcade(master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127.0,
		                turnSpeed);

		// printf("%.2f \n", chassis::position() / tpu);

		delay(20);
	}
}
