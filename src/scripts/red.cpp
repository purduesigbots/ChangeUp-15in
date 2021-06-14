#include "ARMS/chassis.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/intake.hpp"
#include "subsystems/sensors.hpp"

void red() {
	// Store timestamp at beginning of auton for use in last section
	int start = millis();

	// drive to ball while deploying
	chassis::moveAsync(48, 50);
	intake::move(-100);
	indexer::move(-100);
	flywheel::move(-100);
	delay(500);

	// index preload and eject ball on line
	stopAll();
	intake::move(100);
	runUntilFull();
	indexer::move(50);
	ejector::move(-100);
	chassis::waitUntilSettled();

	// back up, turn, and grab center ball
	stopAll();
	chassis::move(-24, 50);
	chassis::turnAbsolute(-45, 50);
	intake::move(100);
	chassis::move(33, 50);
	stopAll();
	chassis::move(-33, 50);

	// turn and spit out center ball and face goal
	chassis::turnAbsolute(180, 50);
	intake::move(-100);
	delay(400);
	chassis::turnAbsolute(140, 50);
	stopAll();

	// drive to corner goal and cycle
	intake::move(100);
	chassis::move(38, 75);

	// score corner
	indexer::move(100);
	flywheel::move(100);
	waitOnColor(2000);
	intake::move(0);
	delay(300);
	stopAll();

	// back up and remove blue ball
	intake::move(-100);
	chassis::moveAsync(-48, 30);
	delay(350);
	flywheel::move(100);
	chassis::waitUntilSettled();
	stopAll();

	// turn and drive to side goal
	chassis::turnAbsolute(60, 50);
	intake::move(100);
	ejector::move(-100);
	chassis::move(34, 30);
	sideSort();

	// wait until last second and back up
	while (millis() - start < 43500)
		delay(10);
	chassis::setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	intake::move(-50);
	chassis::move(-20, 100);
}

void red_old() {
	// deploy
	chassis::tank(-20, -20);
	delay(500);
	flywheel::move(-100);
	indexer::move(-100);
	intake::move(-100);
	delay(800);
	intake::move(0);

	// first line ball
	runUntilFullAsync();
	intake::move(100);
	chassis::move(60, 50);

	// spit at second line ball
	chassis::move(-13, 30);
	chassis::turnAbsolute(-60, 50);
	intake::move(-60);
	delay(1200);

	// align with corner
	chassis::turnAbsolute(154, 50);
	intake::move(100);
	chassis::fast(25, 75);
	chassis::move(27, 40);

	// score corner
	indexer::move(100);
	flywheel::move(100);
	waitOnColor(2000);
	intake::move(0);
	delay(300);
	stopAll();
	intake::move(-100);
	chassis::move(-18, 30);
	intake::move(0);

	// align with wall and wait
	chassis::turnAbsolute(-90, 50);
	chassis::tank(-20, -20);
	delay(2500);
	chassis::tank(0, 0);
	flywheel::move(100);
	indexer::move(100);
	ejector::move(100);
	intake::move(-100);

	// drive to middle goal
	chassis::move(62, 75);
	stopAll();
	chassis::turnAbsolute(180, 50);

	// score middle home row
	intake::move(100);
	indexer::move(60);
	chassis::move(26, 25);
	waitOnColor(2000);
	runUntilFull();
	stopAll();

	// align with edge goal
	chassis::move(-10, 50);
	chassis::turnAbsolute(80, 50);
	eject();
	intake::move(0);
	flywheel::move(0);
	chassis::move(69);
	stopAll();

	// poke
	chassis::turnAbsolute(7);
	chassis::move(27);
	chassis::arcLeft(-1000, .7);

	// run the ball back for better exit velocity
	flywheel::move(-30);
	delay(100);

	// shoot
	chassis::tank(100, 100);
	delay(150);
	flywheel::move(100);
	delay(400);

	chassis::move(-6);
}

void red_unused() {

	// deploy
	chassis::tank(-20, -20);
	delay(500);
	flywheel::move(-100);
	indexer::move(-100);
	intake::move(-100);
	delay(800);
	intake::move(0);

	// first line ball
	runUntilFullAsync();
	intake::move(100);
	chassis::move(60, 50);

	// second line ball
	chassis::move(-13, 30);
	chassis::turnAbsolute(-65, 50);
	chassis::move(22, 25);

	// spit balls out
	chassis::move(-18, 50);
	chassis::turnAbsolute(-90, 50);
	intake::move(-50);
	indexer::move(-15);
	delay(1000);
	intake::move(0);
	indexer::move(0);

	// score edge goal
	chassis::turnAbsolute(64.5, 50);
	flywheel::move(-30); // roll the red ball back a little
	intake::move(100);
	indexer::move(60);
	chassis::move(27, 25);
	waitOnColor(2000);
	chassis::tank(20, 20);
	delay(300);
	score(1);
	delay(800);
	chassis::fast(-5, 20);
	chassis::move(-30, 75);
	intake::move(0);

	// eject blue
	eject();
	delay(1000);
	stopAll();

	// corner goal
	chassis::turnAbsolute(137, 50);
	intake::move(100);
	chassis::move(59, 50);
	score(2);
	intake::move(-100);
	chassis::move(-18, 30);
	intake::move(0);

	// align with wall and wait
	chassis::turnAbsolute(-90, 50);
	chassis::tank(-20, -20);
	delay(2000);
	chassis::tank(0, 0);
	runUntilFull();

	// eject ball
	eject();

	// drive to middle goal
	chassis::move(62, 75);
	stopAll();
	chassis::turnAbsolute(180, 50);

	// score middle home row
	intake::move(100);
	indexer::move(60);
	chassis::move(26, 25);
	waitOnColor(2000);
	score(1);

	// put bot in the middle of the field for driver control
	chassis::move(-10, 50);
	chassis::turnAbsolute(305, 50);
	chassis::move(36);
	eject();
	delay(3000);
}
