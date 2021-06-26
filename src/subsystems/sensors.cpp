#include "main.h"

namespace sensors {

#define FLYWHEEL_THRESHOLD 250 // 2800
#define EJECTOR_THRESHOLD 10 // 2850

#define BLUE 180
#define RED 25

//ADIAnalogIn flywheel_sensor('e');
//ADIAnalogIn ejector_sensor('f');
Optical flywheel_sensor(19);
Distance ejector_sensor(17);
Optical color(20);

void init() {
	color.set_led_pwm(100);
	flywheel_sensor.set_led_pwm(100);
}

bool flywheelDetect() {
	//return (flywheel_sensor.get_value() < FLYWHEEL_THRESHOLD);
	return (flywheel_sensor.get_proximity() > FLYWHEEL_THRESHOLD);
}

bool ejectorDetect() {
	//return (ejector_sensor.get_value() < EJECTOR_THRESHOLD);
	return (ejector_sensor.get() < EJECTOR_THRESHOLD);
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

bool ourColorDetect() {
	if (color.get_proximity() > 250) {

		if (selector::auton > 0)
			return (color.get_hue() <= RED) ? true : false;
		if (selector::auton < 0)
			return (color.get_hue() >= BLUE) ? true : false;
	}
	return false;
}

bool ballDetect() {
	return color.get_proximity() > 250;
}

} // namespace sensors
