#include "PPMEncoder.h"

#define OUTPUT_PIN 10
#define NUM_CHANNELS 8

#define YAW 0
#define THROTTLE 1
#define ROLL 2
#define PITCH 3
#define AUX1 4
#define AUX2 5
#define AUX3 6
#define AUX4 7

uint16_t data_channel[NUM_CHANNELS];

void init_payload(){
  data_channel[THROTTLE] = 1000;
  data_channel[ROLL] = 1500;
  data_channel[PITCH] = 1500;
  data_channel[YAW] = 1500;

  data_channel[AUX1] = 1000;
  data_channel[AUX2] = 1000;
  data_channel[AUX3] = 1000;
  data_channel[AUX4] = 1000;
}

void update_ppm(){
  for(int i = 0; i < NUM_CHANNELS; i++){
      ppmEncoder.setChannel(i, data_channel[i]);
  }
}

void setup() {
  ppmEncoder.begin(OUTPUT_PIN, NUM_CHANNELS);
  init_payload();
}

void loop() {
  update_ppm();
}
