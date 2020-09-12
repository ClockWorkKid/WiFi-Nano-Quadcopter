/*
 * www.espcopter.com/learn
 * 
*/

#define standalone


#include <espcopter.h> // ESPcopter kütüphanesi


void setup() {
  mainSetup(); // uçuş ayarları
}

void loop() {
   mainLoop ();  // uçuş kontrol döngüsü
   
   ESPsetPixel (0,255,0,0);
   ESPsetPixel (1,255,0,0);
   ESPsetPixel (2,255,0,0);
   ESPsetPixel (3,255,0,0);
   ESPsetPixel (4,0,255,0);
   ESPsetPixel (5,0,255,0);
   ESPsetPixel (6,0,255,0);
   ESPsetPixel (7,0,255,0);
   ESPsetPixel (8,0,0,255);
   ESPsetPixel (9,0,0,255);
   ESPsetPixel (10,0,0,255);
   ESPsetPixel (11,0,0,255);
   strip.Show();
   
}