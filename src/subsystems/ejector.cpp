#include "main.h"
#include "sensors.hpp"

namespace ejector {

okapi::MotorGroup motors = {-8};

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
	static int eject = 0;
	static int count = 0;
	static bool ejecting = false;

	if (sensors::colorDetect()) {
		if (eject == 0)
			eject = 1;
		else if (ejecting)
			eject = 2;
	}

	if (sensors::ejectorDetect() && eject) {
		ejecting = true;
	}

	if (ejecting)
		count += 10;

	if (count > 80) {
		eject -= 1;
		count = 0;
		ejecting = false;
	}

	if (master.get_digital(DIGITAL_R2)) {
		eject = 0;
		count = 0;
		ejecting = false;
	}

	if (master.get_digital(DIGITAL_L2) || eject) // outtake
		speed = -100;
	else if (master.get_digital(DIGITAL_L1)) // score
		speed = 100;
	else if (master.get_digital(DIGITAL_R1))
		speed = 50;
	else if (master.get_digital(DIGITAL_X))
		speed = 100;
	else
		speed = 0;

	move(speed);
}

} // namespace ejector
