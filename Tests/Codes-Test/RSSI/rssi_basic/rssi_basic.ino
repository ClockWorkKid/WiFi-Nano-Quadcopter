
#include <ESP8266WiFi.h>

String ssid0 = "Star";
String ssid1 = "MahSay";
String ssid2 = "Kantahasan/Galaxy Network";
String ssid3 = "Nafisa(Galaxy Network)";
String ssid4 = "Ahad";

int str0 = 0;
int str1 = 0;
int str2 = 0;
int str3 = 0;
int str4 = 0;


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}

void loop() {
  int n = WiFi.scanNetworks();

  for (int i = 0; i < n; ++i) {

    if (WiFi.SSID(i) == ssid0)
      str0 = WiFi.RSSI(i);
    else if (WiFi.SSID(i) == ssid1)
      str1 = WiFi.RSSI(i);
    else if (WiFi.SSID(i) == ssid2)
      str2 = WiFi.RSSI(i);
    else if (WiFi.SSID(i) == ssid3)
      str3 = WiFi.RSSI(i);
    else if (WiFi.SSID(i) == ssid4)
      str4 = WiFi.RSSI(i);
  }

  Serial.print(str0);  Serial.print(" ");
  Serial.print(str1);  Serial.print(" ");
  Serial.print(str2);  Serial.print(" ");
  Serial.print(str3);  Serial.print(" ");
  Serial.println(str4);
  
  WiFi.scanDelete();
}
