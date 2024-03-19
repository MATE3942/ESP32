#include <Arduino.h>
#include <WiFi.h>

const char *WIFI_NAME = "";
const char *WIFI_PASSWORD = "";

WiFiServer server(80);

String header;

String LED_STATE = "off";

const int GPIOpin = 23;

void setup()
{
    Serial.begin(115200);
    pinMode(GPIOpin, OUTPUT);

    digitalWrite(GPIOpin, LOW);

    Serial.print("Connecting to ");
    Serial.println(WIFI_NAME);
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    Serial.print("Trying to connect to Wifi Network");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
       Serial.print(".");
    }
    Serial.println("");
    Serial.println("Successfully connected to WiFi network");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop()
{
    WiFiClient client = server.available();
    if (client)
    {
        Serial.println("New Client is requesting web page");
        String current_data_line = "";
        while (client.connected())
        {
            if (client.available())
            {
                char new_byte = client.read();
                Serial.write(new_byte);
                header += new_byte;
                if (new_byte == '\n')
                {
                    if (current_data_line.length() == 0)
                    {
                        // Send a response to the client
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
                        // Check the value of the pin
                        if (header.indexOf("LED1=ON") != -1)
                        {
                            Serial.println("GPIO23 LED is ON");
                            LED_STATE = "on";
                            digitalWrite(GPIOpin, HIGH);
                        }
                        if (header.indexOf("LED1=OFF") != -1)
                        {
                            Serial.println("GPIO23 LED is OFF");
                            LED_STATE = "off";
                            digitalWrite(GPIOpin, LOW);
                        }
                        // Display the HTML web page
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #4CAF50; border: 2px solid #4CAF50;; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        // Web Page Heading
                        client.println("</style></head>");
                        client.println("<body><center><h1>ESP32 Web server LED control</h1></center>");
                        client.println("<center><h2>Press Button to interact</h3></center>");
                        client.println("<form><center>");
                        client.println("<p> LED one is " + LED_STATE + "</p>");
                        // If the PIN_NUMBER_22State is off, it displays the ON button
                        client.println("<center> <button class=\"button\" name=\"LED1\" value=\"ON\" type=\"submit\">LED1 ON</button>");
                        client.println("<button class=\"button\" name=\"LED1\" value=\"OFF\" type=\"submit\">LED1 OFF</button><br><br>");
                        client.println("</center></form></body></html>");
                        client.println();
                        break;
                    }
                    else
                    {
                        current_data_line = "";
                    }
                }
                else if (new_byte != '\r')
                {
                    current_data_line += new_byte;
                }
            }
        }
        // Clear the header variable
        header = "";
        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}