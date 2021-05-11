#ifndef _FLYWHEEL_H_
#define _FLYWHEEL_H_

#include "okapi/api.hpp"

namespace flywheel {

extern okapi::MotorGroup motors;
extern int speed;
void init();
void move(int speed);

} // namespace flywheel

#endif
