#include "esp_wifi.h"

#define WIFI_SSID "Chaoyou2"
#define WIFI_PASSWORD "1234567890"

extern esp_netif_ip_info_t wifi_info;
extern bool wifi_is_connected;
void wifi_init_sta(void);
esp_netif_ip_info_t wifi_get_ip_info();