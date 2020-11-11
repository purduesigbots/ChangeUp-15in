#include "main.h"

void red() {
	// auton to pick up ball #1

	//commented for testing/tuning turn function
	chassis::move(30, 50);
  intake::move(100);
  chassis::move(30, 50);

	chassis::arcRight(-2000, .5, 50);

	chassis::move(34, 50);
	chassis::move(-12, 50);

	chassis::turn(130, 50);

	intake::move(-100);
	delay(1000);
	intake::move(0);

	chassis::turn(41, 50);

	intake::move(100);
	chassis::move(48, 50);
	//chassis::turn(90, 50); turn testing line
}
