#include "main.h"
#include "subsystems/intake.hpp"

void red() {
	chassis::useVelocity = true;
	// first line ball
	intake::move(120);
	chassis::move(48, 55);

	// second line ball
	chassis::move(-10, 30);
	chassis::turnAbsolute(-64, 20);
	chassis::move(24, 25);

	// spit balls out
	chassis::move(-24, 50);
	chassis::turnAbsolute(-80, 20);
	intake::move(-100);
	indexer::move(-15);
	delay(1000);
	intake::move(0);
	indexer::move(0);

	// score edge goal
	chassis::turnAbsolute(62, 20);
	intake::move(100);
	chassis::move(28, 50);
	delay(500);
	intake::move(0);
	score(1);
	chassis::move(-36, 50);

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
	chassis::move(53, 50);
	score(2);
	intake::move(0);
	chassis::move(-20, 30);

	// align middle home row
	chassis::turnAbsolute(90, 20);
	delay(8000);
	intake::move(-100);
	indexer::move(-100);
	flywheel::move(-100);
	chassis::move(-50, 50);
	chassis::turnAbsolute(180, 20);
	indexer::move(0);
	flywheel::move(0);
	/*
	  // score middle home row
	  intake::move(100);
	  chassis::move(24, 50);
	  score(1);
	  intake::move(0);
	  chassis::move(-12, 50);
	    */
}
