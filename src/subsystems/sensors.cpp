#include "main.h"

namespace sensors {

#define LINE_THRESHOLD 2880
#define BLUE 210
#define RED 25

ADIAnalogIn line_sensor('e');
Optical color(9);

void init() {
	color.set_led_pwm(100);
}


bool lineDetect() {
	return (line_sensor.get_value() < LINE_THRESHOLD);
}

bool colorDetect() {
	if (selector::auton < 0)
		return (color.get_hue() <= RED) ? true : false;
	else
		return (color.get_hue() >= BLUE) ? true : false;
}

} // namespace sensors
