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
  { 255,5,0,0,0,78,0,8,13,0,
  2,0,9,6,29,17,2,26,31,31,
  79,78,0,79,70,70,0,1,0,61,
  40,22,22,2,31,109,97,118,105,0,
  1,0,11,31,22,22,2,31,85,195,
  167,0,1,0,74,16,21,21,2,31,
  121,101,115,105,108,0,1,0,48,16,
  21,21,2,31,107,196,177,114,109,196,
  177,122,196,177,0 }; 
   
// this structure defines all the variables of your control interface  
struct { 

    // input variable
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t button_2; // =1 if button pressed, else =0 
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_3; // =1 if button pressed, else =0 
  uint8_t button_4; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 
