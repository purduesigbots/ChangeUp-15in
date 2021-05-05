#include "ARMS/chassis.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/intake.hpp"
#include "subsystems/sensors.hpp"

void red() {

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

	// align mwith wall and wait
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
