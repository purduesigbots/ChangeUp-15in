#include "main.h"

namespace indexer {

okapi::MotorGroup motors = {-14};

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
	static bool detected = false;

	if (sensors::colorDetect())
		speed = 100;
	else if (master.get_digital(DIGITAL_L1)) // score ball
		speed = 100;
	else if (master.get_digital(DIGITAL_L2)) // outtake
		speed = 50;
	else if (master.get_digital(DIGITAL_R1)) // run until dectected
		speed = 50;
	else
		speed = 0;

	move(speed);
}

} // namespace indexer
