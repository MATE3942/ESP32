#include <Arduino.h>
//#include <TinyGPSPlus.h>
//#include <SoftwareSerial.h>

// Function Declarations
void updateSerial();
void test_sim800_module();
void send_SMS();

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial.println("Initializing...");
  delay(3000);
  test_sim800_module();
  send_SMS();
}

void loop() {
  updateSerial();
}

void test_sim800_module()
{
  Serial.println("Testing SIM800 Module\n");

  Serial.println("Communication with the module");
  Serial2.println("AT");
  updateSerial();
  Serial.println("-----------------------------");

  Serial.println("Signal Quality: should be more than 5");
  Serial2.println("AT+CSQ");
  updateSerial();
  Serial.println("-----------------------------");

  Serial.println("SIM card ID");
  Serial2.println("AT+CCID");
  updateSerial();
  Serial.println("-----------------------------");

  Serial.println("Network Registration: 1 for home network and 5 for public network");
  Serial2.println("AT+CREG?");
  updateSerial();
  Serial.println("-----------------------------");

  Serial.println("Product Information");
  Serial2.println("ATI");
  updateSerial();
  Serial.println("-----------------------------");

  Serial.println("Battery Information");
  Serial2.println("AT+CBC");
  updateSerial();
  Serial.println("-----------------------------");

  Serial.println("Operator Information");
  Serial2.println("AT+COPS?");
  updateSerial();
  Serial.println("-----------------------------");
}

// Function Definitions
void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (Serial2.available())
  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}

void send_SMS()
{
  Serial2.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  Serial2.println("AT+CMGS=\"+573226137339\"");//Phone number to SMS
  updateSerial();
  Serial2.print("Circuit Digest"); //text content
  updateSerial();
  Serial.println();
  Serial.println("Message Sent");
  Serial2.write(26);
}