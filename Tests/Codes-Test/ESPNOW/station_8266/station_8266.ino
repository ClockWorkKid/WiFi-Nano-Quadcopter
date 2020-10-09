#include <ESP8266WiFi.h>
#include <espnow.h>

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


bool compare_address(uint8_t* add1, uint8_t* add2)
{
  for (int i = 0; i < 6; i++)
    if (add1[i] != add2[i])
      return false;
  return true;
}

void print_address(uint8_t* add){
  for(int i = 0; i<6; i++){
    Serial.print(add[i], HEX);
    Serial.print(" ");
  }
}

class Drone_Handler {
  public:
    uint8_t address[6];  // RECEIVER MAC Address
    drone_message droneData;
    command_message commandData;
    // boolean connection_status = false;

    Drone_Handler() {
    }

    void begin(uint8_t* droneAddress) {
      memcpy(address, droneAddress, 6);
      esp_now_add_peer(address, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
      print_address(droneAddress);
      Serial.println(" ");
    }

    void send(command_message* inputCommand) {
      memcpy(&commandData, inputCommand, sizeof(commandData));
      esp_now_send(address, (uint8_t *) &commandData, sizeof(commandData));
    }

    void receive(const unsigned char* incomingData){
      memcpy(&droneData, incomingData, sizeof(droneData));
    }

    void print_droneData(){
      Serial.print("Message: "); Serial.print(droneData.message);
      Serial.print(" Battery Voltage: "); Serial.print(droneData.battery);
      Serial.print(" Alive Time: "); Serial.println(droneData.time_alive);
      Serial.println();
    }
};


#define num_drones 2
Drone_Handler drone[num_drones];
command_message dummy_command;

uint8_t drone1_address[] = {0x5C, 0xCF, 0x7F, 0xB7, 0x22, 0x8E};
uint8_t drone2_address[] = {0x84, 0xF3, 0xEB, 0x5A, 0x73, 0xA2};
uint8_t drone3_address[] = {0xBC, 0xDD, 0xC2, 0x2B, 0x0E, 0x98};
uint8_t station_address[] = {0x80, 0x7D, 0x3A, 0xB7, 0x81, 0x54};

unsigned long beginTime;
unsigned long lastTime = 0;  
unsigned long timerDelay = 1000;  // send commands timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  
  if (sendStatus != 0){
    Serial.println("Delivery fail");
  }
  else{
    Serial.print("Data successfully sent to :");
    print_address((uint8_t*)mac_addr);
    Serial.println("\n");
  }
  
}

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {

  bool recognized = false;

  Serial.print("Msg Source");
  print_address(mac);
    
  for (int i = 0; i < num_drones; i++){
    if (compare_address(drone[i].address, mac)) {
      drone[i].receive(incomingData);
      
      Serial.print("Recognized as drone no. "); Serial.println(i);
      drone[i].print_droneData();
      
      recognized = true;
      break;
    }
  }
  if(!recognized) Serial.println("Unrecognized source\n");
}
 
void setup() {
  
  beginTime = millis();
  Serial.begin(115200);
  Serial.print("\n\n\n\n\n");
  
  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);  // sendCB to get the status of Trasnmitted packet
  esp_now_register_recv_cb(OnDataRecv);  // recvCB to get recv packer info

  
  drone[0].begin(drone2_address);
  drone[1].begin(drone3_address);
  //drone[2].begin(drone3_address);
}


void loop() {
  
  unsigned long currentTime = millis();
  
  if ((currentTime - lastTime) > timerDelay) {
    // Set values to send

    dummy_command.message = "Standby";

    dummy_command.target_pos[0] = random(-5, 5);
    dummy_command.target_pos[1] = random(-5, 5);
    dummy_command.target_pos[2] = random(-5, 5);

    dummy_command.station_clock[0] = floor(((currentTime - beginTime) / 1000) / 60.0);
    dummy_command.station_clock[1] = ((currentTime - beginTime) / 1000) % 60;

    for (int i = 0; i < num_drones; i++){
      drone[i].send(&dummy_command);
    }
    
    lastTime = currentTime;
  }
}
