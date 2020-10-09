#include <ESP8266WiFi.h>
#include <espnow.h>

#define LED 2

uint8_t stationAddress[] = {0x84, 0xF3, 0xEB, 0x5A, 0x73, 0xA2};

String ssid0 = "Star";
String ssid1 = "MahSay";
String ssid2 = "Kantahasan/Galaxy Network";
String ssid3 = "Nafisa(Galaxy Network)";
String ssid4 = "Ahad";

// Send data structure
typedef struct signal_message {
  int sig0;
  int sig1;
  int sig2;
  int sig3;
  int sig4;
} signal_message;

signal_message sigData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  
  if (sendStatus != 0){
    digitalWrite(LED, 0);
  }
  else{
    digitalWrite(LED, 1);
  }
  
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
  WiFi.mode(WIFI_STA);
  
  if (esp_now_init() != 0) {
    blink_forever();
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(stationAddress, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);

}

void loop() {
  int n = WiFi.scanNetworks();

  for (int i = 0; i < n; ++i) {

    if (WiFi.SSID(i) == ssid0)
      sigData.sig0 = WiFi.RSSI(i);
    else if (WiFi.SSID(i) == ssid1)
      sigData.sig1 = WiFi.RSSI(i);
    else if (WiFi.SSID(i) == ssid2)
      sigData.sig2 = WiFi.RSSI(i);
    else if (WiFi.SSID(i) == ssid3)
      sigData.sig3 = WiFi.RSSI(i);
    else if (WiFi.SSID(i) == ssid4)
      sigData.sig4 = WiFi.RSSI(i);
  }
  
  esp_now_send(stationAddress, (uint8_t *) &sigData, sizeof(sigData));
}
