#include <Arduino.h>
#include "Network/WifiManager.h"
#include <stdlib.h>
#include "nvs_flash.h"
#include "nvs.h"
#include "Constants.h"
#include "Commands.h"

// using namespace RemoteRelais::ESP::Settings;
using namespace RemoteRelais::ESP::Network;

#define NETWORK_LED 12

WifiManager *_wifiManager;

nvs_handle app_nvs_handle;

void onWifiConnected()
{
  Serial.println("Connected to ");
  Serial.println(_wifiManager->getSSID());
}

void setMemory(char *key, char *value)
{
  const char *cstKey = key;
  const char *cstValue = value;
  nvs_set_str(app_nvs_handle, cstKey, cstValue);
  nvs_commit;
}

void getMemoryString(char *key, char *outValue)
{
  size_t required_size;
  const char *cstKey = key;
  nvs_get_str(app_nvs_handle, cstKey, NULL, &required_size);
  nvs_get_str(app_nvs_handle, cstKey, outValue, &required_size);
}

void connectToWifi()
{
  char ssid[30];
  char ssidPassword[30];

  getMemoryString(SSID, ssid);
  getMemoryString(SSID_PASSWORD, ssidPassword);

  if (ssid != NULL || *ssid != '\0' && ssidPassword != NULL || *ssidPassword != '\0')
  {
    Serial.println("Should connect");
    // _wifiManager->Connect(ssid, ssidPassword);
  }
}

void readCommand()
{
  if (Serial.available() > 0)
  {
    String value = Serial.readString();
    // Commands starting with set ssid
    if (value.startsWith(SET_SSID))
    {
      char *key;
      char *command;

      if (value.startsWith(SET_SSID_PASSWORD))
      {
        command = SET_SSID_PASSWORD;
        key = SSID_PASSWORD;
      }
      else if (value.startsWith(SET_SSID))
      {
        command = SET_SSID;
        key = SSID;
      }

      String valueOfCommand = value.substring(strlen(command) + 1, value.length());
      char valueOfCommandArray[valueOfCommand.length()];

      valueOfCommand.toCharArray(valueOfCommandArray, strlen(valueOfCommandArray));
      setMemory(key, valueOfCommandArray);
      Serial.print("Key ");
      Serial.print(key);
      Serial.print(" set to value ");
      Serial.println(valueOfCommandArray);
      connectToWifi();
    }
    else if (value.startsWith(GET_SSID))
    {
      Serial.print("ssid:");
      char ssid[30];
      getMemoryString(SSID, ssid);
      Serial.println(ssid);
    }
  }
}

void setup()
{
  nvs_open(APP_NAMESPACE, NVS_READWRITE, &app_nvs_handle);

  Serial.begin(14400);
  Serial.println("Booted ApPlant");
  char ssid[30];
  char ssidPassword[30];
  getMemoryString(SSID, ssid);
  getMemoryString(SSID_PASSWORD, ssidPassword);
  Serial.println(ssid);
  Serial.println(ssidPassword);
  // setupGPIO();

  _wifiManager = new WifiManager();
  _wifiManager->OnConnectedEvent = &onWifiConnected;

  connectToWifi();
}

void loop()
{
  delay(10);

  readCommand();
}
