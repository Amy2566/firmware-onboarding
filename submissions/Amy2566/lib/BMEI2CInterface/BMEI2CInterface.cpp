#include "BMEI2CInterface.h"

#include <math.h>

bool BMEI2CInterface::begin()
{
    initialized_ = bme_.begin(BMEConstants::BME_I2C_ADDRESS);
    return initialized_;
}

bool BMEI2CInterface::readTemperature()
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

float BMEI2CInterface::getTemperatureCelsius() const
{
    return temperature_c_;
}

bool BMEI2CInterface::isInitialized() const
{
    return initialized_;
}
