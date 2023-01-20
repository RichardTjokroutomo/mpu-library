#include <mpuCalibrator_Richard.h>

Calibrator calibrate;

#define MPU 0x68
float gX, gY, gZ;
float aX, aY;
char latch;

void setup() {

 calibrate.initialize(MPU);
 Serial.begin(9600);
 Serial.println("System ready, press 1 to find mean, press 2 to find SD");
}

void loop() {
 latch = Serial.read();

 if(latch == 49){
  gX = calibrate.gyroMean(MPU, 0x43, 131.0);  // (DEV_ADDR, REG_ADDR, Calibration factor)
  gY = calibrate.gyroMean(MPU, 0x45, 131.0);
  gZ = calibrate.gyroMean(MPU, 0x47, 131.0);
  
  Serial.println("gyro mean errors : ");
  Serial.println(gX);
  Serial.println(gY);
  Serial.println(gZ);

  aX = calibrate.acclMean(MPU, true, 16384.0);  // (DEV_ADDR, Is it roll?, Calibration factor)
  aY = calibrate.acclMean(MPU, false, 16384.0);
  
  Serial.println("accel mean errors : ");
  Serial.println(aX);
  Serial.println(aY);
  Serial.println();
 
  latch = '\n';
  }

  if(latch == 50){
    
  gX = calibrate.gyroSD(MPU, 0x43, 131.0);
  gY = calibrate.gyroSD(MPU, 0x45, 131.0);
  gZ = calibrate.gyroSD(MPU, 0x47, 131.0);
  
  Serial.println("gyro SD errors : ");
  Serial.println(gX);
  Serial.println(gY);
  Serial.println(gZ);

  aX = calibrate.acclSD(MPU, true, 16384.0);
  aY = calibrate.acclSD(MPU, false, 16384.0);
  
  Serial.println("accel SD errors : ");
  Serial.println(aX);
  Serial.println(aY);
  Serial.println();
 
  latch = '\n';
    }
    
}
