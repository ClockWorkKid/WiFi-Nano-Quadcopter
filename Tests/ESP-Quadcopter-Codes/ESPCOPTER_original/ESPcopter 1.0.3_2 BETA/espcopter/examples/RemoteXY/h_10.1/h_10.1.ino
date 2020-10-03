
/*
 * 
 */
 
 
#define REMOTE_XY_REMOTE
 
#include "remotexy.h"
#include <espcopter.h>

// ************************************************************************************************************************************



void setup() {
  mainSetup();
  Trim_Roll = 0; // -1750, 1750
  Trim_Pitch = 0; // -1750, 1750
  Trim_Yaw = 100;  // -1750, 1750
}

void loop() {
   mainLoop();  // main flying loop
   if(RemoteXY.switch_1 == 1){ // if switch_1 is on do here
   armControl =1;     
   takeOff(500, 10000); //Take off 500 altitude for 25 seconds 
   delay_(5000);
   setAltitude(7500);
   delay_(5000);
   land();//land 
   }else{ // if switch_1 is off do here
   armControl = 0; // close the motors
}
} 
