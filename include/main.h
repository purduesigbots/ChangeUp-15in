#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "ARMS/api.h"
#include "ARMS/chassis.h"

// subsystems
#include "subsystems/ejector.hpp"
#include "subsystems/flywheel.hpp"
#include "subsystems/indexer.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/sensors.hpp"

// scripts
#include "scripts/blue.hpp"
#include "scripts/macros.hpp"
#include "scripts/red.hpp"
#include "scripts/skills.hpp"

using namespace pros;

extern Controller master;

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#endif

#endif // _PROS_MAIN_H_
