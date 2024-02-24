#include "MS5837.h"

MS5837 depthSensor;
double depth; // in meters

void setup() {
  Serial.begin(9600);
  initDepthSensor();

  delay(2000);
}

void loop() {
  if (Serial.available()) {
    getDepth();
    Serial.print("DEPTH: ");
    Serial.print(depth);
    Serial.println("");
  }

  delay(10);
}


// intialize pressure sensor with necessary delays
void initDepthSensor() {
  delay(500);

  Serial.println("Intializing Depth Sensor...");

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


// reads depth from pressure sensor
void getDepth() {
  depthSensor.read();
  depth = (double) depthSensor.depth();  // float -> double
}
