Documentation for the Modtronix esp32MX-E board.

# STM32F030 Secondary Microcontroller
The esp32MX-E has a secondary STM32F030F4 microcontroller. It controls the PHY reset circuitry, and provides additional I/O via the the I2C port of the ESP32. It can also be programmed with custom firmware.

## Programming
The STM32F030F4 can be programmed via the following methods:
- Serial Port Bootloader
- ST-Link programmer
- By the host ESP32
See below for details.

### Serial Bootloader
The STM32 microcontroller has a built in serial(UART) bootloader, that is activated by pressing the user button while applying power to the esp32MX-E board. Once in the bootloader mode, we need a method to connect to the UART on the STM32. A simple way to do this is to have software on the ESP32 act as a bridge between the STM32 and virtual comm port chip. This enables us to use the STM32CubeProgrammer (STM32CubeProg) to program the STM32 via the UART.

### ST-Link Programmer
To program an STM32 chip using a ST-Link programmer, we need to connect the GND, Reset, SWDIO and SWCLK of the STM32 chip to the corresponding pins of the ST-Link programmer. These pins are all available available on the pin header of the esp32MX-E.

### ESP32 programming the STM32
It is possible for the ESP32 to directly program the STM32 via it's UART bootloader. The ESP32 is connected to the STM32 via I2C. We have to add an I2C command to put the STM32 into bootloader mode. After doing this, the ESP32 will reconfigure the I2C pins connected to the STM32 to a UART. This is possible, seeing that the I2C and UART of the STM32F030 use the same pins. So, during normal operation, these pins on the STM32 are I2C pins, and when starting the STM32 in bootloader mode, they are UART pins.
