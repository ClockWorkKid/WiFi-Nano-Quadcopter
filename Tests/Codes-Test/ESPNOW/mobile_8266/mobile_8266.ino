#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t stationAddress[] = {0x5C, 0xCF, 0x7F, 0xB7, 0x22, 0x8E};

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


void print_address(uint8_t* add){
  for(int i = 0; i<6; i++){
    Serial.print(add[i], HEX);
    Serial.print(" ");
  }
}

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

  Serial.print("Msg Source: ");
  print_address(mac);
  Serial.println();
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
