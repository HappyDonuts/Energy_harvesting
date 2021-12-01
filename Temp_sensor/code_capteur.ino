#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup(void)
{
    Serial.begin(9600);
    sensors.begin();
}

void loop(void)
{
    sensors.requestTemperatures();
    Serial.println(sensors.getTempCByIndex(0));
    delay(1000);
}
