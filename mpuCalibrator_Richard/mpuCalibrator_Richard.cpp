#include "mpuCalibrator_Richard.h"

void Calibrator::initialize(byte MPU){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  }

float Calibrator::gyroMean(byte MPU, byte REG_ADDR, float CAL_FACTOR){

  float result = 0.00;
  float val = 0.00;

  for(int i = 0; i <= 199; i++){
    Wire.beginTransmission(MPU);
    Wire.write(REG_ADDR);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 2, true);
    val = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;

    result += val;
    }

    result /= 200;
    return result;
  }

float Calibrator::gyroSD(byte MPU, byte REG_ADDR, float CAL_FACTOR){
  float result = 0.00;
  float val = 0.00;
  float val2 = 0.00;
  float keeper;

  for(int i = 0; i <= 199; i++){
    Wire.beginTransmission(MPU);
    Wire.write(REG_ADDR);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 2, true);
    keeper = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;
    val += keeper;
    val2 += sq(keeper);
  }

   result = sqrt((val2 / 200) - sq(val / 200));

   return result;
  }

float Calibrator::acclMean(byte MPU, boolean ROLL, float CAL_FACTOR){
  float kX, kY, kZ;
  float vX = 0.00;
  float vY = 0.00;
  float vZ = 0.00;
  float result = 0.00;

  for(int i = 0; i <= 199; i++){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    kX = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;
    kY = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;
    kZ = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;

    vX += kX;
    vY += kY;
    vZ += kZ;
    }

    vX /= 200;
    vY /= 200;
    vZ /= 200;

    if(ROLL == true){
       result = (atan(vY / sqrt(sq(vX) + sq(vZ))) * 180 / PI);
      }
    else{
      result = (atan(-1 * vX / sqrt(sq(vY) + sq(vZ))) * 180 / PI);
      }

      return result;
  }

float Calibrator::acclSD(byte MPU, boolean ROLL, float CAL_FACTOR){
  float kX, kY, kZ;
  float val = 0.00;
  float val2 = 0.00;
  
  float result = 0.00;

  for(int i = 0; i<= 199; i++){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    kX = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;
    kY = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;
    kZ = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;

    if(ROLL == true){
       val += (atan(kY / sqrt(sq(kX) + sq(kZ))) * 180 / PI);
       val2 += sq((atan(kY / sqrt(sq(kX) + sq(kZ))) * 180 / PI));
      }
    else{
      val += (atan(-1 * kX / sqrt(sq(kY) + sq(kZ))) * 180 / PI);
      val2 += sq((atan(-1 * kX / sqrt(sq(kY) + sq(kZ))) * 180 / PI));
      }
    }
    result = sqrt((val2 / 200) - sq(val / 200));
    return result;
  }
