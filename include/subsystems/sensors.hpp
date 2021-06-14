#ifndef _SENSORS_H_
#define _SENSORS_H_

namespace sensors {

void init();
bool flywheelDetect();
bool ejectorDetect();
bool intakeDetect();
bool prox();
bool colorDetect();

} // namespace sensors
#endif
