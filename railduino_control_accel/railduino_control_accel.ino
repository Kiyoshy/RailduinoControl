#include <AccelStepper.h>

// Define pin numbers
const int stepPin = 5;
const int dirPin = 2;
const int enPin = 8;
const int limitSwitchPinForward = 9; // Connect the forward limit switch to pin 9.
const int limitSwitchPinBackward = 10; // Connect the backward limit switch to pin 10
AccelStepper stepper(1, stepPin, dirPin); // Create an instance of the AccelStepper

void setup() {
  // Set the motor pins
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
  stepper.setMaxSpeed(2000.0); // Set maximum speed in steps per second
  stepper.setAcceleration(1000.0); // Set acceleration in steps per second^2

  // Configure limit switch pins
  pinMode(limitSwitchPinForward, INPUT_PULLUP); // Configure the forward limit switch pin as pull-up resistor input
  pinMode(limitSwitchPinBackward, INPUT_PULLUP); // Configure the limit switch pin backward as pull-up resistor input
}

void moveWithLimits(int direction, int limitSwitchPin) {
  while (digitalRead(limitSwitchPin) == HIGH) {
    stepper.setSpeed(500.0 * direction); // Set the speed and direction of the motor
    stepper.runSpeed(); // Step the motor
  }
  stepper.stop(); // Stop the motor
}

void loop() {
  moveWithLimits(1, limitSwitchPinForward); // Move forward until the forward limit switch is reached
  delay(1000); // One-second delay
  moveWithLimits(-1, limitSwitchPinBackward); // Move backward until the backward limit switch is reached
  delay(1000);
}