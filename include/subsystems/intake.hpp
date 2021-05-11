#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "okapi/api.hpp"

namespace intake {

extern okapi::MotorGroup motors;
extern int speed;
void init();
void move(int speed);

} // namespace intake

#endif
