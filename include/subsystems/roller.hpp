#ifndef _ROLLER_H_
#define _ROLLER_H_

#include "okapi/api.hpp"

namespace roller{

extern okapi::MotorGroup motors;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> controller;
void init();
void move(int speed);
void opcontrol();

}

#endif
