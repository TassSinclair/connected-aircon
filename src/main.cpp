#include <comms.h>
#include <networking.h>
#include "secrets.h"
#include <PubSubClient.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Panasonic.h>

const uint16_t kIrLed = D2;
IRPanasonicAc ac(kIrLed);

Networking networking(wifi_ssid, wifi_password, "connected-aircon");

Comms comms(
  PubSubClient(networking.getClient()),
  mqtt_server
);

void printState() {
  Serial.println("remote is in the following state:");
  Serial.printf("  %s\n", ac.toString().c_str());
}

boolean payloadIs(byte* payload, const char* known) {
  return strcmp((char *) payload, known) == 0;
}

void callback(const char *topic, byte *payload, unsigned int length)
{
  payload[length] = '\0';
  if (strcmp(topic, Comms::POWER_TOPIC) == 0)
  {
    if(payloadIs(payload, Comms::POWER_ON))
    {
      ac.on();
    }
    else if(payloadIs(payload, Comms::POWER_OFF))
    {
      ac.off();
    }
  }
  else if (strcmp(topic, Comms::MODE_TOPIC) == 0)
  {
    if(payloadIs(payload, Comms::MODE_AUTO)) {
      ac.setMode(kPanasonicAcAuto);
    }
    else if(payloadIs(payload, Comms::MODE_HEAT)) {
      ac.setMode(kPanasonicAcHeat);
    }
    else if(payloadIs(payload, Comms::MODE_COOL)) {
      ac.setMode(kPanasonicAcCool);
    }
    else if(payloadIs(payload, Comms::MODE_DRY)) {
      ac.setMode(kPanasonicAcDry);
    }
    else if(payloadIs(payload, Comms::MODE_FAN)) {
      ac.setMode(kPanasonicAcFan);
    }
  }
  else if (strcmp(topic, Comms::FAN_TOPIC) == 0)
  {
    if(payloadIs(payload, Comms::FAN_MAX)) {
      ac.setFan(kPanasonicAcFanMax);
    }
    else if(payloadIs(payload, Comms::FAN_MED)) {
      ac.setFan(kPanasonicAcFanMed);
    }
    else if(payloadIs(payload, Comms::FAN_MIN)) {
      ac.setFan(kPanasonicAcFanMin);
    }
    else if(payloadIs(payload, Comms::FAN_AUTO)) {
      ac.setFan(kPanasonicAcFanAuto);
    }
  }
  else if (strcmp(topic, Comms::SWING_H_TOPIC) == 0)
  {
    if(payloadIs(payload, Comms::SWING_H_FULL_LEFT)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHFullLeft);
    }
    else if(payloadIs(payload, Comms::SWING_H_LEFT)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHLeft);
    }
    else if(payloadIs(payload, Comms::SWING_H_MIDDLE)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHMiddle);
    }
    else if(payloadIs(payload, Comms::SWING_H_RIGHT)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHRight);
    }
    else if(payloadIs(payload, Comms::SWING_H_FULL_RIGHT)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHFullRight);
    }
    else if(payloadIs(payload, Comms::SWING_H_AUTO)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHAuto);
    }
  }
  else if (strcmp(topic, Comms::SWING_V_TOPIC) == 0)
  {
    if(payloadIs(payload, Comms::SWING_V_HIGHEST)) {
      ac.setSwingVertical(kPanasonicAcSwingVHighest);
    }
    else if(payloadIs(payload, Comms::SWING_V_HIGH)) {
      ac.setSwingVertical(kPanasonicAcSwingVHigh);
    }
    else if(payloadIs(payload, Comms::SWING_V_MIDDLE)) {
      ac.setSwingVertical(kPanasonicAcSwingVMiddle);
    }
    else if(payloadIs(payload, Comms::SWING_V_LOW)) {
      ac.setSwingVertical(kPanasonicAcSwingVLow);
    }
    else if(payloadIs(payload, Comms::SWING_V_LOWEST)) {
      ac.setSwingVertical(kPanasonicAcSwingVLowest);
    }
    else if(payloadIs(payload, Comms::SWING_V_AUTO)) {
      ac.setSwingHorizontal(kPanasonicAcSwingVAuto);
    }
  }
  else if (strcmp(topic, Comms::TEMP_TOPIC) == 0)
  {
    ac.setTemp(atoi((char*) payload));
  }
  printState();
  ac.send();
}

void setup() {
  ac.begin();
  delay(200);
  
  ac.off();
  ac.setModel(kPanasonicUnknown);
  ac.setFan(kPanasonicAcFanAuto);
  ac.setMode(kPanasonicAcHeat);
  ac.setTemp(20);
  ac.setSwingVertical(kPanasonicAcSwingVAuto);
  ac.setSwingHorizontal(kPanasonicAcSwingHAuto);
  
  Serial.begin(115200);
  networking.connect();
  comms.connect();
  comms.setCallback(callback);
}

void loop() {
  networking.loop();
  comms.loop();
}