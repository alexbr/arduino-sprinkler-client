#ifndef main_h_
#define main_h_

#include <Arduino.h>

#define TRIGGER_PIN_IN 2 // For sprinkler trigger

// Main loop functions
void checkTrigger();

// Helpers
bool connect();
void printString(const char *str);
void printStringLn(const char *str);
void printStringP(const char *str);
void printStringLnP(const char *str);

#endif