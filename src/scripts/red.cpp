#include "main.h"

void red() {
	// first line ball
	intake::move(100);
	chassis::move(50, 50);

	// second line ball
	chassis::move(-12, 50);
	chassis::turn(50, 50);
	chassis::move(26, 50);

	// spit balls across
	chassis::move(-12, 50);
	chassis::turnAbsolute(315, 50);
	intake::move(-50);
	delay(1000);
	intake::move(0);

	// descore edge goal
	chassis::turnAbsolute(287, 50);
	intake::move(100);
	chassis::move(35, 40);
	delay(500);
	intake::move(0);

	// outtake edge goal blue ball
	chassis::move(-5, 50);
	chassis::turnAbsolute(287);
	chassis::move(-28, 50);
	intake::move(-50);
	delay(600);
	intake::move(0);

	// corner goal ball
	runUntilFull();
	chassis::turnAbsolute(218, 50);
	intake::move(100);
	chassis::move(56, 50);
	intake::move(0);

	// score corner goal
	chassis::moveAsync(3, 25);
	score(1);
	intake::move(100);
	flywheel::move(100);
	indexer::move(100);
	ejector::move(100);
	while (!sensors::colorDetect())
		delay(20);
	intake::move(0);
	delay(2500);
	flywheel::move(0);
	indexer::move(0);
	ejector::move(0);

	// outtake blue ball
	chassis::move(-24, 50);
	intake::move(-50);
	delay(500);
	intake::move(0);

	// align middle home row
	chassis::turnAbsolute(270, 50);
	chassis::move(-40, 50);
	chassis::turnAbsolute(180, 50);

	// score middle home row
	intake::move(100);
	chassis::move(24, 50);
	delay(250);
	intake::move(0);
	score(1);
	chassis::move(-12, 50);
}
