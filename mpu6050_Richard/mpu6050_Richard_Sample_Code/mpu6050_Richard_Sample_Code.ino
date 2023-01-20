#include <mpuCalibrator_Richard.h>
#include <mpu6050_Richard.h>

Calibrator calibrate;
mpu Mpu;

#define MPU 0x68
float gXm, gYm, gXsd, gYsd;
float aXm, aYm, aXsd, aYsd;

float gX = 0.00;
float gY = 0.00;

float aX = 0.00;
float aXprev = 0.00;
float aY = 0.00;

float roll = 0.00;
float pitch = 0.00;

char latch = 49;
boolean start = false;
float current, prev, dt;

void setup() {
 calibrate.initialize(MPU);
 Serial.begin(9600);
 Serial.println("system ready, press 1 to begin, or press 2 to stop");
}

void loop() {
latch = Serial.read();

if(latch == 49){
  CalculateErrors();
  start = true;
  latch = '\n';
  }
if(latch == 50){
  start = false;
  }

if(start == true){
  // this is where the new library will be put into action //
  ProcessResultGyro();
  ProcessResultAccl(); 
  FinalProcessing();
  }

}

void CalculateErrors(){

  // gyro Mean
  gXm = calibrate.gyroMean(MPU, 0x43, 131.0);  // (DEV_ADDR, REG_ADDR, Calibration factor)
  gYm = calibrate.gyroMean(MPU, 0x45, 131.0);

  // gyro SD
  gXsd = calibrate.gyroSD(MPU, 0x43, 131.0);
  gYsd = calibrate.gyroSD(MPU, 0x45, 131.0);

  // accel Mean
  aXm = calibrate.acclMean(MPU, true, 16384.0); // (DEV_ADDR, Is it roll?, Calibration factor)
  aYm = calibrate.acclMean(MPU, false, 16384.0);

  // accel SD
  aXsd = calibrate.acclSD(MPU, true, 16384.0);
  aYsd = calibrate.acclSD(MPU, false, 16384.0);
 
  }

void ProcessResultGyro(){

   prev = current;
   current = millis();
   dt = (current - prev) / 1000;
   gX = (Mpu.gyroProcess(MPU, 0x43, gXm, 131.0, dt)); // (DEV_ADDR, REG_ADDR, Gyro Mean Error, Calibration factor, time change)
  // Serial.println(gX);
  }

void ProcessResultAccl(){
  aXprev = aX;
  aX = Mpu.acclProcess(MPU, true, aXm, 16384.0);  // (DEV_ADDR, Is it roll? Accel Mean Error, Calibration factor)

  //Serial.println(aX);
  }

void FinalProcessing(){
  roll = Mpu.finalProcess(gX, gXm, gXsd, roll, dt, aX, aXm, aXsd); // (Gyro Latest reading, Gyro mean error, Gyro SD, Previous roll value, time change, Accel latest reading, Accel mean error, Accel SD)
  Serial.println(roll);
  }
