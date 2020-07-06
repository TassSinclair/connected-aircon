#include "networking.h"

Networking::Networking(
  const char *wifi_ssid,
  const char *wifi_password,
  const char *hostname) : _client(), _wifi_ssid(wifi_ssid), _wifi_password(wifi_password), _hostname(hostname)
{
}

void Networking::connect()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.mode(WIFI_STA);
    WiFi.hostname(_hostname);
    WiFi.begin(_wifi_ssid, _wifi_password);
    Serial.print("WiFi connecting: ");
    Serial.println(_wifi_ssid);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

WiFiClient& Networking::getClient()
{
  return _client;
}

void Networking::loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    connect();
  }
}
