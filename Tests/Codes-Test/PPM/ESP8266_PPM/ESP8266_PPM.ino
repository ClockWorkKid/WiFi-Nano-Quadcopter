//############################################################################//
//                          PPM Declarations                                  //
//############################################################################//

#define CPU_MHZ 80
#define CHANNEL_NUMBER 8  //set the number of chanels
#define CHANNEL_DEFAULT_VALUE 1100  //set the default servo value
#define FRAME_LENGTH 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PULSE_LENGTH 300  //set the pulse length
#define onState 0  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 5 //set PPM signal output pin on the arduino

int ppm[CHANNEL_NUMBER];
void ppmISR(void);
void ppm_begin(void);


//############################################################################//
//                            Setup and Loop                                  //
//############################################################################//

#define THROTTLE 1
#define ROLL 2
#define PITCH 3
#define YAW 0
#define AUX1 4
#define AUX2 5
#define AUX3 6
#define AUX4 7


void setup() {
  ppm_begin();
  Serial.begin(115200);
}

void loop() {

  ppm[THROTTLE] = 1000;
  ppm[ROLL] = 1500;
  ppm[PITCH] = 1500;
  ppm[YAW] = 1500;

  ppm[AUX1] = 1000;
  ppm[AUX2] = 1000;
  ppm[AUX3] = 1000;
  ppm[AUX4] = 1000;

  yield();
}
