# Ground-Control

This repository contains the device firmware for the Ground-Control project for rocket launching.

 [TTGO T-Beam V1.2](https://www.aliexpress.com/item/1005003088139358.html) with 868MHz radio is used as a hardware.

### TODO
- Rocket configuration and telemetry reading with [Lora](https://en.wikipedia.org/wiki/LoRa)
- Reading logs from launchpad
- folders and their description
- more unified events (transparency from communication/buttons/activity monitors and so on)
- move platform dependent code to common folder

### Known issues
- [MenuScreen.cpp](https://github.com/gaskoin/ground-control/blob/main/main/MenuScreen.cpp) - For now it is not a problem but in the future we may need to implement some kind of view of items that fits on screen. More than ~5 items we will crash the screen now.

### Porting guide:
Code is written with portability in mind and porting mainly require removing usage of esp library and replacing it with other MCU one in listed files. 

Some concepts may need complete redesign as proprietary [esp-now](https://github.com/espressif/esp-now) is used in the project for launchpad communication and interfaces may not fit for other solutions.

#### Platform dependent code:
- [Power.hpp](https://github.com/gaskoin/ground-control/blob/main/main/include/Power.hpp) and [Power.cpp](https://github.com/gaskoin/ground-control/blob/main/main/Power.cpp) -> probably useless in other projects not using AXP2101 PMU.
- [Logger.cpp](https://github.com/gaskoin/ground-control/blob/main/main/Logger.cpp)
- [driver/I2C.hpp](https://github.com/gaskoin/ground-control/blob/main/main/include/drivers/I2C.hpp)
- [Button.cpp](https://github.com/gaskoin/ground-control/blob/main/main/Button.cpp)
- [Communication.hpp](https://github.com/gaskoin/ground-control/blob/main/main/include/Communication.hpp) and [Communication.cpp](https://github.com/gaskoin/ground-control/blob/main/main/Communication.cpp)
- [Display.hpp](https://github.com/gaskoin/ground-control/blob/main/main/include/Display.hpp) and [Display.cpp](https://github.com/gaskoin/ground-control/blob/main/main/Display.cpp) - SSD1306 is used in the project so this may be reimplemented for other displays.
