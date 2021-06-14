#include "main.h"

void waitOnColor(int expiration) {
	int count = 0;
	while (!sensors::colorDetect() && count < expiration) {
		count += 10;
		delay(10);
	}
	if (count < expiration)
		intake::move(-100);
}

void runUntilFull() {
	int count = 0;
	while (!sensors::flywheelDetect() && count < 2000) {
		flywheel::move(50);
		ejector::move(60);
		indexer::move(100);
		count += 10;
		delay(10);
	}
	ejector::move(0);
	flywheel::move(0);
	indexer::move(0);
}

void runUntilFullAsync() {
	Task runUntilFullTask(runUntilFull);
}

void score(int num) {
	int i = 0;
	bool detected = sensors::flywheelDetect();

	flywheel::move(100);
	ejector::move(100);
	indexer::move(60);

	int count = 0;

	while (i < num && count < 1000) {
		count += 10;
		delay(10);
		if (sensors::flywheelDetect()) {
			if (!detected)
				detected = true;
		} else {
			if (detected) {
				detected = false;
				i += 1;
			}
		}
	}
	indexer::move(0);
	delay(75);
	ejector::move(0);
	flywheel::move(0);
}

void stopAll() {
	intake::move(0);
	indexer::move(0);
	flywheel::move(0);
	ejector::move(0);
}

void eject() {
	indexer::move(-20);
	flywheel::move(-80);
	ejector::move(-100);
	intake::move(-100);
}

void runUntilFullReverse() {
	int count = 0;
	while (!sensors::flywheelDetect() && count < 1000) {
		flywheel::move(-50);
		count += 10;
		delay(10);
	}
	flywheel::move(0);
}

void sideSort() {
	intake::move(100);
	indexer::move(100);
	ejector::move(-100);
	flywheel::move(100);

	int count = 0;
	int sensor = 0;

	while (sensor != 3 && count < 5000) {
		if (sensor == 0 && sensors::ejectorDetect()) {
			sensor = 1;
			ejector::move(100);
			chassis::moveAsync(2, 30);
		}
		if (sensor == 1 && sensors::flywheelDetect())
			sensor = 2;
		if (sensor == 2 && sensors::intakeDetect())
			sensor = 3;
		chassis::arcade((count % 500 - 250) / 7, 0);

		count += 10;
		delay(10);
	}

	chassis::arcade(0, 0);

	indexer::move(0);
	ejector::move(0);
	delay(250);
	stopAll();
}

void backUntilIntake() {
	while (!intake::isMoving()) {
		chassis::tank(-20, -20);
		delay(10);
	}
	chassis::tank(0, 0);
}

void backUntilIntakeAsync() {
	Task backUntilIntakeTask(backUntilIntake);
}
