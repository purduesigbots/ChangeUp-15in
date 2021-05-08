#ifndef _INDEXER_H_
#define _INDEXER_H_

#include "okapi/api.hpp"

namespace indexer {

extern okapi::MotorGroup motors;
extern int speed;
void init();
void move(int speed);

} // namespace indexer

#endif
