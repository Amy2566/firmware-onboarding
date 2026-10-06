#pragma once

#include <Adafruit_BME280.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

class BMESPIInterface
{
public:
    BMESPIInterface();

    bool begin();
    bool readTemperature();
    float getTemperatureCelsius() const;
    bool isInitialized() const;

private:
    Adafruit_BME280 bme_;
    float temperature_c_ = 0.0F;
    bool initialized_ = false;
};

using BMESPIInterfaceInstance = etl::singleton<BMESPIInterface>;
