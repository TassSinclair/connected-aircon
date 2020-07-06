#include "comms.h"

const char *Comms::_MQTT_CLIENT = "connected-aircon";

const char *Comms::_STATUS_TOPIC = "connected-aircon/status";
const char *Comms::_STATUS_AVAILABLE = "available";
const char *Comms::_STATUS_UNAVAILABLE = "unavailable";

const char *Comms::POWER_TOPIC = "connected-aircon/power";
const char *Comms::POWER_ON = "on";
const char *Comms::POWER_OFF = "off";

const char *Comms::MODE_TOPIC = "connected-aircon/mode";
const char *Comms::MODE_HEAT = "heat";
const char *Comms::MODE_COOL = "cool";
const char *Comms::MODE_FAN = "fan";
const char *Comms::MODE_AUTO = "auto";
const char *Comms::MODE_DRY = "dry";

const char *Comms::TEMP_TOPIC = "connected-aircon/temp";

const char *Comms::FAN_TOPIC = "connected-aircon/fan";
const char *Comms::FAN_MAX = "max";
const char *Comms::FAN_MED = "med";
const char *Comms::FAN_MIN = "min";
const char *Comms::FAN_AUTO = "auto";

const char *Comms::SWING_V_TOPIC = "connected-aircon/swing-v";
const char *Comms::SWING_V_HIGHEST = "highest";
const char *Comms::SWING_V_HIGH = "high";
const char *Comms::SWING_V_MIDDLE = "middle";
const char *Comms::SWING_V_LOW = "low";
const char *Comms::SWING_V_LOWEST = "lowest";
const char *Comms::SWING_V_AUTO = "auto";

const char *Comms::SWING_H_TOPIC = "connected-aircon/swing-h";
const char *Comms::SWING_H_FULL_LEFT = "full-left";
const char *Comms::SWING_H_LEFT = "left";
const char *Comms::SWING_H_MIDDLE = "middle";
const char *Comms::SWING_H_RIGHT = "right";
const char *Comms::SWING_H_FULL_RIGHT = "full-right";
const char *Comms::SWING_H_AUTO = "auto";

Comms::Comms(
   PubSubClient pubSubClient,
   const char* mqtt_server
   ): _pubSubClient(pubSubClient), _mqtt_server(mqtt_server)
{
   _last_load_value = -1;
   _last_load_publish = 0;
}


void Comms::connect()
{
  while (!_pubSubClient.connected())
  {
    _pubSubClient.setServer(_mqtt_server, 1883);
    Serial.print("MQTT connecting: ");
    Serial.println(_mqtt_server);
    if (_pubSubClient.connect(
      _MQTT_CLIENT,
      _STATUS_TOPIC,
      1,
      true,
      _STATUS_UNAVAILABLE))
    {
      Serial.println("MQTT connected");
    }
    else
    {
      Serial.print("MQTT failed, reason: ");
      Serial.println(_pubSubClient.state());
      Serial.println("MQTT retrying in 5 seconds");
      delay(5000);
    }
  }
  _pubSubClient.subscribe("connected-aircon/#");
  _publishAvailability();
}

void Comms::loop()
{
  if (!_pubSubClient.connected())
  {
    connect();
  }
  _pubSubClient.loop();
}

void Comms::_publishAvailability()
{
  _pubSubClient.publish(
    _STATUS_TOPIC,
    _STATUS_AVAILABLE,
    true
  );
}

void Comms::setCallback(MQTT_CALLBACK_SIGNATURE)
{
  _pubSubClient.setCallback(callback);
}
