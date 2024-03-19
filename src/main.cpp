#include <Arduino.h>

// Function declarations
void displayNumber(int number);

// Define the LED pins
  const int ledPins[] = {12, 14, 27, 26, 25, 33, 32};

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Set all the LED pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  Serial.println("Type the number you want to see in the 7 segment display: ");
  while (!Serial.available()); // Wait for user input

  // Read the number from serial
  int number = Serial.parseInt();

  // Clear the serial buffer
  while(Serial.available() > 0) {
    Serial.read();
  }

  // Write to the 7 segment display
  switch(number) {
    case 1:
      displayNumber(6);
      break;
    case 2:
      displayNumber(91);
      break;
    case 3:
      displayNumber(79);
      break;
    case 4:
      displayNumber(102);
      break;
    case 5:
      displayNumber(109);
      break;
    case 6:
      displayNumber(125);
      break;
    case 7:
      displayNumber(7);
      break;
    case 8:
      displayNumber(127);
      break;
    case 9:
      displayNumber(111);
      break;
    case 0:
      displayNumber(63);
      break;
    default:
      displayNumber(0);
      break;
  }
  delay(1000);
}

void displayNumber(int number) {
  // Assuming common anode 7-segment display
  for (int i = 0; i < 7; i++) {
    digitalWrite(ledPins[i], (number >> i) & 1);
  }
}