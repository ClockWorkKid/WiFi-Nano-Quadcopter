// https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/

#include <esp_now.h>
#include <WiFi.h>

#define txInterval 100

#define thr_pin 39
#define yaw_pin 36
#define rol_pin 34
#define pit_pin 35
#define aux0_pin 15
#define aux1_pin 4

uint8_t drone_address[] = {0x5C, 0xCF, 0x7F, 0xB7, 0x22, 0x8E};
uint8_t drone2_address[] = {0x84, 0xF3, 0xEB, 0x5A, 0x73, 0xA2};
uint8_t drone3_address[] = {0xBC, 0xDD, 0xC2, 0x2B, 0x0E, 0x98};
uint8_t station_address[] = {0x80, 0x7D, 0x3A, 0xB7, 0x81, 0x54};


// Receive data structure
typedef struct drone_message {
  String message;
  float battery;
  unsigned long time_alive;
  float pose[7];
} drone_message;


// Send data structure
typedef struct command_message {
  int throttle;
  int roll;
  int pitch;
  int yaw;
  int aux[4];
  uint8_t station_clock[2];
} command_message;


bool compare_address(uint8_t* add1, const unsigned char* add2)
{
  for (int i = 0; i < 6; i++)
    if (add1[i] != add2[i])
      return false;
  return true;
}

void print_address(uint8_t* add) {
  for (int i = 0; i < 6; i++) {
    Serial.print(add[i], HEX);
    Serial.print(" ");
  }
}

class Drone_Handler {
  public:
    uint8_t address[6];  // RECEIVER MAC Address
    drone_message droneData;
    command_message commandData;
    esp_now_peer_info_t peerInfo;
    boolean connection_status = false;

    Drone_Handler() {
    }

    void begin(uint8_t* droneAddress) {
      memcpy(address, droneAddress, 6);
      memcpy(peerInfo.peer_addr, address, 6); //register peer
      peerInfo.channel = 0;
      peerInfo.encrypt = false;

      print_address(droneAddress);
      if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println(" peer registration failure\n");
      }
      else {
        Serial.println(" peer registration success\n");
        connection_status = true;
      }
    }

    void transmit() {
      esp_now_send(address, (uint8_t *) &commandData, sizeof(commandData));
    }

    void send(command_message* inputCommand) {
      memcpy(&commandData, inputCommand, sizeof(commandData));

      esp_now_send(address, (uint8_t *) &commandData, sizeof(commandData));
    }

    void receive(const unsigned char* incomingData) {
      memcpy(&droneData, incomingData, sizeof(droneData));
    }

    void print_droneData() {
      Serial.print("Message: "); Serial.print(droneData.message);
      Serial.print(" Battery Voltage: "); Serial.print(droneData.battery);
      Serial.print(" Alive Time: "); Serial.println(droneData.time_alive);
      Serial.println();
    }
};


Drone_Handler drone;


unsigned long beginTime;
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;  // send commands timer


// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {

  if (status != ESP_NOW_SEND_SUCCESS) {
    Serial.println("Delivery fail");
  }
  else {
    Serial.print("Data successfully sent to :");
    print_address((uint8_t*)mac_addr);
    Serial.println("\n");
  }

}

// Callback function that will be executed when data is received
void OnDataRecv(const unsigned char* mac, const unsigned char* incomingData, int len) {

  bool recognized = false;

  Serial.print("Msg Source: ");
  print_address((uint8_t*)mac);


  if (compare_address(drone.address, mac)) {
    drone.receive(incomingData);

    Serial.println("Recognized as registered drone");
    drone.print_droneData();

    recognized = true;
  }

  if (!recognized) Serial.println("Unrecognized drone\n");
}


void setup() {

  pinMode(thr_pin, INPUT);
  pinMode(yaw_pin, INPUT);  
  pinMode(yaw_pin, INPUT);
  pinMode(rol_pin, INPUT);  
  pinMode(aux0_pin, INPUT);
  pinMode(aux1_pin, INPUT);

  beginTime = millis();
  Serial.begin(115200);
  Serial.print("\n\n\n\n\n");

  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station

  if (esp_now_init() != ESP_OK) {  // Init ESP-NOW
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for
  esp_now_register_send_cb(OnDataSent);  // sendCB to get the status of Trasnmitted packet
  esp_now_register_recv_cb(OnDataRecv);  // recvCB to get recv packer info

  drone.begin(drone_address);

}


void loop() {

  unsigned long currentTime = millis();

  if ((currentTime - lastTime) > txInterval) {
    drone.commandData.throttle = analogRead(thr_pin);
    drone.commandData.roll = analogRead(rol_pin);
    drone.commandData.pitch = analogRead(pit_pin);
    drone.commandData.yaw = analogRead(yaw_pin);

    drone.commandData.aux[0] = !digitalRead(aux0_pin) ? !drone.commandData.aux[0] : drone.commandData.aux[0];
    drone.commandData.aux[1] = !digitalRead(aux1_pin) ? !drone.commandData.aux[1] : drone.commandData.aux[1];

    drone.commandData.station_clock[0] = floor(((currentTime - beginTime) / 1000) / 60.0);
    drone.commandData.station_clock[1] = ((currentTime - beginTime) / 1000) % 60;

    Serial.print(drone.commandData.throttle);  Serial.print(" ");
    Serial.print(drone.commandData.roll);  Serial.print(" ");
    Serial.print(drone.commandData.pitch);  Serial.print(" ");
    Serial.print(drone.commandData.yaw);  Serial.print(" ");
    Serial.print(drone.commandData.aux[0]);  Serial.print(" ");
    Serial.print(drone.commandData.aux[1]);  Serial.println();

    if (drone.connection_status) {
      drone.transmit();
    }
    else {
      Serial.println(" peer not connected, no data sent\n");
    }
    
    lastTime = currentTime;
  }


}
