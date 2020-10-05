/******************************************************************************************************
 * https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/

----------------------------------------esp_now_init()-------------------------------------------------

  Initializes ESP-NOW. You must initialize Wi-Fi before initializing ESP-NOW. Returns 0, if succeed.
  
-------------------------------------esp_now_set_self_role(role) --------------------------------------

  the role can be:  ESP_NOW_ROLE_IDLE = 0,
                    ESP_NOW_ROLE_CONTROLLER, 
                    ESP_NOW_ROLE_SLAVE, 
                    ESP_NOW_ROLE_COMBO, 
                    ESP_NOW_ROLE_MAX

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
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t stationAddress[] = {0x80, 0x7D, 0x3A, 0xB7, 0x81, 0x54};

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
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  
  if (sendStatus != 0){
    Serial.println("Delivery fail");
  }
  
}

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  
  memcpy(&commandData, incomingData, sizeof(commandData));
  
  Serial.print("Message Received: ");
  Serial.println(commandData.message);
  Serial.print("Target Position: ");
  Serial.print(commandData.target_pos[0]);
  Serial.print(" ");
  Serial.print(commandData.target_pos[1]);
  Serial.print(" ");
  Serial.println(commandData.target_pos[2]);
  Serial.print("Station Time: ");
  Serial.print(commandData.station_clock[0]);
  Serial.print(":");
  Serial.println(commandData.station_clock[1]);
  Serial.println();
}
 
void setup() {

  beginTime = millis();
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for
  // sendCB to get the status of Trasnmitted packet  
  // recvCB to get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  // Register peer
  esp_now_add_peer(stationAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  unsigned long currentTime = millis();
  
  if ((currentTime - lastTime) > timerDelay) {
    // Set values to send

    droneData.message = "Standingby";
    
    droneData.battery = random(1, 10);
    
    droneData.time_alive = (currentTime - beginTime)/1000 ;
    
    droneData.pose[0] = random(-5, 5);
    droneData.pose[1] = random(-5, 5);
    droneData.pose[2] = random(-5, 5);
    droneData.pose[3] = random(-5, 5);
    droneData.pose[4] = random(-5, 5);
    droneData.pose[5] = random(-5, 5);
    droneData.pose[6] = random(-5, 5);
    
    // Send message via ESP-NOW
    esp_now_send(stationAddress, (uint8_t *) &droneData, sizeof(droneData));

    lastTime = currentTime;
  }
}
