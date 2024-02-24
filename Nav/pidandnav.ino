#include <Wire.h>
#include <Servo.h>
#include "MS5837.h"
#define TCAADDR 0x70

MS5837 depthSensor;
const int MPU_addr1 = 0x68;
float xAccel, yAccel, zAccel, roll, pitch;
double proportionalGain, integralGain, derivativeGain;
double error, derivativeError, previousError, integralSum, pidOutput;
double proportion_value, integral_value, derivative_value;
double depth, goal, depth_diff; // in meters
double bot_width = 17; //in inches
double baselineDepth, baselineRoll, baselinePitch;

int RB_PWM;
int LF_PWM;
int LB_PWM;
int RF_PWM;
int FRONT_PWM;
int BACK_PWM;

Servo LF_T; //left front
Servo LB_T; //left back
Servo RF_T; //right front
Servo RB_T; //right back
Servo F_VERT;
Servo B_VERT;

int tick = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  LF_T.attach(12); 
  RB_T.attach(10);
  LB_T.attach(8);
  RF_T.attach(13);

  F_VERT.attach(9);
  B_VERT.attach(11);

  initDepthSensor(7);
  calibrateDepth();
  
  initMPU(1);
  calibrateMPU();

  tunePID(500, 10, 0);
}



void loop() {
  if (Serial.available()) {
    
    RF_PWM = Serial.readStringUntil('-').toInt();
    LF_PWM = Serial.readStringUntil('=').toInt();
    RB_PWM = ((Serial.readStringUntil('+').toInt() - 1500) * (-1)) + 1500;
    LB_PWM = Serial.readStringUntil('*').toInt();
    FRONT_PWM = Serial.readStringUntil(',').toInt();
    BACK_PWM = Serial.readStringUntil('.').toInt();
    
    

    if ((FRONT_PWM == 1501) && (BACK_PWM == 1501)) {
      
      getDepth(7);
      getAngle(1);

      Serial.print(" PID ON ");
      Serial.print("DEPTH: ");
      Serial.print(depth);
      Serial.print(" ");
      
//      Serial.print("Depth: ");
//      Serial.print(depth);
//      
//      Serial.print(" | Roll: ");
//      Serial.print(roll);
//      
//      Serial.print(" | Pitch: ");
//      Serial.println(pitch);
      
      depth_diff = bot_width / (tan(roll - PI / 2)); // in inches
      depth_diff /= 39.37; // conversion to meters
      
      // gets depth every 50 readings to ensure it stays in place
      if (tick == 0) {
        tick++;
        goal = depth;
      }
      else if (tick % 50) {
        tick = 0;
      }
      
      FRONT_PWM = PID(depth, goal) + 1500;
      BACK_PWM = PID(depth, goal) + 1500;
    }

    tick = 0;

    Serial.println("RB_PWM: " + String((RB_PWM - 1500) * (-1) + 1500) + ", " +
               "LF_PWM: " + String(LF_PWM) + ", " + 
               "LB_PWM: " + String(LB_PWM) + ", " + 
               "RF_PWM: " + String(RF_PWM) + ", " + 
               "FRONT_VERT: " + String(FRONT_PWM) + ", " + 
               "BACK_VERT: " + String(BACK_PWM));

    LF_T.writeMicroseconds(LF_PWM);
    LB_T.writeMicroseconds(LB_PWM);
    RF_T.writeMicroseconds(RF_PWM);
    RB_T.writeMicroseconds(RB_PWM);    
    F_VERT.writeMicroseconds(FRONT_PWM);
    B_VERT.writeMicroseconds(BACK_PWM);

//    Serial.println("RB_PWM: " + String((RB_PWM - 1500) * (-1) + 1500) + ", " +
//                   "LF_PWM: " + String(LF_PWM) + ", " + 
//                   "LB_PWM: " + String(LB_PWM) + ", " + 
//                   "RF_PWM: " + String(RF_PWM) + ", " + 
//                   "FRONT_VERT: " + String(FRONT_PWM) + ", " + 
//                   "BACK_VERT: " + String(BACK_PWM));
    
    delay(10);
  }
}





// change SDA/SCL on mux
void selectChannel(int channel) {
  if (channel > 7) return;

  Wire.beginTransmission(0x70); // TCA9548A address
  Wire.write(1 << channel);     // send byte to select bus
  Wire.endTransmission();
}


// intialize pressure sensor with necessary delays
void initDepthSensor(int channel) {
  delay(500);

  Serial.println("Intializing Depth Sensor...");
  selectChannel(channel);

  while (!depthSensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }

  depthSensor.setModel(MS5837::MS5837_02BA);
  depthSensor.setFluidDensity(997);
  depthSensor.init();

  Serial.println("Success!\n");

  delay(500);
}


// intialize MPU6050 with necessary delays
void initMPU(int channel) {
  delay(500);
  Serial.println("Intializing MPU6050...");

  selectChannel(channel);
  Wire.beginTransmission(MPU_addr1);                 //begin, send the slave adress (in this case 68)
  Wire.write(0x6B);                                  //make the reset (place a 0 into the 6B register)
  Wire.write(0);
  Wire.endTransmission(true);                        //end the transmission

  Serial.println("Success!\n");
  delay(500);
}


// reads depth from pressure sensor
void getDepth(int channel) {
  selectChannel(channel);
  depthSensor.read();
  depth = (double) depthSensor.depth();  // float -> double
  depth -= baselineDepth;
}


// MPU6050 calculations to obtain roll and pitch
void getAngle(int channel) {
  selectChannel(channel);

  Wire.beginTransmission(MPU_addr1);
  Wire.write(0x3B);  //send starting register address, accelerometer high byte
  Wire.endTransmission(false); //restart for read

  Wire.requestFrom(MPU_addr1, 6, true); //get six bytes accelerometer data
  int t = Wire.read();
  xAccel = (t << 8) | Wire.read();
  t = Wire.read();
  yAccel = (t << 8) | Wire.read();
  t = Wire.read();
  zAccel = (t << 8) | Wire.read();

  // IN RADIANS
  roll = atan2(yAccel , zAccel);
  pitch = atan2(-xAccel , sqrt(yAccel * yAccel + zAccel * zAccel)); //account for roll already applied
  
  
  // convert to degrees
  // roll *= 180.0 / PI;
  // pitch *= 180.0 / PI;

  roll -= baselineRoll;
  pitch -= baselinePitch;

}


//Pid calculations :)
double PID(double depth, double goal) {

  error = goal - depth; //depth from sensor
  integralSum += error;
  derivativeError = error - previousError;

  proportion_value = proportionalGain * error;
  //integral_value = integralGain * integralSum;
  //derivative_value = derivativeGain * derivativeError;

  pidOutput = proportion_value + integral_value + derivative_value;
  pidOutput = -pidOutput;

  if (pidOutput > 0) {
    pidOutput += 36;
  }
  else {
    pidOutput -= 36;
  }

  pidOutput = max(-400, pidOutput);
  pidOutput = min(400, pidOutput);

  previousError = error; //for derivative

  return pidOutput;
}


//change gain values
void tunePID(double proportional, double integral, double derivative) {
  proportionalGain = proportional;
  integralGain = integral;
  derivativeGain = derivative;
}


void calibrateDepth() {
  Serial.println("Calibrating Depth Sensor");
  
  int tick = 0;
  double sum = 0.0;
  while (tick < 100) {
    getDepth(7);
    sum += depth;
    
    tick++;
  }

  baselineDepth = sum/tick;

  Serial.print("Depth Deviation: ");
  Serial.println(baselineDepth);
  Serial.println();

  delay(300);
}


void calibrateMPU() {
  Serial.println("Calibrating MPU6050");
  
  int tick = 1;
  double rollSum = 0.0;
  double pitchSum = 0.0;
  
  while (tick <= 100) {
    getAngle(1);
    rollSum += roll;
    pitchSum += pitch;
    tick++;
  }

  baselineRoll = rollSum/tick;
  baselinePitch = pitchSum/tick;

  Serial.print("Roll Deviation: ");
  Serial.println(baselineRoll);
  Serial.print("Pitch Deviation: ");
  Serial.println(baselinePitch);
  Serial.println();

  delay(300);
}
