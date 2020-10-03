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
   ESPrainbow(); // gökgüşahı efekti
}