
# Ethernet Example

This is a very basic Ethernet example. It will initialize the Ethernet peripherals, and connect to a DHCP server on the network. Once it has connected to the server, it will print the IP address via the virtual COM port on the USB. You can ping the board using this IP address.

To view the output of the virtual COM port, connect the board to the USB port a PC. Look in the PC's device manager what serial port number is created for the virtual COM port. Start a serial port terminal app on the PC, and connect to that serial port using 115200 baud, 8-bit, no parity, and 1 stop and start bit.


## ESP-IDF
This example currently only runs on ESP-IDF v4.0-beta2. And, the "components\esp_eth\src\esp_eth_phy_lan8720.c" file in the ESP-IDF source folder has to be replaced with the file in "esp-idf_v4.0-beta2_replace_files\components\esp_eth\src\esp_eth_phy_lan8720.c". We are working on resolving this issue, and to get the latest v4.0 to work. Hope to have it working soon.

To obtain ESP-IDF v4.0-beta2, follow the guide on this page:
[docs.espressif.com/projects/esp-idf/en/v4.0-beta2/get-started/index.html](https://docs.espressif.com/projects/esp-idf/en/v4.0-beta2/get-started/index.html)  
As mentioned in the "Get ESP-IDF" section, the best way to get it is to use the GIT command:  
`git clone -b v4.0-beta2 --recursive https://github.com/espressif/esp-idf.git`
