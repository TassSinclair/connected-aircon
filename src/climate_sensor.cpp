#include "climate_sensor.h"

ClimateSensor::ClimateSensor(Comms& comms, uint8_t pin) : _comms(comms), _dht(), _pin(pin)
{
}

struct ClimateSensor::_dht_sample
{
  const char* status;
  float temperature;
  float humidity;
  float heat_index;
};

void ClimateSensor::connect()
{
  _dht.setup(_pin, DHTesp::DHT22);
}

ClimateSensor::_dht_sample ClimateSensor::_sample()
{
  const char* status = _dht.getStatusString();
  float temperature = _dht.getTemperature();
  float humidity = _dht.getHumidity();
  Serial.print("status: ");
  Serial.print(status);
  Serial.print("\ttemp: ");
  Serial.print(temperature);
  Serial.print("\thumid: ");
  Serial.println(humidity);
  return ClimateSensor::_dht_sample {
    status,
    temperature,
    humidity,
    _dht.computeHeatIndex(temperature, humidity, false)
  };
}

void ClimateSensor::loop()
{
  if (_last_sampling + _dht.getMinimumSamplingPeriod() < millis()) {
    ClimateSensor::_dht_sample sample = _sample();
    if (isnan(sample.temperature) || isnan(sample.humidity))
    {
      return;
    }
    _last_sampling = millis();
    _comms.connect();
    _comms.publishActualTemp(sample.temperature);
    delay(100);
    _comms.publishActualHumidity(sample.humidity);
    delay(100);
  }
}