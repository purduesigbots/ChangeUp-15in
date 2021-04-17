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
	static int speed;

	if (master.get_digital(DIGITAL_L1))
		speed = 100;
	else if (master.get_digital(DIGITAL_R1)) {
		if (sensors::flywheelDetect())
			speed = -10;
		else
			speed = 50;
	} else if (master.get_digital(DIGITAL_L2))
		speed = -40;
	else
		speed = 0;

	move(speed);
}

} // namespace flywheel
