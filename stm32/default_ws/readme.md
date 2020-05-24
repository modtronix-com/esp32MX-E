This folder is a [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) workspace, containing a single project named "default". It contains the default firmware for the STM32F030

This code performs the following main functions:
- Monitors the ESP32 reset pin. If a reset is applied(via reset button on the esp32MX-E or USB programming), it resets the PHY chip(LAN8720)
- Checks when the ESP32 starts outputting the 50MHz PHY clock on the GPIO0 pin, and takes the PHY out of reset.

This the code monitors the GPIO0 pin of the ESP32. This pin will output the 50MHz PHY clock once the ESP32 is configured for Ethernet. If 200 or more pulses are found on the GPIO0 pin within 3ms, the PHY is taken out of reset. The reason we check for 200 pulses in 3ms is to enable GPIO0 to be used to blink the LED when Ethernet is NOT enabled. This allow the esp32MX-E board to be programmed with code that does not use Ethernet, and uses GPIO0 to blink the LED.