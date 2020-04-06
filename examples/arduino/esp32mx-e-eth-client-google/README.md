
Basic Ethernet client test. The esp32MX-E will connect to google, and print the resuls to a
terminal at 115200 baud.
  
This test requires the board is plugged into a network with a DHCP server. When running this
sketch, the esp32MX-E will connect to the DHCP server and obtain an IP address. It will then
attemp to connect to "google.com", and print the result to the terminal.

To test this sketch, do the following:
 - Install Arduino IDE
 - Install "Arduino ESP32" via the board manager (https://github.com/espressif/arduino-esp32#installation-instructions)
   This code was tested with v1.0.4 of "Arduino ESP32", which uses v3.2 of the Espressif ESP-IDE
 - Select the "ESP32 Pico Kit" board in the Arduino IDE
 - Plug the esp32MX-E into a network with a DHCP server, and connect to PC via USB
 - Verify and Upload this sketch
 - Start the Serial Monitor (in Tools menu)
