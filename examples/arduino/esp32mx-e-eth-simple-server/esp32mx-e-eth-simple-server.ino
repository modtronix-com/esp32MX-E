/*
Ethernet Web Server LED Blink

A simple web server that lets you blink an LED via the web.
This sketch will print the IP address of your esp32MX-E board(once connected)
to the Serial monitor. From there, you can open that address in a web browser
to turn on and off the LED on pin 5.

If the IP address of your shield is yourAddress:
http://yourAddress/H turns the LED on
http://yourAddress/L turns it off

To test this sketch, do the following:
 - Install Arduino IDE
 - Install "Arduino ESP32" via the board manager (https://github.com/espressif/arduino-esp32#installation-instructions)
   This code was tested with v1.0.4 of "Arduino ESP32", which uses v3.2 of the Espressif ESP-IDE
 - Select the "ESP32 Pico Kit" board in the Arduino IDE
 - Plug the esp32MX-E into a network with a DHCP server, and connect to PC via USB
 - Verify and Upload this sketch
 - Start the Serial Monitor (in Tools menu)
*/

// Defines for Modtronix esp32MX-E board
#define ETH_ADDR      0
#define ETH_POWER_PIN -1    // There is no power pin, use -1 to disable the code
#define ETH_MDC_PIN   23
#define ETH_MDIO_PIN  18
#define ETH_TYPE      ETH_PHY_LAN8720
#ifdef ETH_CLK_MODE
#undef ETH_CLK_MODE
#endif
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_OUT

#include <ETH.h>
#include <WiFi.h>

WiFiServer server(80);

static bool eth_connected = false;

void handleEvent(WiFiEvent_t event) {
  switch (event) {
    case SYSTEM_EVENT_ETH_START:
      //set Ethernet hostname
      ETH.setHostname("esp32mx-e");
      Serial.println("ETH Started");
      Serial.print("ETH MAC: ");
      Serial.println(ETH.macAddress());
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      Serial.println("ETH Connected");
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      Serial.print("ETH IPv4: ");
      Serial.println(ETH.localIP());

      Serial.print("ETH ");
      if (ETH.fullDuplex()) {
        Serial.print("FULL_DUPLEX, ");
      }
      Serial.print(ETH.linkSpeed());
      Serial.println("Mbps");
      eth_connected = true;
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      Serial.println("ETH Disconnected");
      eth_connected = false;
      break;
    case SYSTEM_EVENT_ETH_STOP:
      Serial.println("ETH Stopped");
      eth_connected = false;
      break;
    default:
      break;
  }
}

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);

    WiFi.onEvent(handleEvent);
    ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
    
    server.begin();
}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(5, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(5, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
