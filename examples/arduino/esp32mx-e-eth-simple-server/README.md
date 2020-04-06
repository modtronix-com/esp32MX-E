
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
