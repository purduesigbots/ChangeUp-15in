#include "main.h"

void red() {
	// auton to pick up ball #1

	//commented for testing/tuning turn function
	intake::move(100);
	chassis::move(50, 50);

	chassis::move(-12, 50);

	chassis::turn(50, 50);

	chassis::move(26, 50);
	chassis::move(-12, 50);

	chassis::turnAbsolute(179, 50);

	intake::move(-50);
	delay(1000);
	intake::move(0);

	chassis::turn(38, 50);

	intake::move(100);
	chassis::move(56, 50);

	chassis::moveAsync(3, 25);

	score(2);
	chassis::voltage(100, -50);
	score(1);
	intake::move(0);

	chassis::move(-24, 50);

	intake::move(-50);
	delay(250);
	intake::move(0);




	//chassis::turn(90, 50); turn testing line
}
