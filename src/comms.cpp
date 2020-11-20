#include "comms.h"

const char *Comms::_MQTT_CLIENT = "connected-aircon";

const char *Comms::_GET_STATUS_TOPIC = "connected-aircon/get/status";
const char *Comms::_STATUS_AVAILABLE = "available";
const char *Comms::_STATUS_UNAVAILABLE = "unavailable";

const char *Comms::POST_MODE_TOPIC = "connected-aircon/post/mode";
const char *Comms::_GET_MODE_TOPIC = "connected-aircon/get/mode";
const char *Comms::MODE_OFF = "off";
const char *Comms::MODE_HEAT = "heat";
const char *Comms::MODE_COOL = "cool";
const char *Comms::MODE_FAN_ONLY = "fan_only";
const char *Comms::MODE_AUTO = "auto";
const char *Comms::MODE_DRY = "dry";

const char *Comms::POST_TARGET_TEMP_TOPIC = "connected-aircon/post/target-temp";
const char *Comms::_GET_TARGET_TEMP_TOPIC = "connected-aircon/get/target-temp";
const char *Comms::_GET_ACTUAL_TEMP_TOPIC = "connected-aircon/get/actual-temp";
const char *Comms::_GET_ACTUAL_HUMIDITY_TOPIC = "connected-aircon/get/actual-humidity";

const char *Comms::POST_FAN_TOPIC = "connected-aircon/post/fan";
const char *Comms::_GET_FAN_TOPIC = "connected-aircon/get/fan";
const char *Comms::FAN_MAXIMUM = "maximum";
const char *Comms::FAN_MEDIUM = "medium";
const char *Comms::FAN_MINIMUM = "minimum";
const char *Comms::FAN_AUTO = "automatic";


const char *Comms::POST_SWING_TOPIC = "connected-aircon/post/swing";
const char *Comms::_GET_SWING_TOPIC = "connected-aircon/get/swing";
const char *Comms::SWING_AUTO = "swing";
const char *Comms::SWING_V_HIGHEST = "vertical highest";
const char *Comms::SWING_V_HIGH = "vertical high";
const char *Comms::SWING_V_MIDDLE = "vertical middle";
const char *Comms::SWING_V_LOW = "vertical low";
const char *Comms::SWING_V_LOWEST = "vertical lowest";
const char *Comms::SWING_V_AUTO = "vertical swing";
const char *Comms::SWING_H_FAR_LEFT = "horizontal far left";
const char *Comms::SWING_H_LEFT = "horizontal left";
const char *Comms::SWING_H_MIDDLE = "horizontal middle";
const char *Comms::SWING_H_RIGHT = "horizontal right";
const char *Comms::SWING_H_FAR_RIGHT = "horizontal far right";
const char *Comms::SWING_H_AUTO = "horizontal swing";

Comms::Comms(
   PubSubClient pubSubClient,
   const char* mqtt_server
   ): _pubSubClient(pubSubClient), _mqtt_server(mqtt_server)
{
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
      _GET_STATUS_TOPIC,
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
  _pubSubClient.subscribe("connected-aircon/post/#");
  _publishAvailability();
}

void Comms::publishMode(const char* mode)
{
  _pubSubClient.publish(
    _GET_MODE_TOPIC,
    mode
  );
}

void Comms::publishTargetTemp(int temp)
{
  _pubSubClient.publish(
    _GET_TARGET_TEMP_TOPIC,
    String(temp).c_str()
  );
}

void Comms::publishActualTemp(float temp)
{
  _pubSubClient.publish(
    _GET_ACTUAL_TEMP_TOPIC,
    String(temp).c_str()
  );
}

void Comms::publishActualHumidity(float humidity)
{
  _pubSubClient.publish(
    _GET_ACTUAL_HUMIDITY_TOPIC,
    String(humidity).c_str()
  );
}

void Comms::publishFan(const char* fan)
{
  _pubSubClient.publish(
    _GET_FAN_TOPIC,
    fan
  );
}

void Comms::publishSwing(const char* swing)
{
  _pubSubClient.publish(
    _GET_SWING_TOPIC,
    swing
  );
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
    _GET_STATUS_TOPIC,
    _STATUS_AVAILABLE,
    true
  );
}

void Comms::setCallback(MQTT_CALLBACK_SIGNATURE)
{
  _pubSubClient.setCallback(callback);
}
