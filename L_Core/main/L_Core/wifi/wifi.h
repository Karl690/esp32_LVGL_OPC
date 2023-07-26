#include "esp_wifi.h"

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

extern esp_netif_ip_info_t wifi_info;
extern char ipAddress[];

void InitWifi(void);
esp_netif_ip_info_t wifi_get_ip_info();
void wifi_disconnect();
void wifi_connect();