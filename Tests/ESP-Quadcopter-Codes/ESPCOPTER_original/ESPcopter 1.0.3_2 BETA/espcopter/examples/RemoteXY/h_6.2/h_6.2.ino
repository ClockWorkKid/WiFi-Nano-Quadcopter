
#define REMOTE_XY_REMOTE
#define NeoPixel

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
  // ESPrainbow();
   
  int red = RemoteXY.rgb_1_r;
  int blue = RemoteXY.rgb_1_b;
  int green =  RemoteXY.rgb_1_g;
   
  for(int i ; i < 12; i++){
    pixels.setPixelColor(i, pixels.Color(red,green,blue));
   }
   pixels.show(); 

   if(RemoteXY.button_1 == 1){  // if button_1 is on do here
   takeOff(500, 10000); //Take off 500 altitude for 25 seconds 
   land();//land 
   }
   
   }else{ // if switch_1 is off do here
   armControl = 0; // close the motors
}
} 
