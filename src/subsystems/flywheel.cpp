#include "main.h"

namespace flywheel {

okapi::MotorGroup motors = {-9};

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	motors.moveVoltage(speed * 120);
}

void opcontrol() {
	static bool detect = false;
	static int speed;

	if (master.get_digital(DIGITAL_L1)) {
		detect = false;
		speed = 100;
	} else if (master.get_digital(DIGITAL_R1)) {
		if (sensors::flywheelDetect()) {
			detect = true;
		}
		if (detect) {
			speed = -15;
		} else {
			speed = 50;
		}
	} else if (master.get_digital(DIGITAL_L2)) {
		detect = false;
		speed = -40;
	} else if (master.get_digital(DIGITAL_X))
		speed = -100;
	else
		speed = 0;

	move(speed);
}

} // namespace flywheel
