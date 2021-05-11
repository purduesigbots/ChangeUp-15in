#include "main.h"

pros::Controller master(CONTROLLER_MASTER);
const double tpu = 59;
void initialize() {
	selector::init(360, 1);

	chassis::init({-1, -3}, {4, 6}, // motors
	              600,              // gearset
	              tpu, 4.75,        // TPU
	              12,               // setle time
	              .5, 1,            // linear/angular thresholds
	              2, 2,             // regular/arc slew
	              5,                // imu port
	              {0, 0, 0},        // encoder ports
	              0,                // expander port
	              10                // joystick threshold
	);

	pid::init(false,   // debug output
	          .08, .1, // linear constants
	          1, 6,    // angular contants
	          0, 0,    // linear point constants
	          0, 0,    // angular point constants
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
	bool flywheelBall = false;
	int ejectBalls = 0;
	int ejectCount = 0;
	while (true) {
		// button to start autonomous for testing
		if (master.get_digital(DIGITAL_LEFT) && !competition::is_connected())
			autonomous();

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
			ejectCount = 0;
			ejectBalls = 0;
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

		// auto eject
		if (sensors::colorDetect()) {
			indexer::speed = 80;
			if (ejectBalls == 0)
				ejectBalls = 1;
			else if (ejectCount > 0)
				ejectBalls = 2;
		}
		if (sensors::ejectorDetect() && ejectCount == 0) {
			ejectBalls--;
			ejectCount = 80;
		}
		if (ejectCount > 0)
			ejectCount -= 10;
		if (ejectBalls > 0 || ejectCount > 0)
			ejector::speed = -100;

		// deploy
		if (master.get_digital(DIGITAL_X)) {
			intake::speed = -100;
			indexer::speed = -100;
			flywheel::speed = -100;
		}

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

		// update subsystems
		intake::move(intake::speed);
		ejector::move(ejector::speed);
		indexer::move(indexer::speed);
		flywheel::move(flywheel::speed);

		delay(10);
	}
}
