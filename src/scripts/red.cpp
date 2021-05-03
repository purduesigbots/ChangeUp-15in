#include "main.h"
#include "subsystems/intake.hpp"

void red() {
	// deploy

	chassis::tank(-30, -30);
	delay(500);
	flywheel::move(-100);
	indexer::move(-100);
	intake::move(-100);
	ejector::move(100);
	delay(800);
	intake::move(0);

	chassis::useVelocity = true;

	// first line ball
	runUntilFullAsync();
	intake::move(100);
	chassis::move(58, 100);

	// second line ball
	chassis::move(-14, 30);
	chassis::turnAbsolute(-60, 20);
	chassis::move(23.5, 25);

	// spit balls out
	chassis::move(-20.5, 50);
	chassis::turnAbsolute(-80, 20);
	intake::move(-75);
	indexer::move(-15);
	delay(1000);
	intake::move(0);
	indexer::move(0);

	// score edge goal
	chassis::turnAbsolute(64, 20);
	intake::move(100);
	chassis::move(29, 25);
	delay(200);
	intake::move(0);
	intake::move(-100);
	score(1);
	intake::move(-100);
	chassis::move(-10, 15);
	chassis::move(-27, 55);
	intake::move(0);

	// corner goal ball
	chassis::turnAbsolute(90, 20);
	intake::move(-100);
	indexer::move(-100);
	flywheel::move(-100);
	delay(400);
	indexer::move(0);
	flywheel::move(0);
	chassis::turnAbsolute(138, 20);
	intake::move(100);
	chassis::move(59, 75);
	score(2);
	intake::move(0);
	intake::move(-100);
	chassis::move(-15, 30);
	intake::move(0);

	// align middle home row
	chassis::turnAbsolute(-90, 30);
	chassis::useVelocity = false;
	chassis::tank(-20, -20);
	chassis::useVelocity = true;
	delay(1700);
	chassis::tank(0, 0);
	runUntilFull();
	delay(6000);
	indexer::move(-30);
	flywheel::move(-80);
	ejector::move(-100);
	intake::move(-100);
	chassis::move(64, 75);
	indexer::move(0);
	flywheel::move(0);
	ejector::move(0);
	intake::move(0);
	chassis::turnAbsolute(180, 20);
	indexer::move(0);
	flywheel::move(0);

	// score middle home row
	intake::move(100);
	chassis::move(24, 50);
	delay(500);
	intake::move(0);
	score(1);
	chassis::move(-12, 50);
}
