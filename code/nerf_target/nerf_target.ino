#include <Servo.h>;

// Pins
const int servoPin = 3;
const int triggerPin = 8;
const int ledPin = 13;

// Servo angles
const int servoAngleUp = 120;
const int servoAngleDown = 10;

// Servo delay
const int servoDelay = 500;

// Servo object
Servo servo;

// Counter
int counter = 0;

// State
bool state = true;

// Run once at startup
void setup() {
  // Attach the servo
  servo.attach(servoPin);
  // Set the servo to the down position
  servo.write(servoAngleDown);

  // Set up other pins
  pinMode(triggerPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Set up the serial port
  Serial.begin(9600);
}

// Run repeatedly
void loop() {
  // Save the trigger state
  bool contact = (digitalRead(triggerPin) == LOW);

  // If contact is detected
  if (contact) {
    // Turn on LED
    digitalWrite(ledPin, HIGH);

    // Wait for 500ms
    // This prevents the servo from moving up and down too often
    delay(servoDelay);

    // Move the servo to the up position
    servo.write(servoAngleUp);

    // Update the state
    // Only if the state is not correct
    if (state != contact) {
      state = true;
      
      // Increment the counter
      counter++;

      // Print count to serial
      Serial.println(counter);
    }
  } else {
    // Turn off LED
    digitalWrite(ledPin, LOW);

    // Move the servo to the down position
    servo.write(servoAngleDown);

    // Reset state to false
    state = false;
  }
}
