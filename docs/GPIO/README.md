

# Pinouts & GPIO Pins #

| ESP32 Pin | Analog | DAC/T | Serial | Function | Note |
| --- | --- | --- | --- | --- | --- | --- |
| GPIO0  | ADC2-1  | Touch-1 |           | **NOT available**, used by Bootloader and PHY | Default **Pull-Up**. Bootloader Mode=0, Run Mode=1 |
| GPIO1  |         |         | TX0       | **Available** if USB comm not used. USB TX.| On the ESP32-NodeMCU, this pin is used for the USB to Serial converter TX pin    |
| GPIO2  | ADC2-2  | Touch-2 |           | **Available** if SD not used. SD Card. 47k PU| Default **Pull-Down**. Must be 0 to enter Bootloader Mode (when GPIO0=0). |
| GPIO3  |         |         | RX0       | **Available** if USB comm not used. USB RX via jumper. | On the ESP32-NodeMCU, this pin is used for the USB to Serial converter RX pin    |
| GPIO4  | ADC2-0  | Touch-0 |           | **Available** to user. |               | 
| GPIO5  |         |         | VSPI-SS   | **Available** by default, LED via Jumper | Default **Pull-up**, use to determine timing of SDIO Slave. |
| GPIO12 | ADC2-5  | Touch-5 | MISO      | **Available** to user. | **JTAG** TDI - Default **Pull-down**. If 1 at PU, sets flash = 1.8V, else standard 3.3V. **MUST be 0** at PU for 3.3V board! |
| GPIO13 | ADC2-4  | Touch-4 | MOSI      | **Available** to user. | **JTAG** TCK    |
| GPIO14 | ADC2-6  | Touch-6 | CLK       | **Available** if SD not used.<br>SD Card.| **JTAG** TMS    |
| GPIO15 | ADC2-3  | Touch-3 | SS        | **Available** if SD not used.<br>SD Card.| **JTAG** TDO - Default **Pull-up**. If 0 at PU, silences boot messages printed by the ROM bootloader.|
| GPIO16 |         |         | RX2       | **Available** to user. | **NOT AVAILABLE** on Wrover, used for PSRAM CS ! |
| GPIO17 |         |         | TX2       | **Available** to user. | **NOT AVAILABLE** on Wrover, used for PSRAM CLK ! |
| GPIO18 |         |         | VSPI-CLK  | **NOT available**, used by PHY |     |
| GPIO19 |         |         | VSPI-MISO | **NOT available**, used by PHY |     |
| GPIO21 |         |         | I2C-SDA   | **NOT available**, used by PHY |     |
| GPIO22 |         |         | I2C-SCL   | **NOT available**, used by PHY |     |
| GPIO23 |         |         | VSPI-MOSI | **NOT available**, used by PHY |     |
| GPIO25 | ADC2-8  | DAC 1   |           | **NOT available**, used by PHY |     |
| GPIO26 | ADC2-9  | DAC 2   |           | **NOT available**, used by PHY |     |
| GPIO27 | ADC2-7  | Touch-7 |           | **NOT available**, used by PHY |     |
| GPIO32 | ADC1-4  | Touch-9 |           | I2C SCL, can also be\\ **used for user I2C** | XTAL32 |
| GPIO33 | ADC1-5  | Touch-8 |           | I2C SCL, can also be\\ **used for user I2C** | XTAL32 |
| GPIO34 | ADC1-6  |         |           | **Available** by default,\\ User Button via Jumper | **Input Only!** No PU or PW! |
| GPIO35 | ADC1-7  |         |           | **Available** to user.\\  Input only | **Input Only!** No PU or PW! |
| GPIO36 | ADC1-0  |         |           | **Available** to user.\\  Input only | **Input Only!** No PU or PW! |
| GPIO39 | ADC1-3  |         |           | **Available** to user.\\  Input only | **Input Only!** No PU or PW! |

## Other Pins that are not available ##
| ESP32 Pin | Analog | DAC/T | Serial | NodeMCU | Wrover | Note |
| --- | --- | --- | --- | --- | --- | --- |
| GPIO6  |         |         |         |     | N/A | **NOT AVAILABLE** used for SPI Flash Wrover/Wroom Modules |
| GPIO7  |         |         |         |     | N/A | **NOT AVAILABLE** used for SPI Flash Wrover/Wroom Modules |
| GPIO8  |         |         |         |     | N/A | **NOT AVAILABLE** used for SPI Flash Wrover/Wroom Modules |
| GPIO9  |         |         | RX1     |     | N/A | **NOT AVAILABLE** used for SPI Flash Wrover/Wroom Modules |
| GPIO10 |         |         | TX1     |     | N/A | **NOT AVAILABLE** used for SPI Flash Wrover/Wroom Modules |
| GPIO11 |         |         |         |     | N/A | **NOT AVAILABLE** used for SPI Flash Wrover/Wroom Modules |
| GPIO16 |         |         | RX2     |     |     | **NOT AVAILABLE** on Wrover, used for PSRAM CS ! |
| GPIO17 |         |         | TX2     |     |     | **NOT AVAILABLE** on Wrover, used for PSRAM CLK ! |
| GPIO37 |         |         |         | N/A | N/A | Pin is NOT available on NodeMCU and Wrover boards!   |
| GPIO38 |         |         |         | N/A | N/A | Pin is NOT available on NodeMCU and Wrover boards!   |


## Input Only Pins: 34-39 ##
Pins 34, 35, 36, 37, 38 and 39 cannot be configured as outputs, but they can be used as either digital inputs, analog inputs, or for other unique purposes. Also note that they do not have internal pull-up or pull-down resistors, like the other I/O pins.

GPIO pins 36-39 are an integral part of the ultra low noise pre-amplifier for the ADC – they are wired up to 270pF capacitors, which help to configure the sampling time and noise of the pre-amp.

## Pin Matrix ##
The ESP32 has a pin matrix allowing any of the I/O pins to be assigned following peripherals:
  * 3 x SPI interfaces
  * 3 x UART interfaces
  * 2 x I2C interfaces
  * 2 x I2S interfaces
  * 16 x PWM outputs

## ADC ##
See ADC pins in table above.

## UART ##
The ESP32 has 3 UART interfaces (0,1 and 2), which provide asynchronous communication (RS232 and RS485) and IrDA support.
Communication speed is up to 5 Mbps. All UARTs provides hardware management of the CTS and RTS signals and software flow
control (XON and XOFF). All of the interfaces can be accessed by the DMA controller or directly by the CPU.

## SPI, HSPI and VSPI ##
The ESP32 has 4 SPI peripherals(SPI0, SPI1, HSPI and VSPI), of which 2(HSPI and VSPI) are available to the user.

SPI Peripherals can be configured for slave and master modes in 1-line full-duplex and 1/2/4-line half-duplex communication modes. 
They support the following general-purpose SPI features:
  * Four timing modes of the SPI format transfer, which depend on the polarity (POL) and the phase (PHA)
  * up to 40 MHz and the divided clocks of 80 MHz
  * up to 64-byte FIFO
  * Each SPI can be served by DMA

SPI0 and SPI1 are used for the external Flash, and are not available to the user!
This leaves two SPI peripherals for general use, HSPI and VSPI. They have default pins(IOMUX pins), but can also be assigned to any other
I/O pin using the Pin Matrix. When using the default pins, speeds up to 80MBits/sec is possible, where 40MBits/sec is the limit when
using the pin matrix. For details, see [[https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/spi_master.html#gpio-matrix-and-iomux|this page]].

The default pins for HSPI are:
  * SS = GPIO 15
  * CLK = GPIO 14
  * MISO = GPIO 12
  * MOSI = GPIO 13

The default pins for VSPI are:
  * SS = GPIO 5
  * CLK = GPIO 18
  * MISO = GPIO 19
  * MOSI = GPIO 23

## I2C ##
The ESP32 has two I2C bus interfaces which can serve as I2C master or slave, depending on the user’s configuration.
The I2C interfaces support:
  * Standard mode (100 kbit/s)
  * Fast mode (400 kbit/s)
  * Up to 5 MHz, yet constrained by SDA pull-up strength
  * 7-bit/10-bit addressing mode
  * Dual addressing mode 
Users can program command registers to control I2C interfaces, so that they have more flexibility.

## I2S ##
Two standard I2S interfaces are available in ESP32. They can be operated in the master or slave mode, in full
duplex and half-duplex communication modes, and can be configured to operate with an 8-/16-/32-/40-/48-bit
resolution as input or output channels. BCK clock frequency, from 10 kHz up to 40 MHz, is supported. When one
or both of the I2S interfaces are configured in the master mode, the master clock can be output to the external
DAC/CODEC.
Both of the I2S interfaces have dedicated DMA controllers. PDM and BT PCM interfaces are supported.

## PWM ##
The Pulse Width Modulation (PWM) controller can be used for driving digital motors and smart lights. The controller
consists of PWM timers, the PWM operator and a dedicated capture sub-module. Each timer provides timing in
synchronous or independent form, and each PWM operator generates a waveform for one PWM channel. The
dedicated capture sub-module can accurately capture events with external timing.

## LED PWM ##
The LED PWM controller can generate 16 independent channels of digital waveforms with configurable periods
and duties. The 16 channels of digital waveforms operate at 80 MHz APB clock, eight of which have the option of using the 8
MHz oscillator clock. Each channel can select a 20-bit timer with configurable counting range, while its accuracy
of duty can be up to 16 bits within a 1 ms period.
The software can change the duty immediately. Moreover, each channel supports step-by-step duty increasing or
decreasing automatically, which makes it useful for the LED RGB color-gradient generator.

## Touch Sensor ##
The ESP32 has 10 capacitive sensing GPIOs.

## Buttons and LEDs ##
The following pins are used for Buttons and LEDs on common ESP32 based boards:

## JTAG Pins ##
Pins 12 to 15 are also used for JTAG functions. If JTAG debugging is required, these pins should be used in such a way that they will be
available for the JTAG programmer/debugger.

## ESP32 Strapping Pins ##
**GPIO0**, **GPIO5** and **GPIO15** have pull-**up** resistors enabled during power up.\\
**GPIO2** and **GPIO12** have pull-**down** resistors enabled during power up.\\
These pull-up and pull-down resistors can be disabled via software once the device is running.

The ESP32 will enter the serial bootloader when GPIO0 is held low on reset. Otherwise it will run the program in flash.

GPIO0 has an internal pullup resistor, so if it is left unconnected then it will pull high.

Many boards use a button marked "Flash" (or "BOOT" on some Espressif development boards) that pulls GPIO0 low when pressed.

GPIO2 must also be either left unconnected/floating, or driven Low, in order to enter the serial bootloader.

## EN(RST) Pin ##
The EN pin is the 3.3V regulator’s enable pin. It’s pulled up, so connect to ground to disable the 3.3V regulator. This means that you can use
this pin connected to a push button to restart your ESP32, for example. This pin does NOT go low during a software reset of the ESP32.
