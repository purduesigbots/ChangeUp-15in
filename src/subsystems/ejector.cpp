#include "main.h"

namespace ejector {

okapi::MotorGroup motors = {19};

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	motors.moveVoltage(speed * 120);
}

void opcontrol() {
	static int speed;

	if (master.get_digital(DIGITAL_L1))
		speed = 100;
	else if (master.get_digital(DIGITAL_L2))
		speed = -100;
	else if (master.get_digital(DIGITAL_R1))
		speed = 50;
	else
		speed = 0;

	move(speed);
}

} // namespace ejector
