#include "main.h"

namespace indexer {

okapi::MotorGroup motors = {19};

std::shared_ptr<okapi::AsyncPositionController<double, double>> controller =
    okapi::AsyncPosControllerBuilder()
        .withMotor(motors)
        .withGains({0.001, 0})
        .build();

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
	else if (master.get_digital(DIGITAL_L2))
		speed = -100;
	else
		speed = 0;

	move(speed);
}

} // namespace indexer
