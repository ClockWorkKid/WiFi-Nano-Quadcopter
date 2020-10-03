/*
 * www.espcopter.com/learn
 * 
*/

#define standalone

#include <espcopter.h> // ESPcopter kütüphanesi
#include <SimpleTimer.h> // Timer Kütüphanesi  

SimpleTimer timer;  // the timer objesi yarat

void setup() {
  mainSetup(); // uçuş ayarları
  timer.setInterval(1000, printValues); // printValues fonksiyonu için zaman aralığını ayarla
}

void loop() {
   mainLoop ();  // uçuş kontrol döngüsü
   timer.run(); // timer döngüsü
}

void printValues() {
    Serial.print("Temperature = ");
    Serial.print(getBmeTemp());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(getBmePressure());
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(getBmeAltitude());
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(getBmeHumidity());
    Serial.println(" %");

    Serial.println();
}