/******************************************************************************************************
 * https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/

----------------------------------------esp_now_init()-------------------------------------------------

  Initializes ESP-NOW. You must initialize Wi-Fi before initializing ESP-NOW. Returns 0, if succeed.
  

---------esp_now_add_peer(uint8 mac_addr, uint8 role, uint8 channel, uint8 key, uint8 key_len)---------

  Call this function to pair a device.
  
------------------------esp_now_send(uint8 mac_address, uint8 data, int len)---------------------------

  Send data with ESP-NOW.

-------------------------------------esp_now_register_send_cb()----------------------------------------

  Register a callback function that is triggered upon sending data. When a message is sent, 
  a function is called – this function returns whether the delivery was successful or not.

--------------------------------------esp_now_register_rcv_cb()----------------------------------------

  Register a callback function that is triggered upon receiving data. When data is received 
  via ESP-NOW, a function is called.
  
******************************************************************************************************/

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/


#include <esp_now.h>
#include <WiFi.h>


// REPLACE WITH RECEIVER MAC Address
uint8_t droneAddress[] = {0x84, 0xF3, 0xEB, 0x5A, 0x73, 0xA2};


// Receive data structure
typedef struct drone_message {
  String message;
  float battery;
  unsigned long time_alive;
  float pose[7];
} drone_message;


// Send data structure
typedef struct command_message {
  String message;
  float target_pos[3];
  uint8_t station_clock[2];
} command_message;


// Create a drone_message called myData
drone_message droneData;
command_message commandData;


unsigned long beginTime;
unsigned long lastTime = 0;  
unsigned long timerDelay = 1000;  // send commands timer

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  
  if (status != ESP_NOW_SEND_SUCCESS){
    Serial.println("Delivery fail");
  }
  
}

// Callback function that will be executed when data is received
//void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
void OnDataRecv(const unsigned char* mac, const unsigned char* incomingData, int len) {
  
  memcpy(&droneData, incomingData, sizeof(droneData));

  Serial.print("Message Received: ");
  Serial.println(droneData.message);
  Serial.print("Battery Voltage: ");
  Serial.println(droneData.battery);
  Serial.print("Alive Time: ");
  Serial.println(droneData.time_alive);
  Serial.println();
}
 
void setup() {
  
  beginTime = millis();
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for
  // sendCB to get the status of Trasnmitted packet
  // recvCB to get recv packer info
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, droneAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
}


void loop() {
  
  unsigned long currentTime = millis();
  
  if ((currentTime - lastTime) > timerDelay) {
    // Set values to send

    commandData.message = "Standby";
    
    commandData.target_pos[0] = random(-5, 5);
    commandData.target_pos[1] = random(-5, 5);
    commandData.target_pos[2] = random(-5, 5);
    
    commandData.station_clock[0] = floor(((currentTime - beginTime)/1000)/60.0);
    commandData.station_clock[1] = ((currentTime - beginTime)/1000) % 60;

    // Send message via ESP-NOW
    esp_now_send(droneAddress, (uint8_t *) &commandData, sizeof(commandData));

    lastTime = currentTime;
  }
}
