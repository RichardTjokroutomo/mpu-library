#ifndef mpu6050_Richard_H
#define mpu6050_Richard_H
#include "Arduino.h"
#include <Wire.h>

class mpu{

  public :
  void initialize(byte _MPU);
  float gyroProcess(byte _MPU, byte _REG_ADDR, float _ERRORS, float _CAL_FACTOR, float _DT);
  float acclProcess(byte _MPU, boolean ROLL, float _ERRORS, float _CAL_FACTOR);
  float finalProcess(float _GYRO_CAL, float _GYRO_MEAN, float _GYRO_SD, float _GYRO_SUM, float DT, float _ACCL_CAL, float _ACCL_MEAN, float _ACCL_SD);
  
  };

#endif
