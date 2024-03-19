#include <Arduino.h>

// Define the GPIO pins for the RGB LED
const int ledRPin = 16; // Example pin for red
const int ledGPin = 17; // Example pin for green
const int ledBPin = 5; // Example pin for blue

// Set the frequency and resolution for PWM
const int freq = 5000;
const int resolution = 8;

// Define the LED channels
const int ledRChannel = 0;
const int ledGChannel = 1;
const int ledBChannel = 2;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Configure LED PWM functionalities
  ledcSetup(ledRChannel, freq, resolution);
  ledcSetup(ledGChannel, freq, resolution);
  ledcSetup(ledBChannel, freq, resolution);

  // Attach the channels to the GPIOs to be controlled
  ledcAttachPin(ledRPin, ledRChannel);
  ledcAttachPin(ledGPin, ledGChannel);
  ledcAttachPin(ledBPin, ledBChannel);
}

void loop() {
  // Ask for the RGB value
  Serial.println("Enter a Hexadecimal value: ");
  while (!Serial.available()) {
    // Wait for input
  }
  String hexCode = Serial.readStringUntil('\n');

  // Remove the '#' character from the hexadecimal code
  if (hexCode[0] == '#') {
    hexCode.remove(0, 1);
  }

  // Convert the hexadecimal code to integer
  long hexValue = strtol(hexCode.c_str(), nullptr, 16);

  // Extract the red, green, and blue values using bitwise operations and bit shifting
  int red = (hexValue >> 16) & 0xFF;
  int green = (hexValue >> 8) & 0xFF;
  int blue = hexValue & 0xFF;

  // Invert the values for Common Anode LED
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;

  // Write the inverted values to the LED
  ledcWrite(ledRChannel, red);
  ledcWrite(ledGChannel, green);
  ledcWrite(ledBChannel, blue);

  Serial.print("Red: ");
  Serial.print(255 - red); // Print original values
  Serial.print(", Green: ");
  Serial.print(255 - green);
  Serial.print(", Blue: ");
  Serial.println(255 - blue);

  Serial.println("------------------------------");
}