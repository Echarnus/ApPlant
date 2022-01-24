#ifndef wifi_manager_h
#define wifi_manager_h

#include <string>
#include <Wifi.h>

using namespace std;

namespace RemoteRelais
{
    namespace ESP
    {
        namespace Network
        {
            class WifiManager
            {
            private:
                char *_ssid;
                int status = WL_IDLE_STATUS;
                WiFiClient client;

            public:
                char *getSSID();
                void Connect(char *ssid, char *password);
                void (*OnConnectedEvent)();
                ~WifiManager();
            };
        }; // namespace Network
    };     // namespace ESP
};         // namespace RemoteRelais

#endif