#ifndef main_h_
#define main_h_

#include <Arduino.h>

#define TRIGGER_PIN_IN 2 // For sprinkler trigger

void checkTrigger();
bool connect();

#endif