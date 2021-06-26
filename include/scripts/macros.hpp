#ifndef _MACROS_HPP_
#define _MACROS_HPP_

void waitOnColor(int expiration);
void waitOnOurColor(int expiration);
void runUntilFull(int flywheelSpeed = 70);
void runUntilFullReverse();
void runUntilFullAsync();
void score(int num = 1);
void stopAll();
void eject();
void autoSort(int num);

#endif
