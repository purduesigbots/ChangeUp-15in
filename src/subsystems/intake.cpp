#include "main.h"

namespace intake {

okapi::MotorGroup motors = {-13, 11};

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) { // speed from -100 to 100
	motors.moveVoltage(speed * 120);
}

void opcontrol() {
	static int speed;

	if (master.get_digital(DIGITAL_R1))
		speed = 100;
	else if (master.get_digital(DIGITAL_R2))
		speed = -100;
	else
		speed = 0;

	move(speed);
}

} // namespace intake
