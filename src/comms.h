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
   void publishMode(const char* mode);
   void publishActualTemp(float temp);
   void publishActualHumidity(float humidity);
   void publishTargetTemp(int temp);
   void publishFan(const char* fan);
   void publishSwing(const char* swing);

   static const char *POST_MODE_TOPIC;
   static const char *MODE_OFF;
   static const char *MODE_HEAT;
   static const char *MODE_COOL;
   static const char *MODE_FAN_ONLY;
   static const char *MODE_DRY;
   static const char *MODE_AUTO;

   static const char *POST_TARGET_TEMP_TOPIC;

   static const char *POST_FAN_TOPIC;
   static const char *FAN_MINIMUM;
   static const char *FAN_MEDIUM;
   static const char *FAN_MAXIMUM;
   static const char *FAN_AUTO;

   static const char *POST_SWING_TOPIC;
   static const char *SWING_AUTO;
   static const char *SWING_V_HIGHEST;
   static const char *SWING_V_HIGH;
   static const char *SWING_V_MIDDLE;
   static const char *SWING_V_LOW;
   static const char *SWING_V_LOWEST;
   static const char *SWING_V_AUTO;
   static const char *SWING_H_FAR_LEFT;
   static const char *SWING_H_LEFT;
   static const char *SWING_H_MIDDLE;
   static const char *SWING_H_RIGHT;
   static const char *SWING_H_FAR_RIGHT;
   static const char *SWING_H_AUTO;

private:
   PubSubClient _pubSubClient;
   void _publishAvailability();
   const char *_mqtt_server;
   static const char *_MQTT_CLIENT;

   static const char *_GET_STATUS_TOPIC;
   static const char *_STATUS_AVAILABLE;
   static const char *_STATUS_UNAVAILABLE;
   static const char *_GET_POWER_TOPIC;
   static const char *_GET_MODE_TOPIC;
   static const char *_GET_TARGET_TEMP_TOPIC;
   static const char *_GET_ACTUAL_TEMP_TOPIC;
   static const char *_GET_ACTUAL_HUMIDITY_TOPIC;
   static const char *_GET_FAN_TOPIC;
   static const char *_GET_SWING_TOPIC;
};

#endif
