#include "main.h"

void runUntilFull() {
	while (!sensors::flywheelDetect()) {
		flywheel::move(70);
		ejector::move(60);
		indexer::move(100);
	}
	ejector::move(0);
	flywheel::move(0);
	indexer::move(0);
}

void score(int num) {
	int i = 0;
	bool detected = sensors::flywheelDetect();

	flywheel::move(100);
	ejector::move(100);
	indexer::move(60);

	while (i < num) {
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
