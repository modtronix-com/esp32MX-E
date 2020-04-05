
# Examples using Arduino IDE
This folder contains examples using Arduino for ESP32. For details, see [Github.com/espressif/arduino-esp32](https://github.com/espressif/arduino-esp32)

## Installation
The examples provided in this folder have been build using [v1.0.4](https://github.com/espressif/arduino-esp32/releases/tag/1.0.4) of Arduino-ESP32, which uses v3.2 of the Espressif ESP-IDE. For details on installing it, see this page:  
https://github.com/espressif/arduino-esp32#installation-instructions  

In addition, we also used VS Code, with the Microsoft Arduino Plugin.

## Usage
In the Tools menu of the Arduino IDE, select the "ESP32 Pico Kit" board. We might add the "esp32MX-E" board to future versions of Arduino ESP32, but currently it is not required.

## Additional Modifications
The followig can be done to have the esp32MX-E listed as an available board in the Tools menu of the IDE, but it is NOT required. As mentioned above, using the "ESP32 Pico Kit" board works fine.   

Currently the Arduino-ESP32 board manager does not list the esp32MX-E as an available board by default. To add it to the list of available boards in the Arduino IDE(in Tools menu), the following can to be done:
- After installing the Arduino IDE and the Arduino-ESP32 board, locate the "boards.txt" file in the ESP32 folder. It will be located in the following folder of your Arduino installation: "..\packages\esp32\hardware\esp32\1.0.4"
- Add the code given below to the end of this file(or to top of file after ").

```
esp32mx-e.name=Modtronix ESP32MX-E

esp32mx-e.upload.tool=esptool_py
esp32mx-e.upload.maximum_size=1310720
esp32mx-e.upload.maximum_data_size=327680
esp32mx-e.upload.wait_for_upload_port=true

esp32mx-e.serial.disableDTR=true
esp32mx-e.serial.disableRTS=true

esp32mx-e.build.mcu=esp32
esp32mx-e.build.core=esp32
esp32mx-e.build.variant=esp32mx-e
esp32mx-e.build.board=ESP32MX-E

esp32mx-e.build.f_cpu=240000000L
esp32mx-e.build.flash_mode=dio
esp32mx-e.build.flash_size=4MB
esp32mx-e.build.boot=dio
esp32mx-e.build.partitions=default
esp32mx-e.build.defines=

esp32mx-e.menu.FlashFreq.80=80MHz
esp32mx-e.menu.FlashFreq.80.build.flash_freq=80m
esp32mx-e.menu.FlashFreq.40=40MHz
esp32mx-e.menu.FlashFreq.40.build.flash_freq=40m

esp32mx-e.menu.UploadSpeed.921600=921600
esp32mx-e.menu.UploadSpeed.921600.upload.speed=921600
esp32mx-e.menu.UploadSpeed.115200=115200
esp32mx-e.menu.UploadSpeed.115200.upload.speed=115200
esp32mx-e.menu.UploadSpeed.256000.windows=256000
esp32mx-e.menu.UploadSpeed.256000.upload.speed=256000
esp32mx-e.menu.UploadSpeed.230400.windows.upload.speed=256000
esp32mx-e.menu.UploadSpeed.230400=230400
esp32mx-e.menu.UploadSpeed.230400.upload.speed=230400
esp32mx-e.menu.UploadSpeed.460800.linux=460800
esp32mx-e.menu.UploadSpeed.460800.macosx=460800
esp32mx-e.menu.UploadSpeed.460800.upload.speed=460800
esp32mx-e.menu.UploadSpeed.512000.windows=512000
esp32mx-e.menu.UploadSpeed.512000.upload.speed=512000

esp32mx-e.menu.DebugLevel.none=None
esp32mx-e.menu.DebugLevel.none.build.code_debug=0
esp32mx-e.menu.DebugLevel.error=Error
esp32mx-e.menu.DebugLevel.error.build.code_debug=1
esp32mx-e.menu.DebugLevel.warn=Warn
esp32mx-e.menu.DebugLevel.warn.build.code_debug=2
esp32mx-e.menu.DebugLevel.info=Info
esp32mx-e.menu.DebugLevel.info.build.code_debug=3
esp32mx-e.menu.DebugLevel.debug=Debug
esp32mx-e.menu.DebugLevel.debug.build.code_debug=4
esp32mx-e.menu.DebugLevel.verbose=Verbose
esp32mx-e.menu.DebugLevel.verbose.build.code_debug=5

##############################################################
```