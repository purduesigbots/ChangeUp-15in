#include "main.h"

pros::Controller master(CONTROLLER_MASTER);
const double tpu = 59;
void initialize() {
	const char* b[] = {"Main", "Cross Block", "Cross Sort", "Wall", ""};
	selector::init(360, 1, b);

	chassis::init({-1, -4	, 7}, {3, 9, -8}, // motors
	              600,              // gearset
	              tpu, 4.75,        // TPU
	              5, // 12          // setle time
	              .5, 1,            // linear/angular thresholds
	              2, 2,             // regular/arc slew
	              5,                // imu port
	              {0, 0, 0},        // encoder ports
	              0,                // expander port
	              10                // joystick threshold
	);

	odom::init(false,
						 0,
						 0,
						 tpu,
						 tpu,
						 false,		// holonomic
						 10				// exit error
	);

	pid::init(false,   // debug output
	          .1, .1,  // linear constants 		 .08, .1
	          1, 6,    // angular contants
	          5, 1,    // linear point constants
	          5, 5,    // angular point constants
	          .05,     // arc kp
	          0,       // dif kp
	          10       // min error
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
		blue(1);
		break;
	case -2:
		blue(2);
		break;
	case -3:
		blue(3);
		break;
	case -4:
		blue_wall(1);
		break;
	case 1:
		red(1);
		break;
	case 2:
		red(2);
		break;
	case 3:
		red(3);
		break;
	case 4:
		red_wall(1);
		break;
	case 0:
		skills();
		break;
	}
}

void opcontrol() {
	bool flywheelBall = false;
	bool ejecting = false;
	//bool sorting = true;
	int ejectCount = 0;
	while (true) {
		// button to start autonomous for testing
		if (master.get_digital(DIGITAL_LEFT) && !competition::is_connected())
			autonomous();

		//if (master.get_digital_new_press(DIGITAL_UP) && !competition::is_connected())
		//	selector::auton *= -1;

		// stop all subsystems
		intake::speed = 0;
		ejector::speed = 0;
		indexer::speed = 0;
		flywheel::speed = 0;

		// intake
		if (master.get_digital(DIGITAL_R1)) {
			intake::speed = 100;
			ejector::speed = 50;
			indexer::speed = 50;
			flywheel::speed = 50;
			if (sensors::flywheelDetect())
				flywheelBall = true;
			if (flywheelBall) {
				// run flywheel backward and the indexer slower if a ball is at the top
				flywheel::speed = -15;
				indexer::speed = 20;
			}
		}

		// outtake and ejector reset
		if (master.get_digital(DIGITAL_R2)) {
			intake::speed = -100;
			ejecting = false;
			ejectCount = 0;
		}

		// score
		if (master.get_digital(DIGITAL_L1)) {
			indexer::speed = 80;
			ejector::speed = 100;
			flywheel::speed = 100;
			flywheelBall = false;
		}

		// manual eject
		if (master.get_digital(DIGITAL_L2)) {
			if (indexer::speed == 0)
				indexer::speed = -25;
			if (flywheel::speed == 0)
				flywheel::speed = -40;
			flywheelBall = false;
			ejector::speed = -100;
		}

		//if (master.get_digital_new_press(DIGITAL_DOWN)) {
		//	sorting = !sorting;
		//	ejecting = false;
		//}

		if (sensors::colorDetect()) {
			ejecting = true;
			indexer::speed = 80;
			ejectCount = 0;
		}
		if (ejecting) {
			ejector::speed = -100;
			ejectCount += 10;
			if (ejectCount >= 100)
				ejector::speed = -100;
		}

		if (ejecting && sensors::ejectorDetect()) {
			ejecting = false;
			ejectCount = 0;
		}

		// deploy
		if (master.get_digital(DIGITAL_X)) {
			intake::speed = -100;
			indexer::speed = -100;
			flywheel::speed = -100;
		}

		// chassis
		double a = 1.5; // lower = linear, higher = cubic; cannot be 0
		double throttleInput = master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127.0;
		double throttleSpeed = a * (pow(throttleInput, 3) / 10000 + throttleInput / a) / (a + 1);
		double turnInput = master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127.0;
		double turnSpeed = a * (pow(turnInput, 3) / 10000 + turnInput / a) / (a + 1);

		chassis::arcade(throttleSpeed, turnSpeed);

		// update subsystems
		intake::move(intake::speed);
		ejector::move(ejector::speed);
		indexer::move(indexer::speed);
		flywheel::move(flywheel::speed);

		delay(10);
	}
}
