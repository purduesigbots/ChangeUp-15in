#include "main.h"
#include "sensors.hpp"

namespace indexer {

okapi::MotorGroup motors = {-10};
int speed = 0;

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	indexer::speed = speed;
	motors.moveVelocity(speed * 2);
}

} // namespace indexer
