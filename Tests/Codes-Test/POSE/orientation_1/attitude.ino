#define calib_steps 5000

void update_attitude() {
  // Calculating Roll and Pitch from the accelerometer data
  
  accAngleX = (atan(imu.acc.y / sqrt(pow(imu.acc.x, 2) + pow(imu.acc.z, 2))) * 180 / PI) - AccErrorX; // ~(0.58)
  accAngleY = (atan(-1 * imu.acc.x / sqrt(pow(imu.acc.y, 2) + pow(imu.acc.z, 2))) * 180 / PI) - AccErrorY; // ~(-1.58)

  // Correct gyro with the calculated error values
  imu.rot.x = imu.rot.x - GyroErrorX; // GyroErrorX ~(-0.56)
  imu.rot.y = imu.rot.y - GyroErrorY; // GyroErrorY ~(2)
  imu.rot.z = imu.rot.z - GyroErrorZ; // GyroErrorZ ~ (-0.8)

  // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  gyroAngleX = gyroAngleX + imu.rot.x * elapsedTime; // deg/s * s = deg
  gyroAngleY = gyroAngleY + imu.rot.y * elapsedTime;
  yaw =  yaw + imu.rot.z * elapsedTime;

  // Complementary filter - combine acceleromter and gyro angle values
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;

  if (roll > 180.0) roll -= 360.0;
  else if (roll < -180.0) roll += 360.0;
  if (pitch > 180.0) pitch -= 360.0;
  else if (pitch < -180.0) pitch += 360.0;
  if (yaw > 360.0) yaw -= 360.0;
  else if (yaw < -360.0) yaw += 360.0;

}


void calculate_IMU_error() {
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 200 times
  for(int c = 0; c < calib_steps; c++){
    imu.update();
    // Sum all readings
    AccErrorX = AccErrorX + ((atan((imu.acc.y) / sqrt(pow((imu.acc.x), 2) + pow((imu.acc.z), 2))) * 180 / PI));
    AccErrorY = AccErrorY + ((atan(-1 * (imu.acc.x) / sqrt(pow((imu.acc.y), 2) + pow((imu.acc.z), 2))) * 180 / PI));

    GyroErrorX = GyroErrorX + imu.rot.x;
    GyroErrorY = GyroErrorY + imu.rot.y;
    GyroErrorZ = GyroErrorZ + imu.rot.z;
  }
  //Divide the sum by 200 to get the error value
  AccErrorX = AccErrorX / calib_steps;
  AccErrorY = AccErrorY / calib_steps;
  GyroErrorX = GyroErrorX / calib_steps;
  GyroErrorY = GyroErrorY / calib_steps;
  GyroErrorZ = GyroErrorZ / calib_steps;

  Serial.print("AccErrorX: ");
  Serial.println(AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(AccErrorY);
  Serial.print("GyroErrorX: ");
  Serial.println(GyroErrorX);
  Serial.print("GyroErrorY: ");
  Serial.println(GyroErrorY);
  Serial.print("GyroErrorZ: ");
  Serial.println(GyroErrorZ);
}
