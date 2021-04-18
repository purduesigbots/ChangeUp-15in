#include "main.h"

void red()
{
	chassis::useVelocity=true;
	// first line ball
	intake::move(100);
	chassis::move(46);

	// second line ball
	chassis::move(-12);
	chassis::turnAbsolute(-65);
	// delay(2000); //anti collision delay
	chassis::move(22, 35);

	// spit balls out
	chassis::move(-22);
	intake::move(-55);
	delay(1000);
	intake::move(0);

	// score edge goal
	chassis::turnAbsolute(65);
	intake::move(100);
	chassis::move(31, 50);
	delay(500);
	intake::move(0);
	score(1);
	chassis::move(-12);

	// corner goal ball
	runUntilFull();
	chassis::turnAbsolute(142, 50);
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
	delay(1000);
	// while (!sensors::colorDetect())
	// 	delay(20);
	intake::move(0);
	delay(500);
	intake::move(-100);
	delay(1500);
	indexer::move(0);
	ejector::move(0);
	chassis::move(-24, 50);
	intake::move(0);
	flywheel::move(0);
	delay(4000);

	// align middle home row
	chassis::turnAbsolute(270, 50);
	chassis::move(-46, 50);
	chassis::turnAbsolute(180, 50);

	// score middle home row
	intake::move(100);
	chassis::move(24, 50);
	delay(250);
	intake::move(0);
	score(1);
	chassis::move(-12, 50);
	chassis::turn(60);
	chassis::move(20);
}
