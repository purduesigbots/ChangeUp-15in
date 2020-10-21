#include "main.h"

namespace flywheel {

okapi::MotorGroup motors = {-10};
ADIAnalogIn line_sensor('a');

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
	else if (master.get_digital(DIGITAL_R1)) {
		if (line_sensor.get_value() > 1850)
			speed = 50;
		else
			speed = -15;
	} else if (master.get_digital(DIGITAL_L2))
		speed = -100;
	else
		speed = 0;

	move(speed);
}

} // namespace flywheel
