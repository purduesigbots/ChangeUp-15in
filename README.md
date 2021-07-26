# BLRS Template
![PROS Project CI](https://github.com/Marsgate/blrs_template/workflows/PROS%20Project%20CI/badge.svg?branch=master)
### Introduction
This project is a starting point for all software sub-teams.
It allows us to have a common code base to work from, speed up trouble shooting,
and reduce the prerequisite knowledge required to create
consistent autonomous programs.

## Libraries
In order to reduce the amount of redundant code between the robots,
we packaged the most important stuff into libraries for easy reuse.

### ARMS
This library includes the autoSelector and Greenhat (now just called ARMS)
all future work is done [here](https://github.com/purduesigbots/ARMS).

### Greenhat
This library handles chassis movement.
Any function that moves the robot around the field will be controlled by functions
located in this library. Documentation for it can be found [here](https://github.com/Marsgate/greenhatlib).
This library was developed by Micah Rassi.

### autoSelector
This library handles the selection of the autonomous program for matches,
hence the name. It creates a graphical menu on the brain's display to allow easy
selection between the multiple autonomous programs. Documentation for it can be
found [here](https://github.com/kunwarsahni01/Vex-Autonomous-Selector). This library was developed by Kunwar Sahni.

## Project Structure
The project structure is focused around dividing the subsystems and autons into
separate files. The `main.cpp` should contain little actual code.

### Subsystems
The subsystems folder contains one file for each subsystem. The general template
for subsystems should follow this pattern:
```
#include "main.h"

namespace intake{

okapi::MotorGroup motors = {5,-6};

void init() {
  motors.setGearing(okapi::AbstractMotor::gearset::green);
  motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move (int speed) {
  motors.moveVoltage(speed*120);
}

void opcontrol() {
  static int speed;

  if(master.get_digital(DIGITAL_R1))
    speed = 100;
  else if(master.get_digital(DIGITAL_R2))
    speed = -100;
  else
    speed = 0;

  move(speed);
}

} //namespace intake
```

The entire subsystem is placed into a unique namespace to allow a general naming
convention to be applied to each subsystem.

The motors (or singular motor) are declared using okapi. We use okapi
because of it's native support for motor groups, which allow for more compact and
readable autonomous programs.

The `init()` function should be called from main.cpp during robot initialization.
It allows the setting of gearing, brake mode, encoder units, and any other subsystem
specific initialization.

The `move()` function is simply a shorthand for voltage based movement. The function
takes a number between -100 and 100. Which is much easier to use than the regular
`moveVoltage` function.

The `opcontrol()` function utilizes a static variable to keep track of the speed
assigned to the subsystem. This approach can make some tasks easier by storing
the previously assigned motor speed.

### The chassis subsystem
All configuration for the chassis can be done from the file:
`main.cpp`

This is where you can define which ports the drive motors are plugged into and
what internal gearset to use. Negative numbers mean reversed motor
```
{1, 2}, // left motors
{-3, -4}, // right motors
200, // motor rpm
```

Below that are the `distance_constant` and `degree_constant`. These affect how
far the robot moves per unit during auton. When calling the function `drive(1)`
the distance constant defines what `1` is. It can be 1 inch, 1 foot, 1 meter, or
any other measurement you choose. By default, we use feet for simplicity. Just
adjust the value until you achieve the desired movement. The same is true of the
`degree_constant`, which should be tuned to produce a consistent 90 degree turn.

## Writing an autonomous
All autonomous programs are located in the `scripts` folder. By default there
is just `red`, `blue`, and `skills`. The `macros.cpp` file is for putting
reusable pieces of code for common actions. If a block of code is used more than
once, you can often make it a macro. This improves program readability greatly.

### Chassis movement
To start moving the robot around the field, you can use the `drive()` function
and the `turn()` function supplied by Greenhat. The template is
`using namespace greenhat;` by default, so all functions from the library are
available with no prefix. To preform more complicated drive maneuvers, read the
Greenhat documentation linked above.

### Other subsystem movement
Other subsystems can be moved by accessing the move function in their namespace.
```
intake::move(100);
```
The move function takes a value between -100 and 100. It will produce a constant
movement at the given voltage until the command `intake::move(0)` is given.
That means that a delay must be put between the starting and stopping of the movement.
```
intake::move(100);
delay(1000); // delay for 1 second
intake::move(0);
```

This type of time-based movement is good enough for many subsystems, but sometimes
more precision is required. In these cases PID is the best option.
Vex motors have a built-in PID that can be used through the `moveVelocity`, `moveAbsolute`, and `moveRelative` commands.
Here is an example of their usage:
```
intake::motors.moveAbsolute(180); // move 180 degrees
while(intake::motors.getPosition() != 180)
  delay(10); //wait until the motor reaches the target
```
Documentation on how to use the built-in functions can be found [here](https://okapilib.github.io/OkapiLib/classokapi_1_1Motor.html).

But even the built-in PID can often be insufficient. This is where an okapi
async position controller comes in handy. They can be added to a subsystem
following the format in the [documentation](https://okapilib.github.io/OkapiLib/md_docs_api_control.html)
```
std::shared_ptr<okapi::AsyncPositionController<double, double>> controller = okapi::AsyncPosControllerBuilder()
  .withMotor(motors)
  .withGains({0.001, 0})
  .build();
```
The controller can then be utilized with the following syntax:
```
intake::controller->setTarget(180); // move 180 degrees
intake::controller->waitUntilSettled();
```

The setup for this type of controller is a little verbose, but it can be much
more consistent than either time based or the built in PID.

## Code Formatting
The template contains a clang-format according to the [BLRS style guide](https://phabricator.purduesigbots.com/w/wiki/cs/design_pros2/styleguide/)
This can be run by executing the `run-clang-format.sh` bash script and will
automatically adjust all code in the project to follow the proper coding standards.
To make life easier its best to install a clang-format extension to whatever editor
your using. These extensions for [Atom (the PROS Editor)](https://atom.io/packages/clang-format) or [VS Code](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)
will automaticaly format your code to the standard everytime you save.
