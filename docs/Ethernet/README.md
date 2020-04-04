
# Ethernet
Ethernet is implemented with the internal Ethernet peripheral of the ESP32. The ESP32 is configured to output a 50MHz clock on the GPIO0 pin. The LAN8720 external PHY chip is used.

## Function of STM32F030
It is important that the PHY chip's reset pin only gets released once the ESP32 is outputting the 50MHz signal on GPIO0. This happens during the Ethernet initialization code. The STM32F030 performs this function. It will monitor the GPIO0 pin for a clock signal. If it detects more than 1000 cycles within a 10ms period, it will release the PHY from reset.