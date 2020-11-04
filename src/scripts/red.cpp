#include "main.h"

void red() {
	// auton to pick up ball #1
	chassis::move(28, 50);
  intake::move(100);
  chassis::move(28, 50);
}
