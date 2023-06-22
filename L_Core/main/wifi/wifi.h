#include "esp_wifi.h"

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

extern esp_netif_ip_info_t wifi_info;
extern bool wifi_is_connected;
void wifi_init_sta(void);
esp_netif_ip_info_t wifi_get_ip_info();