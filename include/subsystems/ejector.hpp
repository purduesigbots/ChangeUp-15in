#ifndef _EJECTOR_H_
#define _EJECTOR_H_

#include "okapi/api.hpp"

namespace ejector {

extern okapi::MotorGroup motors;
extern int speed;
void init();
void move(int speed);

} // namespace ejector

#endif
