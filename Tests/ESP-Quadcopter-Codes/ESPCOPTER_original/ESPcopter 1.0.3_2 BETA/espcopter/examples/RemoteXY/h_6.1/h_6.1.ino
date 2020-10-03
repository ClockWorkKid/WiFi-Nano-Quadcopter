

#define REMOTE_XY_REMOTE
#define NeoPixel

#include "remotexy.h"
#include <espcopter.h>

void setup() {
  
mainSetup();

}

void loop() {
  
mainLoop();
ESPsetPixelCollor(1,255,0,0);
ESPsetPixelCollor(2,0,255,0);
//ESPrainbow();

}
