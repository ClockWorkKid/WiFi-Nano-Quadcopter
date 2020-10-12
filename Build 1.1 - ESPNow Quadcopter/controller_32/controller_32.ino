//############################################################################//
//                          ESPNOW Declarations                               //
//############################################################################//

#include <esp_now.h>
#include <WiFi.h>

#define txInterval 50 //ms
#define timeout 200   //ms

#define thr_pin 39
#define yaw_pin 36
#define rol_pin 34
#define pit_pin 35
#define aux0_pin 15
#define aux1_pin 4

#define pair_indicator 13

#define thr_offset 50
#define yaw_offset 45
#define rol_offset 53
#define pit_offset 68

#define verbose_enabled false

uint8_t drone_address[] = {0xCC, 0x50, 0xE3, 0x3C, 0xAD, 0x13};
uint8_t drone1_address[] = {0x5C, 0xCF, 0x7F, 0xB7, 0x22, 0x8E};
uint8_t drone2_address[] = {0x84, 0xF3, 0xEB, 0x5A, 0x73, 0xA2};
uint8_t drone3_address[] = {0xBC, 0xDD, 0xC2, 0x2B, 0x0E, 0x98};
uint8_t station_address[] = {0x80, 0x7D, 0x3A, 0xB7, 0x81, 0x54};

unsigned long beginTime;
unsigned long currentTime;
unsigned long lastTime = 0; //transmission timer
unsigned long lastReceived; //successful receive timer
unsigned long lastSent;     //successful transmit timer


//############################################################################//
//                            ESPNOW Functions                                //
//############################################################################//

// Receive data structure
typedef struct drone_message {
  bool conn_stat;
  float battery;
  uint8_t local_time[2];
} drone_message;


// Send data structure
typedef struct command_message {
  bool conn_stat;
  int thr;
  int rol;
  int pit;
  int yaw;
  int aux[4];
  uint8_t local_time[2];
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

      if (verbose_enabled) print_address(droneAddress);
      if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        if (verbose_enabled) Serial.println(" peer registration failure\n");
      }
      else {
        if (verbose_enabled) Serial.println(" peer registration success\n");
        connection_status = true;
      }

    }

    void transmit() {
      esp_now_send(address, (uint8_t *) &commandData, sizeof(commandData));
    }

    void transmit_command(command_message* inputCommand) {
      memcpy(&commandData, inputCommand, sizeof(commandData));

      esp_now_send(address, (uint8_t *) &commandData, sizeof(commandData));
    }

    void receive(const unsigned char* incomingData) {
      memcpy(&droneData, incomingData, sizeof(droneData));
    }

    void print_droneData() {
      Serial.print("Drone connection: "); Serial.print(droneData.conn_stat);
      Serial.print(" bat "); Serial.print(droneData.battery);
      Serial.print(" min "); Serial.print(droneData.local_time[0]);
      Serial.print(" sec "); Serial.println(droneData.local_time[1]);
    }

    void print_commandData() {
      Serial.print("Station connection: "); Serial.print(commandData.conn_stat);
      Serial.print(" THR "); Serial.print(commandData.thr);
      Serial.print(" ROL "); Serial.print(commandData.rol);
      Serial.print(" PIT "); Serial.print(commandData.pit);
      Serial.print(" YAW "); Serial.print(commandData.yaw);
      Serial.print(" AU0 "); Serial.print(commandData.aux[0]);
      Serial.print(" AU1 "); Serial.print(commandData.aux[1]);
      Serial.print(" min "); Serial.print(commandData.local_time[0]);
      Serial.print(" sec "); Serial.println(commandData.local_time[1]);
    }
};

Drone_Handler drone;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {

  if (status != ESP_NOW_SEND_SUCCESS) {
    if (verbose_enabled) Serial.println("Delivery fail");
  }
  else {
    lastSent = millis();
    if (verbose_enabled) {
      Serial.print("Data successfully sent to :");
      print_address((uint8_t*)mac_addr);
      Serial.println("\n");
    }
  }

}

// Callback function that will be executed when data is received
void OnDataRecv(const unsigned char* mac, const unsigned char* incomingData, int len) {

  bool recognized = false;

  if (verbose_enabled) {
    Serial.print("Msg Source: ");
    print_address((uint8_t*)mac);
  }

  if (compare_address(drone.address, mac)) {
    lastReceived = millis();
    drone.receive(incomingData);

    if (verbose_enabled) Serial.println("Recognized as registered drone");

    recognized = true;
  }

  if (!recognized && verbose_enabled) Serial.println("Unrecognized drone\n");
}

void espnow32_begin() {

  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station

  if (esp_now_init() != ESP_OK) {
    if (verbose_enabled) Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for
  esp_now_register_send_cb(OnDataSent);  // sendCB to get the status of Trasnmitted packet
  esp_now_register_recv_cb(OnDataRecv);  // recvCB to get recv packer info

  drone.begin(drone_address);

}

//############################################################################//
//                            Helper Functions                                //
//############################################################################//


void joystick_begin() {
  pinMode(thr_pin, INPUT);
  pinMode(yaw_pin, INPUT);
  pinMode(yaw_pin, INPUT);
  pinMode(rol_pin, INPUT);
  pinMode(aux0_pin, INPUT);
  pinMode(aux1_pin, INPUT);

  pinMode(pair_indicator, OUTPUT);
}

void joystick_routine(bool feedback_enabled) {
  drone.commandData.thr = map(analogRead(thr_pin), 0, 4095, 2000, 1000) - thr_offset;
  drone.commandData.rol = map(analogRead(rol_pin), 0, 4095, 2000, 1000) - rol_offset;
  drone.commandData.pit = map(analogRead(pit_pin), 0, 4095, 2000, 1000) - pit_offset;
  drone.commandData.yaw = map(analogRead(yaw_pin), 0, 4095, 2000, 1000) - yaw_offset;

  drone.commandData.aux[0] = !digitalRead(aux0_pin) ? !drone.commandData.aux[0] : drone.commandData.aux[0];
  drone.commandData.aux[1] = !digitalRead(aux1_pin) ? !drone.commandData.aux[1] : drone.commandData.aux[1];

  drone.commandData.local_time[0] = floor(((currentTime - beginTime) / 1000) / 60.0);
  drone.commandData.local_time[1] = ((currentTime - beginTime) / 1000) % 60;

  if (feedback_enabled) {
    Serial.println("\nTransmitter");
    drone.print_commandData();
    drone.print_droneData();
  }

  drone.transmit();
}

//############################################################################//
//                            Setup and Loop                                  //
//############################################################################//

void setup() {

  beginTime = millis();
  Serial.begin(115200);
  Serial.print("\n\n\n\n\n");

  espnow32_begin();
  joystick_begin();
}


void loop() {

  currentTime = millis();

  if ((currentTime - lastReceived) > timeout || (currentTime - lastSent) > timeout) {
    drone.commandData.conn_stat = false;
    digitalWrite(pair_indicator, LOW);
  }
  else {
    drone.commandData.conn_stat = true;
    digitalWrite(pair_indicator, HIGH);
  }

  if ((currentTime - lastTime) > txInterval) {
    joystick_routine(false);
    lastTime = currentTime;
  }
}
