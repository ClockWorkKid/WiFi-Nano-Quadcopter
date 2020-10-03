/* 
   -- New project -- 
    
   This source code of graphical user interface  
   has been generated automatically by RemoteXY editor. 
   To compile this code using RemoteXY library 2.3.3 or later version  
   download by link http://remotexy.com/en/library/ 
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                    
     - for ANDROID 4.1.1 or later version; 
     - for iOS 1.2.1 or later version; 
     
   This source code is free software; you can redistribute it and/or 
   modify it under the terms of the GNU Lesser General Public 
   License as published by the Free Software Foundation; either 
   version 2.1 of the License, or (at your option) any later version.     
*/ 

////////////////////////////////////////////// 
//        RemoteXY include library          // 
////////////////////////////////////////////// 

// RemoteXY select connection mode and include library  
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h> 

#include <RemoteXY.h> 

// RemoteXY connection settings  
#define REMOTEXY_WIFI_SSID "RemoteXY" 
#define REMOTEXY_WIFI_PASSWORD "12345678" 
#define REMOTEXY_SERVER_PORT 6377 


// RemoteXY configurate   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,5,0,0,0,71,0,8,13,0,
  2,0,9,6,29,17,2,26,31,31,
  79,78,0,79,70,70,0,1,0,57,
  7,21,21,2,31,105,108,101,114,105,
  0,1,0,57,38,22,22,2,31,103,
  101,114,105,0,1,0,39,25,18,18,
  2,31,115,111,108,0,1,0,78,24,
  19,19,2,31,115,97,103,0 }; 
   
// this structure defines all the variables of your control interface  
struct { 

    // input variable
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t button_2; // =1 if button pressed, else =0 
  uint8_t button_3; // =1 if button pressed, else =0 
  uint8_t button_4; // =1 if button pressed, else =0 
  uint8_t button_5; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 
