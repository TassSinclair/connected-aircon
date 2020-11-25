#include <comms.h>
#include <networking.h>
#include <climate_sensor.h>
#include "secrets.h"
#include <PubSubClient.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Panasonic.h>

const uint8_t IR_LED_PIN = D2;
IRPanasonicAc ac(IR_LED_PIN);

Networking networking(wifi_ssid, wifi_password, "connected-aircon");

Comms comms(
  PubSubClient(networking.getClient()),
  mqtt_server
);

const uint8_t DHT_PIN = D7;

ClimateSensor climateSensor(comms, DHT_PIN);

boolean payloadIs(byte* payload, const char* known) {
  return strcasecmp((char *) payload, known) == 0;
}

void printState() {
  Serial.println("remote is in the following state:");
  Serial.printf("  %s\n", ac.toString().c_str());
}

void callback(const char *topic, byte *payload, unsigned int length)
{
  payload[length] = '\0';

  if (strcmp(topic, Comms::POST_MODE_TOPIC) == 0)
  {
    if(payloadIs(payload, Comms::MODE_OFF)) {
      ac.off();
      comms.publishMode(Comms::MODE_OFF);
    }
    else if(payloadIs(payload, Comms::MODE_AUTO)) {
      ac.on();
      ac.setMode(kPanasonicAcAuto);
      comms.publishMode(Comms::MODE_AUTO);
    }
    else if(payloadIs(payload, Comms::MODE_HEAT)) {
      ac.on();
      ac.setMode(kPanasonicAcHeat);
      comms.publishMode(Comms::MODE_HEAT);
    }
    else if(payloadIs(payload, Comms::MODE_COOL)) {
      ac.on();
      ac.setMode(kPanasonicAcCool);
      comms.publishMode(Comms::MODE_COOL);
    }
    else if(payloadIs(payload, Comms::MODE_DRY)) {
      ac.on();
      ac.setMode(kPanasonicAcDry);
      comms.publishMode(Comms::MODE_DRY);
    }
    else if(payloadIs(payload, Comms::MODE_FAN_ONLY)) {
      ac.on();
      ac.setMode(kPanasonicAcFan);
      comms.publishMode(Comms::MODE_FAN_ONLY);
    }
  }
  else if (strcmp(topic, Comms::POST_FAN_TOPIC) == 0)
  {
    if(payloadIs(payload, Comms::FAN_MAXIMUM)) {
      ac.setFan(kPanasonicAcFanMax);
      comms.publishFan(Comms::FAN_MAXIMUM);
    }
    else if(payloadIs(payload, Comms::FAN_MEDIUM)) {
      ac.setFan(kPanasonicAcFanMed);
      comms.publishFan(Comms::FAN_MEDIUM);
    }
    else if(payloadIs(payload, Comms::FAN_MINIMUM)) {
      ac.setFan(kPanasonicAcFanMin);
      comms.publishFan(Comms::FAN_MINIMUM);
    }
    else if(payloadIs(payload, Comms::FAN_AUTO)) {
      ac.setFan(kPanasonicAcFanAuto);
      comms.publishFan(Comms::FAN_AUTO);
    }
  }
  else if (strcmp(topic, Comms::POST_SWING_TOPIC) == 0)
  {
    if(payloadIs(payload, Comms::SWING_AUTO)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHAuto);
      ac.setSwingVertical(kPanasonicAcSwingVAuto);
      comms.publishSwing(Comms::SWING_AUTO);
    }
    if(payloadIs(payload, Comms::SWING_H_FAR_LEFT)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHFullLeft);
      comms.publishSwing(Comms::SWING_H_FAR_LEFT);
    }
    else if(payloadIs(payload, Comms::SWING_H_LEFT)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHLeft);
      comms.publishSwing(Comms::SWING_H_LEFT);
    }
    else if(payloadIs(payload, Comms::SWING_H_MIDDLE)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHMiddle);
      comms.publishSwing(Comms::SWING_H_MIDDLE);
    }
    else if(payloadIs(payload, Comms::SWING_H_RIGHT)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHRight);
      comms.publishSwing(Comms::SWING_H_RIGHT);
    }
    else if(payloadIs(payload, Comms::SWING_H_FAR_RIGHT)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHFullRight);
      comms.publishSwing(Comms::SWING_H_FAR_RIGHT);
    }
    else if(payloadIs(payload, Comms::SWING_H_AUTO)) {
      ac.setSwingHorizontal(kPanasonicAcSwingHAuto);
      comms.publishSwing(Comms::SWING_H_AUTO);
    }
    else if(payloadIs(payload, Comms::SWING_V_HIGHEST)) {
      ac.setSwingVertical(kPanasonicAcSwingVHighest);
      comms.publishSwing(Comms::SWING_V_HIGHEST);
    }
    else if(payloadIs(payload, Comms::SWING_V_HIGH)) {
      ac.setSwingVertical(kPanasonicAcSwingVHigh);
      comms.publishSwing(Comms::SWING_V_HIGH);
    }
    else if(payloadIs(payload, Comms::SWING_V_MIDDLE)) {
      ac.setSwingVertical(kPanasonicAcSwingVMiddle);
      comms.publishSwing(Comms::SWING_V_MIDDLE);
    }
    else if(payloadIs(payload, Comms::SWING_V_LOW)) {
      ac.setSwingVertical(kPanasonicAcSwingVLow);
      comms.publishSwing(Comms::SWING_V_LOW);
    }
    else if(payloadIs(payload, Comms::SWING_V_LOWEST)) {
      ac.setSwingVertical(kPanasonicAcSwingVLowest);
      comms.publishSwing(Comms::SWING_V_LOWEST);
    }
    else if(payloadIs(payload, Comms::SWING_V_AUTO)) {
      ac.setSwingVertical(kPanasonicAcSwingVAuto);
      comms.publishSwing(Comms::SWING_V_AUTO);
    }
  }
  else if (strcmp(topic, Comms::POST_TARGET_TEMP_TOPIC) == 0) {
    int temp = atoi((char*) payload);
    ac.setTemp(temp);
    comms.publishTargetTemp(temp);
  }
  printState();
  ac.send();
}

void setup() {
  Serial.begin(115200);

  ac.begin();
  delay(200);
  ac.off();
  ac.setModel(kPanasonicRkr);
  ac.setFan(kPanasonicAcFanAuto);
  comms.publishFan(Comms::FAN_AUTO);
  ac.setMode(kPanasonicAcAuto);
  comms.publishMode(Comms::MODE_AUTO);
  ac.setTemp(20);
  comms.publishTargetTemp(20);
  ac.setSwingVertical(kPanasonicAcSwingVAuto);
  ac.setSwingHorizontal(kPanasonicAcSwingHAuto);
  comms.publishSwing(Comms::SWING_AUTO);
  
  networking.connect();
  comms.connect();
  comms.setCallback(callback);
  climateSensor.connect();
}

void loop() {
  networking.loop();
  comms.loop();
  climateSensor.loop();
}