#include <Arduino.h>

void setup()
{
  Serial.begin(115200);
  // initialize LED digital pin as an output.
  pinMode(GPIO_NUM_23, OUTPUT);
  Serial.println("Pin 23 initialized for output");
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(GPIO_NUM_23, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(GPIO_NUM_23, LOW);
   // wait for a second
  delay(1000);
}