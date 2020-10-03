
#define standalone

#include <espcopter.h> // library
#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

int ledCondition = 0;
void repeatMe() {
    if(ledCondition == 1){
      ledCondition=0;
      esp.greenLed_Digital(ledCondition);
    }else{
      ledCondition=1;
      esp.greenLed_Digital(ledCondition);
    }
    
}

void setup() {
  mainSetup();
  timer.setInterval(1000, repeatMe);
}

void loop() {
    mainLoop();  // main flying loop
    timer.run();
} 