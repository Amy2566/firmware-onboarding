#include "LEDController.h"

void LEDController::begin()
{
    pinMode(BMEConstants::LED_PIN, OUTPUT);
    digitalWrite(BMEConstants::LED_PIN, LOW);
    led_on_ = false;
    last_toggle_ms_ = millis();
}

unsigned long LEDController::calculateBlinkIntervalMs(float temperature_c) const
{
    // Clamp the temperature so very hot/cold readings stay inside our
    // chosen safe blink-rate range.
    if (temperature_c <= BMEConstants::MIN_TEMP_C)
    {
        return BMEConstants::SLOW_BLINK_INTERVAL_MS;
    }

    if (temperature_c >= BMEConstants::MAX_TEMP_C)
    {
        return BMEConstants::FAST_BLINK_INTERVAL_MS;
    }

    const float temperature_range =
        BMEConstants::MAX_TEMP_C - BMEConstants::MIN_TEMP_C;
    const float position =
        (temperature_c - BMEConstants::MIN_TEMP_C) / temperature_range;

    const float interval_range =
        static_cast<float>(BMEConstants::SLOW_BLINK_INTERVAL_MS -
                           BMEConstants::FAST_BLINK_INTERVAL_MS);

    return static_cast<unsigned long>(
        BMEConstants::SLOW_BLINK_INTERVAL_MS - (position * interval_range));
}

void LEDController::update(float temperature_c)
{
    const unsigned long now = millis();
    const unsigned long blink_interval = calculateBlinkIntervalMs(temperature_c);

    if (now - last_toggle_ms_ >= blink_interval)
    {
        led_on_ = !led_on_;
        digitalWrite(BMEConstants::LED_PIN, led_on_ ? HIGH : LOW);
        last_toggle_ms_ = now;
    }
}
