
# Ethernet Example

This is a very basic Ethernet example. It will perform Ethernet initialization, and connect to a DHCP server on the network. Once it has connected to the server, it will print the IP address via the virtual COM port on the USB. You can ping the board using this IP address.

To view the output of the virtual COM port, connect the board to the USB port a PC. Look in the PC's device manager what serial port number is created for the virtual COM port. Start a serial port terminal app on the PC, and connect to that serial port using 115200 baud, 8-bit, no parity, and 1 stop and start bit.


## ESP-IDF
It was built and tested with v4.0 of ESP-IDF, the official development framework for the ESP32 chip from Espressif(manufacturers of theee ESP32). For details, see [github.com/espressif/esp-idf](https://github.com/espressif/esp-idf)

See the [README.md](../README.md) file in the upper level 'examples/idf' directory for more information about examples, and how to install ESP-IDF.

## Building and Flashing
See the "Getting Started" section in the [ESP-IDF guide](https://docs.espressif.com/projects/esp-idf/en/v4.0/get-started/index.html) for details how to build and flash the project. Basically, all that has to be done is:
- Install ESP-IDF v4.0 on your computer
- Start the "ESP-IDF Command Prompt", will be installed in step above
- Change working directory to this folder (../examples/idf/ethernet)
- Connect the esp32MX-E to a USB port on your PC. Note in device manager what virtual COM port is created for it. The next step assumes it is 5.
- Build the code, program the esp32MX-E board, and start the serial port monitor with the command(using your COM port number):  
`idf.py -p COM5 flash monitor`
- When done, the serial port monitor should start with debug output
- Connect the esp32MX-E to a network. A message should be printed in the serial port monitor, stating that a network cable was plugged in, and a DHCP connection made. The IP address assigned to the esp32MX-E will be given.
 