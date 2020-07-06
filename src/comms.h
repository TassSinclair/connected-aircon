#ifndef aircon_remote_comms_h
#define aircon_remote_comms_h

#include <PubSubClient.h>

class Comms
{
public:
   Comms(PubSubClient pubSubClient,
         const char *mqtt_server
   );

   void connect();
   void loop();
   void setCallback(MQTT_CALLBACK_SIGNATURE);

   static const char *POWER_TOPIC;
   static const char *POWER_ON;
   static const char *POWER_OFF;

   static const char *MODE_TOPIC;
   static const char *MODE_HEAT;
   static const char *MODE_COOL;
   static const char *MODE_FAN;
   static const char *MODE_DRY;
   static const char *MODE_AUTO;

   static const char *TEMP_TOPIC;

   static const char *FAN_TOPIC;
   static const char *FAN_MIN;
   static const char *FAN_MED;
   static const char *FAN_MAX;
   static const char *FAN_AUTO;

   static const char *SWING_V_TOPIC;
   static const char *SWING_V_HIGHEST;
   static const char *SWING_V_HIGH;
   static const char *SWING_V_MIDDLE;
   static const char *SWING_V_LOW;
   static const char *SWING_V_LOWEST;
   static const char *SWING_V_AUTO;

   static const char *SWING_H_TOPIC;
   static const char *SWING_H_FULL_LEFT;
   static const char *SWING_H_LEFT;
   static const char *SWING_H_MIDDLE;
   static const char *SWING_H_RIGHT;
   static const char *SWING_H_FULL_RIGHT;
   static const char *SWING_H_AUTO;

private:
   PubSubClient _pubSubClient;
   void _publishAvailability();
   const char *_mqtt_server;
   static const unsigned long _MIN_DELAY = 10000;
   static const float _MIN_LOAD_DELTA;
   static const float _MIN_TEMPERATURE_DELTA;
   float _last_load_value;
   float _last_temperature_value;
   unsigned long _last_temperature_publish;
   unsigned long _last_load_publish;
   static const char *_MQTT_CLIENT;
   static const char *_TEMPERATURE_VALUE_TOPIC;
   static const char *_LOAD_VALUE_TOPIC;
   

   
   static const char *_STATUS_TOPIC;
   static const char *_STATUS_AVAILABLE;
   static const char *_STATUS_UNAVAILABLE;
};

#endif
