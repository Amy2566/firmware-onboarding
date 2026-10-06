#include "BMESPIInterface.h"

#include <math.h>

BMESPIInterface::BMESPIInterface()
    : bme_(BMEConstants::BME_SPI_CS_PIN)
{
}

bool BMESPIInterface::begin()
{
    // The object was constructed with a chip-select pin, so the Adafruit
    // library uses hardware SPI (Uno MOSI=11, MISO=12, SCK=13).
    initialized_ = bme_.begin();
    return initialized_;
}

bool BMESPIInterface::readTemperature()
{
    if (!initialized_)
    {
        return false;
    }

    const float new_temperature = bme_.readTemperature();
    if (isnan(new_temperature))
    {
        return false;
    }

    temperature_c_ = new_temperature;
    return true;
}

float BMESPIInterface::getTemperatureCelsius() const
{
    return temperature_c_;
}

bool BMESPIInterface::isInitialized() const
{
    return initialized_;
}
