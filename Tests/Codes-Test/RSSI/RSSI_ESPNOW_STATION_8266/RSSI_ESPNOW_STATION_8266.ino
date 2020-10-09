#include <ESP8266WiFi.h>
#include <espnow.h>

#define LED 2

// data structure
typedef struct signal_message {
  int sig0;
  int sig1;
  int sig2;
  int sig3;
  int sig4;
} signal_message;

signal_message sigData;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  
  memcpy(&sigData, incomingData, sizeof(sigData));

  Serial.print(sigData.sig0); Serial.print(" ");
  Serial.print(sigData.sig1); Serial.print(" ");
  Serial.print(sigData.sig2); Serial.print(" ");
  Serial.print(sigData.sig3); Serial.print(" ");
  Serial.println(sigData.sig4);

}

void blink_forever(){
    while(true){
    digitalWrite(LED, 0);
    delay(100);
    digitalWrite(LED, 1);
    delay(100);
  }  
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  if (esp_now_init() != 0) {
    blink_forever();
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}
