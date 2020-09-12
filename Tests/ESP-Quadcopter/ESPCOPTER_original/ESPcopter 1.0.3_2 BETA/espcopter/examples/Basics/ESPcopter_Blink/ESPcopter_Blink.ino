
#define standalone

#include <espcopter.h> // library


void setup() {
  mainSetup(); // main flying setup
  esp.greenLed_Digital(0); 
}

void loop() {
 esp.greenLed_Digital(1); 
 delay(500);
 esp.greenLed_Digital(0); 
 delay(500);
}