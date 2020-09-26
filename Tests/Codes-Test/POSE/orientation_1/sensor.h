#include "MPU6050.h"
#include "HMC5883L.h"
#include "BMP085.h"
#include "myVector.h"

#ifndef SENSOR_H
#define SENSOR_H

class accelgyro {
  private:
    MPU6050 imu;
    int16_t ax, ay, az, gx, gy, gz;
    const float ACCEL_SENS = 16384.0; // Accel Sensitivity with default +/- 2g scale
    const float GYRO_SENS  = 131.0;   // Gyro Sensitivity with default +/- 250 deg/s scale
  public:
    myVector acc, rot;
    void init();
    void update();
};

class compass {
  private:
    int16_t mx, my, mz;
  public:
    myVector mag;
    HMC5883L magnetometer;
    double head;
    void init();
    void update();
};

#endif

class barometer {
  private:
    BMP085 ambient;
    int32_t lastMicros;
  public:
    float temperature, pressure;
    void init();
    void update();
};
