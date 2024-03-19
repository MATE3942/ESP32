#include <Arduino.h>

// Function declarations
void displayNumber(int number);

// Define the LED pins
  const int ledPins[] = {12, 14, 27, 26, 25, 33, 32};

void setup() {
  Serial.begin(115200);
  // Set all the LED pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.println("Press any key to start counting.");
  while (!Serial.available());
}

void loop() {
  // Code for counting from 0 to 9
  static int counter = 0; // Counter variable
  displayNumber(counter); // Write to the 7 segment display
  counter = (counter + 1) % 10; // Reset to 0 after reaching 9

  // Code for counting from 9 to 0
  /*static int counter = 9; // Counter variable
  displayNumber(counter); // Write to the 7 segment display
  counter = (counter - 1 + 10) % 10; // Reset to 9 after reaching 0*/

  delay(1000);
}

void displayNumber(int number) {
  int n;
  switch(number) {
    case 1:
      n = 6;
      break;
    case 2:
      n = 91;
      break;
    case 3:
      n = 79;
      break;
    case 4:
      n = 102;
      break;
    case 5:
      n = 109;
      break;
    case 6:
      n = 125;
      break;
    case 7:
      n = 7;
      break;
    case 8:
      n = 127;
      break;
    case 9:
      n = 111;
      break;
    case 0:
      n = 63;
      break;
    default:
      n = 0;
      break;
  }
  // Common cathode 7-segment display
  for (int i = 0; i < 7; i++) {
    digitalWrite(ledPins[i], (n >> i) & 1);
  }
}