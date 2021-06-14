#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "okapi/api.hpp"

namespace intake {

extern okapi::MotorGroup motors;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>>
    controller;
void init();
void move(int speed);
bool isMoving();
void opcontrol();

} // namespace intake

#endif
