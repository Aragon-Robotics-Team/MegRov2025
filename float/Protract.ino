//Code for only protract to the max (i.e. floating mode)

// constants won't change
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as outputs.
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  //protracts the actuator
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);

  delay(35000); // actuator will stop retracting automatically when reaching the limit
}
