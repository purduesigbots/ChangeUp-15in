#include "macros.hpp"
#include "main.h"
#include "subsystems/intake.hpp"
#include "subsystems/sensors.hpp"

void red() {

	// deploy
	chassis::tank(-20, -20);
	delay(300);
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
	chassis::move(23.5, 25);

	// spit balls out
	chassis::move(-19.5, 50);
	chassis::turnAbsolute(-90, 50);
	intake::move(-75);
	indexer::move(-15);
	delay(1000);
	intake::move(0);
	indexer::move(0);

	// score edge goal
	chassis::turnAbsolute(62.5, 50);
	intake::move(100);
	chassis::move(27, 25);
	waitOnColor(2000);
	chassis::tank(20, 20);
	delay(300);
	score(1);
	delay(1000);
	chassis::move(-39, 55);
	intake::move(0);

	// corner goal ball
	chassis::turnAbsolute(90, 100);
	intake::move(-100);
	indexer::move(-100);
	flywheel::move(-100);
	delay(400);
	indexer::move(0);
	flywheel::move(0);
	chassis::turnAbsolute(137, 50);
	intake::move(100);
	chassis::move(59, 50);
	score(2);
	intake::move(-100);
	chassis::move(-18, 30);
	intake::move(0);

	// align mwith wall and wait
	chassis::turnAbsolute(-90, 50);
	chassis::tank(-20, -20);
	delay(2400);
	chassis::tank(0, 0);
	runUntilFull();
	delay(4500);

	// eject ball
	indexer::move(-30);
	flywheel::move(-80);
	ejector::move(-100);
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
	score(1);
	chassis::move(-12, 50);
}
