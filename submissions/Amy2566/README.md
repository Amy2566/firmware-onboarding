# Firmware Onboarding Submission — Amy2566

PlatformIO/Arduino Uno implementation for the HyTech Racing firmware onboarding project. In the current repository this project is placed directly at `submissions/Amy2566/` so the repository CI can discover `platformio.ini`.

## What it does

- Reads BME280 temperature over I2C (`uno_i2c` environment).
- Reads BME280 temperature over hardware SPI (`uno_spi` environment).
- Uses an `LEDController` system to make an external LED blink faster as temperature rises and slower as temperature falls.
- Keeps hardware-facing BME code in interface classes and decision logic in the system class.

## Project structure

```text
Yang_Amy_Firmware_Onboarding/
├── platformio.ini
├── include/
│   └── BMEConstants.h
├── lib/
│   ├── BMEI2CInterface/
│   │   ├── BMEI2CInterface.h
│   │   └── BMEI2CInterface.cpp
│   ├── BMESPIInterface/
│   │   ├── BMESPIInterface.h
│   │   └── BMESPIInterface.cpp
│   └── LEDController/
│       ├── LEDController.h
│       └── LEDController.cpp
└── src/
    ├── main_i2c.cpp
    └── main_spi.cpp
```

## Wiring used by this implementation

### External LED

- Arduino D6 -> resistor (220-330 ohm) -> LED anode (+)
- LED cathode (-) -> GND

Do not use the Uno's built-in D13 LED for this project if you are also testing hardware SPI, because D13 is the SPI clock pin.

### BME280 I2C

- VIN/VCC -> module-appropriate supply (follow your breakout board labeling)
- GND -> GND
- SDA -> A4
- SCL -> A5
- Default address in `BMEConstants.h`: `0x77`
- If the sensor is not detected, try `0x76`

### BME280 hardware SPI

- CS/CSB -> D10
- MOSI/SDI -> D11
- MISO/SDO -> D12
- SCK/SCL -> D13
- VIN/VCC and GND as required by your breakout board

## Build

From the PlatformIO project folder:

```bash
pio run -e uno_i2c
pio run -e uno_spi
```

Upload the environment you are currently wiring/testing:

```bash
pio run -e uno_i2c -t upload
# or
pio run -e uno_spi -t upload
```

Open the serial monitor at 115200 baud:

```bash
pio device monitor -b 115200
```

## Easy-to-change values

All project-wide values are in `include/BMEConstants.h`, including:

- I2C address
- SPI chip-select pin
- LED pin
- minimum/maximum temperatures
- slow/fast blink intervals
- sensor read/Serial print intervals

The onboarding page does not prescribe exact pin numbers or temperature/blink thresholds, so these are practical defaults and can be changed without touching the rest of the code.
