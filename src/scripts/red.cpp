#include "main.h"

void red() {
  for (int i=0; i < 4 ;i++)
  {
    turn(90);
    delay(1000);
  }
  drive(2);
}
