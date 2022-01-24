#ifndef wifi_manager_cpp
#define wifi_manager_cpp

#include "WifiManager.h"
#include <string>

using namespace std;

namespace RemoteRelais
{
    namespace ESP
    {
        namespace Network
        {
            char *WifiManager::getSSID() {
                return _ssid;
            }

            void WifiManager::Connect(char *ssid, char *password)
            {
                size_t sizeOfSsid = strlen(ssid) + 1;
                _ssid = new char[sizeOfSsid];
                strcpy(_ssid, ssid);

                status = WiFi.begin(ssid, password);
                while (status != WL_CONNECTED && status != WL_CONNECT_FAILED)
                {
                    Serial.println(printf("\nConnecting to network: %s", ssid));
                    Serial.println(printf("Status %i", status));
                    delay(150);
                    status = WiFi.status();
                }

                if (status == WL_CONNECT_FAILED)
                {
                    Serial.println("Couldn't get a wifi connection");
                    Serial.println(status);
                }
                else
                {
                    Serial.println(WiFi.localIP());
                    if (OnConnectedEvent != NULL)
                    {
                        OnConnectedEvent();
                    }
                }
            }

            WifiManager::~WifiManager() {
                delete _ssid;
            }
        }; // namespace Network
    };     // namespace ESP
};         // namespace RemoteRelais

#endif