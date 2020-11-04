#ifndef _CONFIG_H_
#define _CONFIG_H_

// Drivetrain configuration constants
namespace chassis {

// negative numbers mean reversed motor
#define LEFT_MOTORS -15, -18
#define RIGHT_MOTORS 17, 20
#define GEARSET 200 // rpm of chassis motors

#define DISTANCE_CONSTANT 45.0 // ticks per distance unit, the default is a foot
#define DEGREE_CONSTANT 4.85   // ticks per degree

// slew control (autonomous only)
#define ACCEL_STEP 2   // smaller number = more slew
#define DECCEL_STEP 12 // 200 = no slew
#define ARC_STEP 2     // acceleration for arcs
#define MIN_SPEED 15

// pid constants
#define LINEAR_KP 0.20
#define LINEAR_KD .5
#define TURN_KP .8
#define TURN_KD 3
#define ARC_KP .05
#define DIF_KP 1

// sensors
#define IMU_PORT 0               // port 0 for disabled
#define ENCODER_PORTS 0, 0, 0, 0 // port 0 for disabled

} // namespace chassis

// Auton selector configuration constants
namespace selector {

// Color of theme from 0-359(H part of HSV)
#define HUE 360

// Default auton numbers
#define DEFAULT 1

// Names of autonomi, up to 10
#define AUTONS "Front", "Back", "Do Nothing"

} // namespace selector

#endif
