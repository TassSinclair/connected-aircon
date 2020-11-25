#ifndef aircon_remote_climate_sensor_h
#define aircon_remote_climate_sensor_h

#include <comms.h>
#include <DHTesp.h>

class ClimateSensor
{
public:
   ClimateSensor(Comms& comms, const uint8_t pin);

   void connect();
   void loop();

private:
   Comms _comms;
   DHTesp _dht;
   uint8_t _pin;
   struct _dht_sample;
   unsigned long _last_sampling;
   _dht_sample _sample();
};

#endif
