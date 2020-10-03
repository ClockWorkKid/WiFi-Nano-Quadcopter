

#define REMOTE_XY_REMOTE
#define AntiCollision 

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

    
     if(RemoteXY.button_2 == 1){
     if(DistanceY1 > 500){
     SetPointOpt[1] = -15;
      esp.buzzer(0);
     }else{
     SetPointOpt[1] = 10;
     esp.buzzer(1);
     }
     }else if(RemoteXY.button_3 == 1){
     if(DistanceY0 > 500){
     SetPointOpt[1] = 15;
      esp.buzzer(0);
     }else{
      esp.buzzer(1);
      SetPointOpt[1] = -10;
     }
     }else{
     SetPointOpt[1] = 0;
     }
    
  
    if(RemoteXY.button_4 == 1){
    if(DistanceX0 > 500){
    SetPointOpt[0] = 15;
    esp.buzzer(0);
    }else{
   SetPointOpt[0] = -10;
    esp.buzzer(1);
    }
    }else if(RemoteXY.button_5 == 1){
    if( DistanceX1 > 500){
    SetPointOpt[0] = -15;
    esp.buzzer(0);
    }else{
    SetPointOpt[0] = +10;
    esp.buzzer(0);
    }
    }else{
    SetPointOpt[0] = 0;
   }
  
  takeOff(500, 30000); //Take off 500 altitude for 25 seconds 
  land();//land 

   }else{ // if switch_1 is off do here
   armControl = 0; // close the motors
}
} 
