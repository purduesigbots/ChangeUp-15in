#include "main.h"

void red() {
	// auton to pick up ball #1
	chassis::move(28, 50);
  intake::move(100);
  chassis::move(28, 50);

	chassis::arcRight(-2000, .5, 50);

	chassis::move(30, 50);
	chassis::move(-12, 50);

	chassis::turn(135, 50);
}
