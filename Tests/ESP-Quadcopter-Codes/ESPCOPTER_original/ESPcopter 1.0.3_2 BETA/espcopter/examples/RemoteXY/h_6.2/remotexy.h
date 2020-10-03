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
  { 255,5,0,0,0,40,0,8,13,0,
  2,0,9,6,29,17,2,26,31,31,
  79,78,0,79,70,70,0,1,0,11,
  31,22,22,2,31,85,195,167,0,6,
  0,55,17,35,35,2,26 }; 
   
// this structure defines all the variables of your control interface  
struct { 

    // input variable
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t rgb_1_r; // =0..255 Red color value 
  uint8_t rgb_1_g; // =0..255 Green color value 
  uint8_t rgb_1_b; // =0..255 Blue color value 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 
