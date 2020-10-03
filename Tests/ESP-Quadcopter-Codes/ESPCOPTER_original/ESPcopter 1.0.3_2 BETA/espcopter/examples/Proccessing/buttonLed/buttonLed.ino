#include <ESP8266WiFi.h>

const char WiFiAPPSK[] = "";
WiFiServer server(80);

#define blueLed 16
#define redLed 2
#define greenLed 0


void setup() {
  Serial.begin(9600);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  
 setupWiFi();

}

void loop() {
WiFiClient client = server.available();
 Serial.println("waiting... ");

  Serial.println(client);
  if (client ) {
    while (client.connected()) {
      while(1){
      if (client.available()) {
   
        int inChar;
        inChar = client.read();
        Serial.println(inChar);
         switch (inChar) {
         case 'A':
         analogWrite(blueLed,0);
         break;
         case 'a':
         analogWrite(blueLed,PWMRANGE);
         break;
         case 'B':
         analogWrite(redLed, PWMRANGE);
         break;
         case 'b':
         analogWrite(redLed, 0);
         break;
         case 'C':
         analogWrite(greenLed, PWMRANGE); 
         break;
         case 'c':
         analogWrite(greenLed, 0); 
         break;
      } 
    }
    }

   // Serial.println("Client disconnected.");
   // client.stop();
 } 

 }
}




void setupWiFi(){
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESPCopter";

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

   WiFi.softAP(AP_NameChar, WiFiAPPSK);

   server.begin();
}