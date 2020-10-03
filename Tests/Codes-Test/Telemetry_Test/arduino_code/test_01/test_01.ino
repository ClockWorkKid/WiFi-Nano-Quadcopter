#include <SoftwareSerial.h>

// #define RX_PIN 11 //used for Mavlink, reads input from Pixhawk
// #define TX_PIN 12 //used for Mavlink, transmits to Pixhawk

// SoftwareSerial Telemetry = SoftwareSerial(RX_PIN, TX_PIN);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for port to connect.
  }
  Serial1.begin(115200);

  Serial.println("Ready");
 
}
void loop()
{
  if (Serial1.available())
  {
    Serial.println(Serial1.read());
  }
}
