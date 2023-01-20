#ifndef mpuCalibrator_Richard_H
#define mpuCalibrator_Richard_H
#include "Arduino.h"
#include <Wire.h>

class Calibrator{
  public :
  void  initialize(byte _MPU);
  float gyroMean(byte _MPU, byte _REG_ADDR, float _CAL_FACTOR);
  float gyroSD(byte _MPU, byte _REG_ADDR, float _CAL_FACTOR);
  float acclMean(byte _MPU, boolean _ROLL, float _CAL_FACTOR);
  float acclSD(byte _MPU, boolean _ROLL, float _CAL_FACTOR);
  };

#endif
