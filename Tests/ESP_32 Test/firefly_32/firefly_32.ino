#include "I2Cdev.h"
#include "Wire.h"

#include "myVector.h"
#include "sensor.h"

accelgyro imu;
compass com;
barometer bar;

void setup() {
  Wire.begin();
  Wire.setClock(800000);
  Serial.begin(115200);

  imu.init();
  com.init();
  bar.init();
}

void loop() {
  unsigned long t0 = micros();
  
  imu.update();
  com.update();
  //bar.update();
  unsigned long t1 = micros();

//  imu.acc.print();
//  imu.rot.print();
//  com.mag.print();
//  Serial.print(com.head);
//  Serial.print(" ");
//  Serial.print(bar.temperature);
//  Serial.print(" ");
//  Serial.print(bar.pressure);
//  Serial.print(" ");
  Serial.print(" Loop freq ");
  Serial.print( 1000000.0/(double)(t1-t0));
  Serial.println();

}
