#include "main.h"
#include "sensors.hpp"

namespace indexer {

okapi::MotorGroup motors = {-10};

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	motors.moveVelocity(speed * 2);
}

void opcontrol() {
	static int speed;
	static bool detected = false;

	speed = 0;

	if (master.get_digital(DIGITAL_L2)) // outtake
		speed = -25;
	if (master.get_digital(DIGITAL_R1)) {
		if (sensors::flywheelDetect())
			speed = 20;
		else
			speed = 50;
	}
	if (master.get_digital(DIGITAL_L1)) // score ball
		speed = 80;
	if (sensors::colorDetect())
		speed = 80;

	move(speed);
}

} // namespace indexer
