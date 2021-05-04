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
	while (!sensors::flywheelDetect() && count < 1000) {
		flywheel::move(70);
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
	indexer::move(-30);
	flywheel::move(-80);
	ejector::move(-100);
	intake::move(-100);
}
