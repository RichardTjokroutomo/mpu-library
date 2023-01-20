#include "mpu6050_Richard.h"

void mpu::initialize(byte MPU){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  }

float mpu::gyroProcess(byte MPU, byte REG_ADDR, float ERRORS, float CAL_FACTOR, float DT){
  float gyro;
  float val = 0.00;
  float result = 0.00;


  Wire.beginTransmission(MPU);
  Wire.write(REG_ADDR);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2 , true);
  gyro = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;
  val = gyro;
  val -= ERRORS;
  result = (val * DT);

  return result;
  }

float mpu::acclProcess(byte MPU, boolean ROLL, float ERRORS, float CAL_FACTOR){
   float kX, kY, kZ;
   float val = 0.00;
   float result = 0.00;

    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    kX = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;
    kY = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;
    kZ = (Wire.read() << 8 | Wire.read()) / CAL_FACTOR;

    if(ROLL == true){
       val += (atan(kY / sqrt(sq(kX) + sq(kZ))) * 180 / PI);   
      }
    else{
      val += (atan(-1 * kX / sqrt(sq(kY) + sq(kZ))) * 180 / PI);
      }

      result = val - ERRORS;
      return result;
  }

float mpu::finalProcess(float GYRO_CAL, float GYRO_MEAN, float GYRO_SD, float GYRO_SUM, float DT, float ACCL_CAL, float ACCL_MEAN, float ACCL_SD){
  float result = 0.00;
  float val2 = GYRO_CAL / DT;

  if( (val2 < (GYRO_MEAN + 30*GYRO_SD)) && (val2 > (GYRO_MEAN - 30*GYRO_SD)) ){
    GYRO_SUM = GYRO_SUM;
    }
  else{
    GYRO_SUM += GYRO_CAL;
    }

  if( (GYRO_SUM < (ACCL_CAL + 5*ACCL_SD)) && (GYRO_SUM > (ACCL_CAL - 5*ACCL_SD)) ){
     GYRO_SUM = GYRO_SUM;
    }
  else{
    GYRO_SUM = (0.9*GYRO_SUM) + (0.1*ACCL_CAL);
    }

    GYRO_SUM = (0.99*GYRO_SUM) + (0.01*ACCL_CAL);
    result = GYRO_SUM;
    return result;
  }
