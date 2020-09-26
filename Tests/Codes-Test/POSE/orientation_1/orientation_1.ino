#include "I2Cdev.h"
#include "Wire.h"

#include "myVector.h"
#include "sensor.h"

accelgyro imu;
compass com;
barometer bar;

float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
double elapsedTime, loop_freq;
unsigned long currentTime, previousTime;

void update_attitude();
void calculate_IMU_error();
void init_laser();
void update_laser();

void setup() {
  Wire.begin();
  Wire.setClock(800000);
  Serial.begin(115200);

  imu.init();
  com.init();
  bar.init();

  init_laser();

  //calculate_IMU_error();
  AccErrorX= -2.89;
  AccErrorY= -0.21;
  GyroErrorX= -2.52;
  GyroErrorY= 0.17;
  GyroErrorZ= -3.52;

  
  previousTime = micros();
}

void loop() {
  update_laser();
  imu.update();
  //com.update();
  //bar.update();

  currentTime = micros();
  elapsedTime = (currentTime - previousTime)/1000000.0;
  loop_freq = 1/elapsedTime;
  previousTime = currentTime;

  update_attitude();
 
//  imu.acc.print();
//  imu.rot.print();
//  com.mag.print();
//  Serial.print(com.head);
//  Serial.print(" ");
//  Serial.print(bar.temperature);
//  Serial.print(" ");
//  Serial.print(bar.pressure);
//  Serial.print(" ");
  Serial.print(roll);
  Serial.print(" ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.print(yaw);
  Serial.print(" ");
  Serial.print(" Loop freq: ");
  Serial.print(loop_freq);
  Serial.println();
}
