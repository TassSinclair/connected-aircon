#ifndef aircon_remote_climate_sensor_h
#define aircon_remote_climate_sensor_h

#include <comms.h>
#include <DHT.h>

class ClimateSensor
{
public:
   ClimateSensor(Comms comms, const uint8_t dhtPin);

   void connect();
   void loop();

private:
   Comms _comms;
   DHT _dht;
   struct _dht_reading;
   _dht_reading _read();
};

#endif
