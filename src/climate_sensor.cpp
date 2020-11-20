#include "climate_sensor.h"

ClimateSensor::ClimateSensor(Comms comms, uint8_t dhtPin) : _comms(comms), _dht(dhtPin, DHT22)
{
}

struct ClimateSensor::_dht_reading
{
  float temperature;
  float humidity;
  float heat_index;
};

void ClimateSensor::connect()
{
  _dht.begin();
}

ClimateSensor::_dht_reading ClimateSensor::_read()
{
  float temperature = _dht.readTemperature();
  float humidity = _dht.readHumidity();
  return ClimateSensor::_dht_reading {
    temperature,
    humidity,
    _dht.computeHeatIndex(temperature, humidity, false)
  };
}

void ClimateSensor::loop()
{
  ClimateSensor::_dht_reading reading = _read();
  if (!isnan(reading.temperature))
  {
    _comms.publishActualTemp(reading.temperature);
    delay(50);
  }
  if (!isnan(reading.humidity))
  {
    _comms.publishActualHumidity(reading.humidity);
    delay(50);
  }
}