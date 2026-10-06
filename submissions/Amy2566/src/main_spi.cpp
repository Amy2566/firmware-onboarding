#include <Arduino.h>
#include "BMESPIInterface.h"
#include "LEDController.h"
#include "BMEConstants.h"

LEDController led_controller;

unsigned long last_sensor_read_ms = 0;
unsigned long last_serial_print_ms = 0;
float current_temperature_c = 0.0F;
bool have_temperature = false;

void setup()
{
    Serial.begin(BMEConstants::SERIAL_BAUD);
    led_controller.begin();

    BMESPIInterfaceInstance::create();
    BMESPIInterface& bme_interface = BMESPIInterfaceInstance::instance();

    Serial.println(F("Starting BME280 in SPI mode..."));

    if (!bme_interface.begin())
    {
        Serial.println(F("BME280 not found over SPI."));
        Serial.println(F("Check CS=10, MOSI=11, MISO=12, SCK=13 and power wiring."));

        while (true)
        {
            delay(1000);
        }
    }

    Serial.println(F("BME280 SPI connection successful."));
}

void loop()
{
    const unsigned long now = millis();

    BMESPIInterface& bme_interface = BMESPIInterfaceInstance::instance();

    if (now - last_sensor_read_ms >= BMEConstants::SENSOR_READ_INTERVAL_MS)
    {
        last_sensor_read_ms = now;

        if (bme_interface.readTemperature())
        {
            current_temperature_c = bme_interface.getTemperatureCelsius();
            have_temperature = true;
        }
    }

    if (have_temperature)
    {
        led_controller.update(current_temperature_c);

        if (now - last_serial_print_ms >= BMEConstants::SERIAL_PRINT_INTERVAL_MS)
        {
            last_serial_print_ms = now;
            Serial.print(F("Temperature: "));
            Serial.print(current_temperature_c);
            Serial.println(F(" C"));
        }
    }
}
