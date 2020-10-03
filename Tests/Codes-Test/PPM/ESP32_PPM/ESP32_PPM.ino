//############################################################################//
//                          PPM Declarations                                  //
//############################################################################//

#define CHANNEL_NUMBER 8  //set the number of chanels
#define CHANNEL_DEFAULT_VALUE 1100  //set the default servo value
#define FRAME_LENGTH 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PULSE_LENGTH 300  //set the pulse length
#define sigPin 25 //set PPM signal output pin on the arduino

int ppm[CHANNEL_NUMBER];
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

#define LED_BUILTIN 2
uint16_t t0;

void setup() {
  ppm_begin();
  Serial.begin(115200);
//  pinMode(LED_BUILTIN, OUTPUT);
//  digitalWrite(LED_BUILTIN, 0);
}

void loop() {

  ppm[THROTTLE] = 1100;
  ppm[ROLL] = 1200;
  ppm[PITCH] = 1300;
  ppm[YAW] = 1400;

  ppm[AUX1] = 1500;
  ppm[AUX2] = 1600;
  ppm[AUX3] = 1700;
  ppm[AUX4] = 1800;
  
  yield();
}
