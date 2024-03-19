#include <Arduino.h>

// Function Declarations
void updateSerial();
void test_sim800_module();
void send_SMS();
void recieve_SMS();

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200);
    delay(3000);
    Serial.print("\nWant to test SIM800 Module? (y/n): ");
    while(!Serial.available()){}
    char test = Serial.read();
    if (test == 'y') {
        test_sim800_module();
    }
    else if (test == 'n') {
        Serial.println("Skipping SIM800 Module Test");
    } else {
        Serial.println("Invalid Input");
    }
}

void loop() {
    Serial.println("\nWhat do you want to do?");
    Serial.println("1. Check connection status");
    Serial.println("2. Recieve Location");
    Serial.println("3. Check Signal Quality");
    Serial.println("4. Check Operator Information");
    Serial.println("5. Exit");
    Serial.print("Enter your choice: ");
    while(!Serial.available()){}
    int choice = Serial.parseInt();
    switch (choice) {
        case 1:
            Serial.println("Checking Connection Status");
            Serial2.println("AT");
            updateSerial();
            Serial.println();
            break;
        case 2:
            Serial.println("Recieving Location");
            //Serial2.println("AT+CIPGSMLOC=?"); // Test GPS Module
            Serial2.println("AT+CIPGSMLOC=1,1"); // Get Location, time and date
            updateSerial();
            Serial.println();
            break;
        case 3:
            Serial.println("Checking Signal Quality");
            Serial2.println("AT+CSQ");
            updateSerial();
            Serial.println();
            break;
        case 4:
            Serial.println("Checking Operator Information");
            Serial2.println("AT+COPS?");
            updateSerial();
            Serial.println();
            break;
        case 5:
            Serial.println("Exiting");
            exit(0);
            break;
        default:
            Serial.println("Invalid Choice");
            break;
    }
    Serial.println();
}

// Function Definitions
void updateSerial() {
    delay(500);
    while (Serial.available()) {
        Serial2.write(Serial.read()); // Forward what Serial received to Software Serial Port
    }
    while (Serial2.available()) {
        Serial.write(Serial2.read()); // Forward what Software Serial received to Serial Port
    }
}

void test_sim800_module() {
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

void send_SMS() {
    Serial2.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    Serial2.println("AT+CMGS=\"+573226137339\""); // Phone number to SMS
    updateSerial();
    Serial2.print("Circuit Digest"); // text content
    updateSerial();
    Serial.println();
    Serial.println("Message Sent");
    Serial2.write(26);
}

void recieve_SMS() {
    Serial2.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
    updateSerial();
    Serial.println("Waiting for SMS");
    delay(10000);
    if (Serial2.available() > 0) {
        String msg = Serial2.readString();
        Serial.println("Message Received: " + msg);
    }
    else {
        Serial.println("No Message Received");
    }
}