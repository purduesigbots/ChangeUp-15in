#include "main.h"

namespace ejector {

okapi::MotorGroup motors = {-19};

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
	static bool eject = false;

	if (sensors::colorDetect())
		eject = true;
	else if (sensors::ejectorDetect())
		eject = false;

	if (master.get_digital(DIGITAL_L2) || eject) // outtake
		speed = -100;
	else if (master.get_digital(DIGITAL_L1)) // score
		speed = 100;
	else if (master.get_digital(DIGITAL_R1)) {
		speed = 50;
	} else
		speed = 0;

	move(speed);
}

} // namespace ejector
