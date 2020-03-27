#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "okapi/api.hpp"

namespace intake{

extern okapi::MotorGroup motors;
void init();
void move();
void opcontrol();

}

#endif
