#pragma once

#include <Arduino.h>

namespace BMEConstants
{
    // Serial monitor
    constexpr unsigned long SERIAL_BAUD = 115200;

    // BME280 I2C address. Adafruit boards normally use 0x77.
    // If your sensor is not detected over I2C, try 0x76 instead.
    constexpr uint8_t BME_I2C_ADDRESS = 0x77;

    // Arduino Uno hardware SPI pins are fixed:
    // MOSI = 11, MISO = 12, SCK = 13. We only need to choose CS.
    constexpr uint8_t BME_SPI_CS_PIN = 10;

    // Use an external LED on a pin that does not conflict with SPI.
    constexpr uint8_t LED_PIN = 6;

    // Read/print temperature at a comfortable rate for the Serial Monitor.
    constexpr unsigned long SENSOR_READ_INTERVAL_MS = 250;
    constexpr unsigned long SERIAL_PRINT_INTERVAL_MS = 500;

    // LED behavior: colder -> slower blink, warmer -> faster blink.
    constexpr float MIN_TEMP_C = 10.0F;
    constexpr float MAX_TEMP_C = 35.0F;
    constexpr unsigned long SLOW_BLINK_INTERVAL_MS = 1000;
    constexpr unsigned long FAST_BLINK_INTERVAL_MS = 150;
}
