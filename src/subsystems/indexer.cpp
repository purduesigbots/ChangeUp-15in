#include "main.h"

namespace indexer {

okapi::MotorGroup motors = {-10};

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

	speed = 0;

	if (master.get_digital(DIGITAL_L2)) // outtake
		speed = -25;
	if (master.get_digital(DIGITAL_R1)) // run until dectected
		speed = 50;
	if (master.get_digital(DIGITAL_L1)) // score ball
		speed = 75;
	if (sensors::colorDetect())
		speed = 100;

	move(speed);
}

} // namespace indexer
