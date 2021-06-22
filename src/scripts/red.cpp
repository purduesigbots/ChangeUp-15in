#include "ARMS/chassis.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/intake.hpp"
#include "subsystems/sensors.hpp"

void red() {
	// Store timestamp at beginning of auton for use in last section
	int start = millis();

	chassis::resetAngle();

	// drive to ball while deploying
	chassis::moveAsync(46, 40);
	indexer::move(-100);
	flywheel::move(-100);
	delay(250);
	intake::move(-100);
	delay(500);

	// index preload and eject ball on line
	stopAll();
	intake::move(100);
	runUntilFull(40);
	indexer::move(50);
	ejector::move(-100);
	chassis::waitUntilSettled();

	// back up and turn towards center ball
	chassis::move(-22, 50);
	ejector::move(0);
	indexer::move(0);
	chassis::turnAbsoluteAsync(-45, 50);
	flywheel::move(-50);
	chassis::waitUntilSettled();
	flywheel::move(0);

	// grab center ball
	chassis::move(31, 50);
	stopAll();
	chassis::turnAbsoluteAsync(-45, 50);
	chassis::move(-31, 40);

	// turn and spit out center ball and drive to corner goal
	chassis::turnAbsolute(215, 50);
	intake::move(-100);
	indexer::move(-100);
	delay(200);
	for (int i = 0; i < 400; i += 10) {
			indexer::move(sensors::colorDetect() ? -100 : 0);
			delay(10);
	}
	chassis::turnAbsolute(140, 50);
	intake::move(100);
	chassis::move(38, 75);

	// score corner
	indexer::move(100);
	flywheel::move(100);
	ejector::move(100);
	waitOnColor(2000);
	intake::move(0);
	indexer::move(0);
	delay(400);
	stopAll();

	// back up and remove blue ball
	intake::move(-25);
	ejector::move(25);
	chassis::moveAsync(-47, 30);
	delay(500);
	intake::move(-75);
	indexer::move(-100);
	flywheel::move(-50);
	ejector::move(-100);
	chassis::waitUntilSettled();
	stopAll();

	// turn and drive to side goal
	chassis::turnAbsolute(60, 50);
	intake::move(100);
	ejector::move(-100);
	chassis::move(32, 30);
	autoSort(3);

	// back up, turn, and go accross field
	chassis::move(-20, 50);
	chassis::turnAbsolute(-90, 35);
	chassis::arcade(-35, 0);
	delay(2000);
	chassis::arcade(0, 0);

	printf("%d\n", millis() - start);
	// If time is past 35 seconds, don't go across field
	if(millis() - start < 35000) {
		intake::move(100);
		indexer::move(100);
		ejector::move(-100);
		chassis::move(100, 75);

		// turn towards side goal and drive in
		chassis::turnAbsolute(-55, 35);
		intake::move(100);
		chassis::move(30, 40);
		autoSort(3);

		printf("%.2f\n", (double)(millis() - start) / 1000);

		// wait until last second and back up
		while (millis() - start < 43500)
			delay(10);
		intake::move(-50);
		chassis::move(-20, 100);
	}
}

void red_wall() {
	// Store timestamp at beginning of auton for use in last section
	int start = millis();

	chassis::resetAngle();

	// drive to ball while deploying
	chassis::moveAsync(26, 40);
	indexer::move(-100);
	flywheel::move(-100);
	delay(250);
	intake::move(-100);
	delay(500);

	// index preload and wait to stop
	stopAll();
	runUntilFull(25);
	chassis::waitUntilSettled();

	// turn to corner goal
	chassis::turnAbsolute(140, 50);
	intake::move(100);
	chassis::move(38, 75);

	// score corner
	chassis::arcade(25, 0);
	indexer::move(100);
	flywheel::move(100);
	ejector::move(100);
	waitOnColor(2000);
	intake::move(0);
	indexer::move(25);
	delay(200);
	indexer::move(0);
	delay(200);
	stopAll();

	intake::move(-50);
	chassis::move(-49, 30);
	stopAll();

	// turn and remove blue ball
	chassis::turnAbsolute(120, 50);
	intake::move(-50);
	indexer::move(-100);
	flywheel::move(-50);
	ejector::move(-100);
	delay(1000);
	stopAll();

	// turn and drive to side goal
	chassis::turnAbsolute(60, 50);
	intake::move(100);
	ejector::move(-100);
	chassis::move(32, 30);
	autoSort(3);

	// back up, turn, and align with wall
	chassis::move(-20, 50);
	chassis::turnAbsolute(-90, 35);
	chassis::arcade(-35, 0);
	delay(2000);

	// drive across field
	intake::move(100);
	indexer::move(100);
	ejector::move(-100);
	chassis::move(100, 75);
	stopAll();

	// turn towards side goal and drive in
	chassis::turnAbsolute(-55, 35);
	intake::move(50);
	chassis::move(30, 40);
	intake::move(0);

	// wait until last second and back up
	while (millis() - start < 40000)
		delay(10);
	autoSort(3);
	chassis::move(-20, 100);
}

void red_odom() {
	// Store timestamp at beginning of auton for use in last section
	int start = millis();

	chassis::resetAngle();
	odom::reset();

	// drive to ball while deploying
	odom::moveAsync({48, 0}, 50);
	indexer::move(-100);
	flywheel::move(-100);
	delay(250);
	intake::move(-100);
	delay(500);

	// index preload and eject ball on line
	stopAll();
	intake::move(100);
	runUntilFull(40);
	indexer::move(50);
	ejector::move(-100);
	chassis::waitUntilSettled();

	// back up, turn, and grab center ball
	stopAll();
	odom::move({24, 0}, 50);
	//chassis::turn(odom::getAngleError({48, -28}), 50);
	intake::move(100);
	odom::move({44, -24}, 50);
	stopAll();
	odom::move({24, 0}, 50);

	// turn and spit out center ball and face goal
	chassis::turnAbsolute(215, 50);
	intake::move(-100);
	delay(400);
	chassis::turn(odom::getAngleError({0, 24}), 50);
	stopAll();

	// drive to corner goal and cycle
	intake::move(100);
	odom::moveThru({0, 24});

	// score corner
	indexer::move(100);
	flywheel::move(100);
	waitOnColor(2000);
	intake::move(0);
	delay(300);
	stopAll();

	// back up and remove blue ball
	intake::move(-100);
	chassis::moveAsync(-45, 50);
	delay(350);
	flywheel::move(100);
	chassis::waitUntilSettled();
	stopAll();

	// turn and drive to side goal
	chassis::turnAbsolute(60, 50);
	intake::move(100);
	ejector::move(-100);
	odom::moveThru({48, 30}, 30);
	autoSort(2);

	// back up, turn, and go accross field
	chassis::move(-20, 50);
	chassis::turnAbsolute(-90, 50);
	odom::moveThru({30, -72}, 100);

	// turn towards side goal and drive in
	intake::move(100);
	odom::moveThru({48, 112}, 30);
	autoSort(1);

	printf("%.2f\n", (double)(millis() - start) / 1000);

	// wait until last second and back up
	while (millis() - start < 43500)
		delay(10);
	intake::move(-50);
	chassis::move(-20, 100);
}

void red_2() {
	chassis::resetAngle();
	// deploy
	chassis::tank(-20, -20);
	delay(500);
	flywheel::move(-100);
	indexer::move(-100);
	intake::move(-100);
	delay(800);
	indexer::move(0);

	// first line ball
	intake::move(100);
	chassis::moveAsync(60, 50);
	delay(700);
	runUntilFull(40);

	// eject ball at line
	indexer::move(100);
	ejector::move(-100);
	chassis::waitUntilSettled();

	// back up
	chassis::move(-34, 30);
	indexer::move(0);
	ejector::move(0);
	chassis::turnAbsolute(-45, 50);

	// grab ball by center goal
	chassis::move(37, 50);
	stopAll();
	chassis::move(-15, 50);

	// face corner goal and spit out ball
	chassis::turnAbsolute(180, 50);
	intake::move(-100);
	delay(500);
	stopAll();
	chassis::turnAbsolute(135, 50);

	// move to corner
	intake::move(100);
	chassis::move(60, 50);

	// score corner
	indexer::move(100);
	flywheel::move(100);
	waitOnColor(2000);
	intake::move(0);
	ejector::move(20);
	delay(300);
	stopAll();
	intake::move(-100);

	// back up and shoot out ball
	chassis::moveAsync(-40, 50);
	delay(500);
	flywheel::move(100);
	chassis::waitUntilSettled();
	stopAll();

	// face and drive into edge goal
	chassis::turnAbsolute(45, 50);
	intake::move(100);
	chassis::move(35, 50);
	chassis::move(-1, 50);

	// sort edge goal
	autoSort(2);
	intake::move(-100);
	chassis::move(-20);

	stopAll();
}

void red2() {
	chassis::resetAngle();
	// deploy
	chassis::tank(-20, -20);
	delay(500);
	flywheel::move(-100);
	indexer::move(-100);
	intake::move(-100);
	delay(800);
	intake::move(0);
	indexer::move(0);

	// first line ball
	intake::move(100);
	chassis::moveAsync(60, 50);
	delay(700);
	runUntilFullAsync();
	chassis::waitUntilSettled();


	// spit at second line ball
	chassis::move(-13, 30);
	chassis::turnAbsolute(-90, 50);
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
	ejector::move(20);
	delay(300);
	stopAll();
	intake::move(-100);
	chassis::move(-18, 30);
	intake::move(0);

	// align with wall and wait
	chassis::turnAbsolute(-90, 50);
	chassis::tank(-20, -20);
	delay(1800);
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
	runUntilFull(40);
	stopAll();
	flywheel::move(-20);
	delay(80);
	stopAll();

	// align with edge goal
	chassis::move(-10, 50);
	chassis::turnAbsolute(85, 50);
	eject();
	intake::move(0);
	flywheel::move(0);
	chassis::move(69, 50);
	stopAll();

	// poke
	chassis::turnAbsolute(9);
	chassis::move(30);
	chassis::arcLeft(-1000, .7);

	// run the ball back for better exit velocity
	flywheel::move(-30);
	delay(100);

	// shoot
	chassis::tank(100, 100);
	delay(150);
	flywheel::move(100);
	delay(400);

	chassis::move(-15);

	stopAll();
}
