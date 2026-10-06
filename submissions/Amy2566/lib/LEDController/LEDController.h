#pragma once

#include <Arduino.h>
#include "BMEConstants.h"

class LEDController
{
public:
    LEDController() = default;

    void begin();
    void update(float temperature_c);

    // Kept public so the temperature-to-rate logic can be tested separately.
    unsigned long calculateBlinkIntervalMs(float temperature_c) const;

private:
    bool led_on_ = false;
    unsigned long last_toggle_ms_ = 0;
};
