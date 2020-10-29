#include "main.h"

void red() {
  // auton to pick up ball #1
  chassis::fast(24, 50);
  intake::move(100);
  chassis::move(12, 25);
}
