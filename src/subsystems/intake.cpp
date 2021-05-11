#include "main.h"

namespace intake {

okapi::MotorGroup motors = {2, -7};
int speed = 0;

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) { // speed from -100 to 100
	intake::speed = speed;
	motors.moveVoltage(speed * 120);
}

} // namespace intake
