#include "I2Cdev.h"
#include "Wire.h"
#include "MPU6050.h"
#include "HMC5883L.h"
#include "BMP085.h"

#include "sensor.h"

/*********************************************************************/
//                     ACCELEROMETER & GYRO                          //
/*********************************************************************/

void accelgyro::init() {
  imu.initialize();
  Serial.print("Testing Accel/Gyro... ");
  Serial.println(imu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  imu.setI2CBypassEnabled(true);  //This sets the bypass so the HMC5883L gets a look in.
}
void accelgyro::update() {
  imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //sensor.getAcceleration(&ax, &ay, &az);
  //sensor.getRotation(&gx, &gy, &gz);
  acc.x = ((double)ax) / ACCEL_SENS;
  acc.y = ((double)ay) / ACCEL_SENS;
  acc.z = ((double)az) / ACCEL_SENS;
  rot.x = ((double)gx) / GYRO_SENS;
  rot.y = ((double)gy) / GYRO_SENS;
  rot.z = ((double)gz) / GYRO_SENS;
}


/*********************************************************************/
//                          COMPASS                                  //
/*********************************************************************/

void compass::init() {
  magnetometer.initialize();
  Serial.print("Testing Mag...  ");
  Serial.println(magnetometer.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
}

void compass::update() {
  magnetometer.getHeading(&mx, &my, &mz);
  mag.x = mx;
  mag.y = my;
  mag.z = mz;
  head = atan2(mag.y, mag.x) / M_PI * 180.0;
  if (head < 0) {
    head = head + 360.0;
  }
}


/*********************************************************************/
//                          BAROMETER                                //
/*********************************************************************/

void barometer::init() {
  ambient.initialize();
  Serial.print("Testing Pressure...  ");
  Serial.println(ambient.testConnection() ? "BMP085 connection successful" : "BMP085 connection failed");
}

void barometer::update() {
  ambient.setControl(BMP085_MODE_TEMPERATURE);

  // wait appropriate time for conversion (4.5ms delay)
  lastMicros = micros();
  while (micros() - lastMicros < ambient.getMeasureDelayMicroseconds());

  // read calibrated temperature value in degrees Celsius
  temperature = ambient.getTemperatureC();

  // request pressure (3x oversampling mode, high detail, 23.5ms delay)
  ambient.setControl(BMP085_MODE_PRESSURE_3);
  while (micros() - lastMicros < ambient.getMeasureDelayMicroseconds());

  // read calibrated pressure value in Pascals (Pa)
  pressure = ambient.getPressure() / 100.0;
}
