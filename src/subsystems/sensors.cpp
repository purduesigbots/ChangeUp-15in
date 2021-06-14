#include "main.h"

namespace sensors {

#define FLYWHEEL_THRESHOLD 2800
#define EJECTOR_THRESHOLD 2850

#define BLUE 180
#define RED 25

// ADIAnalogIn flywheel_sensor('e');
Optical flywheel_sensor(19);
// ADIAnalogIn ejector_sensor('f');
Distance ejector_sensor(17);
Optical color(20);

void init() {
	color.set_led_pwm(100);
}

bool flywheelDetect() {
	// return (flywheel_sensor.get_value() < FLYWHEEL_THRESHOLD);
	return (flywheel_sensor.get_proximity() > 100);
}

bool ejectorDetect() {
	// return (ejector_sensor.get_value() < EJECTOR_THRESHOLD);
	return (ejector_sensor.get() < 20);
}

bool intakeDetect() {
	return (color.get_proximity() > 100);
}

bool prox() {
	return color.get_proximity() > 50;
}

bool colorDetect() {
	if (color.get_proximity() > 250) {

		if (selector::auton < 0)
			return (color.get_hue() <= RED) ? true : false;
		if (selector::auton > 0)
			return (color.get_hue() >= BLUE) ? true : false;
	}
	return false;
}

} // namespace sensors
