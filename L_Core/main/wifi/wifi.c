#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"

#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "wifi.h"
/* The examples use WiFi configuration that you can set via project configuration menu

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_ESP_MAXIMUM_RETRY  3 //CONFIG_ESP_MAXIMUM_RETRY

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static const char *TAG = "wifi station";

static int s_retry_num = 0;

esp_netif_ip_info_t wifi_info;
bool wifi_is_connected = false;
static void event_handler(void* arg,
	esp_event_base_t event_base,
	int32_t event_id,
	void* event_data)
{
	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
		wifi_is_connected = false;
		esp_wifi_connect();
	}
	else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
		wifi_is_connected = false;
		if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
			esp_wifi_connect();
			s_retry_num++;
			ESP_LOGI(TAG, "retry to connect to the AP");
		}
		else {
			xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
		}
		ESP_LOGI(TAG, "connect to the AP fail");
	}
	else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
		wifi_is_connected = true;
		ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
		
		memcpy(&wifi_info, &event->ip_info, sizeof(esp_netif_ip_info_t));
		ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
		s_retry_num = 0;
		xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
	}
	else if (event_base == WIFI_EVENT) {
		// FMOD
		wifi_is_connected = false;
		ESP_LOGE(TAG, "Unhandled WIFI_EVENT event_id = %d", (int)event_id);
	}
	else if (event_base == IP_EVENT) {
		wifi_is_connected = false;
		// FMOD
		ESP_LOGE(TAG, "Unhandled IP_EVENT event_id = %d", (int)event_id);
	}
}
void wifi_init_sta(void)
{
	wifi_is_connected = false;
	s_wifi_event_group = xEventGroupCreate();

	ESP_ERROR_CHECK(esp_netif_init());

	ESP_ERROR_CHECK(esp_event_loop_create_default());
	esp_netif_create_default_wifi_sta();

	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));

	esp_event_handler_instance_t instance_any_id;
	esp_event_handler_instance_t instance_got_ip;
	ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
		ESP_EVENT_ANY_ID,
		&event_handler,
		NULL,
		&instance_any_id));
	ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
		IP_EVENT_STA_GOT_IP,
		&event_handler,
		NULL,
		&instance_got_ip));

	wifi_config_t wifi_config = {
		.sta = {
			.ssid = WIFI_SSID,
			.password = WIFI_PASSWORD,
		/* Setting a password implies station will connect to all security modes including WEP/WPA.
		 * However these modes are deprecated and not advisable to be used. Incase your Access point
		 * doesn't support WPA2, these mode can be enabled by commenting below line */
			//.threshold.authmode = WIFI_AUTH_WPA2_PSK,
	},
	};
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
	ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE)); // FMOD
	ESP_ERROR_CHECK(esp_wifi_start());

	ESP_LOGI(TAG, "wifi_init_sta finished.");

	/* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
	 * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
	EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
		WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
		pdFALSE,
		pdFALSE,
		portMAX_DELAY);

	/* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
	 * happened. */
	if (bits & WIFI_CONNECTED_BIT) {
		ESP_LOGI(TAG,
			"connected to ap SSID:%s password:%s",
			WIFI_SSID,
			WIFI_PASSWORD);
	}
	else if (bits & WIFI_FAIL_BIT) {
		ESP_LOGI(TAG,
			"Failed to connect to SSID:%s, password:%s",
			WIFI_SSID,
			WIFI_PASSWORD);
	}
	else {
		ESP_LOGE(TAG, "UNEXPECTED EVENT");
	}

#if 0   // FMOD
	/* The event will not be processed after unregister */
	ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
	ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
	vEventGroupDelete(s_wifi_event_group);
#endif
	
}

esp_netif_ip_info_t wifi_get_ip_info()
{
	esp_netif_ip_info_t ip_info;
	esp_netif_get_ip_info((esp_netif_t*)IP_EVENT_STA_GOT_IP, &ip_info);
	printf("My IP: " IPSTR "\n", IP2STR(&ip_info.ip));
	printf("My GW: " IPSTR "\n", IP2STR(&ip_info.gw));
	printf("My NETMASK: " IPSTR "\n", IP2STR(&ip_info.netmask));	
	return ip_info;
}
