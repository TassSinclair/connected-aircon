#ifndef aircon_remote_networking_h
#define aircon_remote_networking_h

#include <WiFiClient.h>
#include <ESP8266WiFi.h>

class Networking
{
public:
   Networking(
      const char *wifi_ssid,
      const char *wifi_password,
      const char *host_name
   );

   void connect();
   void loop();
   WiFiClient& getClient();

private:
   WiFiClient _client;
   const char *_wifi_ssid;
   const char *_wifi_password;
   const char *_host_name;
};

#endif
