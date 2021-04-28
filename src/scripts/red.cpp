#include "main.h"
#include "subsystems/intake.hpp"

void red() {
	chassis::useVelocity = true;

	// deploy
	flywheel::move(-100);
	intake::move(-100);
	ejector::move(100);
	delay(500);
	flywheel::move(0);
	intake::move(0);
	ejector::move(0);

	// first line ball
	intake::move(100);
	chassis::move(53, 55);

	// second line ball
	chassis::move(-13, 30);
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
	chassis::turnAbsolute(63.7, 20);
	intake::move(100);
	chassis::move(29, 50);
	delay(200);
	intake::move(0);
	intake::move(-100);
	score(1);
	intake::move(-100);
	chassis::move(-37, 50);
	intake::move(0);

	// corner goal ball
	chassis::turnAbsolute(90, 20);
	intake::move(-100);
	indexer::move(-100);
	flywheel::move(-100);
	delay(400);
	indexer::move(0);
	flywheel::move(0);
	chassis::turnAbsolute(137, 20);
	intake::move(100);
	chassis::move(59, 50);
	score(2);
	intake::move(0);
	intake::move(-100);
	chassis::move(-15, 30);
	intake::move(0);

	// align middle home row
	chassis::turnAbsolute(-90, 30);
	chassis::useVelocity = false;
	chassis::move(-12, 20);
	chassis::useVelocity = true;
	runUntilFull();
	delay(6000);
	indexer::move(-30);
	flywheel::move(-80);
	ejector::move(-100);
	chassis::move(65.3, 50);
	indexer::move(0);
	flywheel::move(0);
	ejector::move(0);
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
