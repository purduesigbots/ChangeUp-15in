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

void runUntilFull(int flywheelSpeed = 70) {
	int count = 0;
	while (!sensors::flywheelDetect() && count < 1000) {
		flywheel::move(flywheelSpeed);
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
	Task([](){
		runUntilFull(50);
		while(1) delay(20);
	});
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
	indexer::move(20);
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

void autoSort(int balls) {
	intake::move(100);
	indexer::move(60);
	flywheel::move(100);
	ejector::move(100);

	int count = 0;
	int ballCount = 0;
	bool ejecting = false;
	bool detect = false;

	while (count < 2000 * balls && (ballCount < balls || ejecting)) {
		if (sensors::ballDetect() && !detect) {
			ballCount++;
		}
		detect = sensors::ballDetect();
		if (sensors::colorDetect() && !ejecting) {
			ejector::move(-80);
			ejecting = true;
		}
		if (ejecting && sensors::ejectorDetect()) {
			ejecting = false;
			ejector::move(100);
		}
		if (ballCount >= balls)
			count = 0;

		chassis::arcade(count < 500 ? 30 : ((count % 500 - 250) / 8), 0);

		delay(10);
		count += 10;
	}

	chassis::arcade(20, 0);
	intake::move(-100);
	delay(1000);

	chassis::arcade(0, 0);
	stopAll();
}
