// Define pin numbers
const int stepPin = 5;
const int dirPin = 2;
const int enPin = 8;
const int limitSwitchPinForward = 9; // Connect the forward limit switch to pin 9.
const int limitSwitchPinBackward = 10; // Connect the backward limit switch to pin 10

void setup() {
  // Set the motor pins
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  // Configure limit switch pins
  pinMode(limitSwitchPinForward, INPUT_PULLUP); // Configure the forward limit switch pin as pull-up resistor input
  pinMode(limitSwitchPinBackward, INPUT_PULLUP); // Configure the limit switch pin backward as pull-up resistor input
}

void moveWithLimits(int direction, int limitSwitchPin) {
  while (digitalRead(limitSwitchPin) == HIGH) {
    // Changes the direction of motor motion
    digitalWrite(dirPin, direction == 1 ? LOW : HIGH);
    // Activate the motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
  }
}

void loop() {
  moveWithLimits(HIGH, limitSwitchPinForward); // Move forward until the forward limit switch is reached
  delay(1000); // One-second delay
  moveWithLimits(LOW, limitSwitchPinBackward); // Move backward until the backward limit switch is reached
  delay(1000);
}