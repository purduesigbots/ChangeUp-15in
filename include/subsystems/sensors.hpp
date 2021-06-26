#ifndef _SENSORS_H_
#define _SENSORS_H_

namespace sensors {

void init();
bool flywheelDetect();
bool ejectorDetect();
bool colorDetect();
bool ourColorDetect();
bool ballDetect();

} // namespace sensors

#endif
