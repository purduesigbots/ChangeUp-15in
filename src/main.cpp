#include "main.h"
#include "selection.h"

pros::Controller controller(CONTROLLER_MASTER);

void initialize() {
  initDrive();
  intake::init();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  switch (autonSelection) {
  case 1:
    blue();
    break;
  case -1:
    red();
    break;
  case 0:
    skills();
    break;
  }
}

void opcontrol() {
  while (true) {
    arcade(controller.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
           controller.get_analog(ANALOG_LEFT_X) * (double)100 / 127);

    delay(20);
  }
}
