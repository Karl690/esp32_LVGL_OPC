#include "main.h"
#include "wifi/wifi.h"
#ifdef USE_OPC
#include "open62541/opc.h"
#endif
#include "taskmanager.h"
#include "devices/display.h"
#include "ui/ui.h"
const char *TAG = "WT32-SqLn";
//string device_info();
extern "C" void app_main(void)
{
	esp_log_level_set(TAG, ESP_LOG_DEBUG); // enable DEBUG logs for this App
    //Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
	wifi_init_sta();
	
#ifdef USE_OPC
	opc_task();
#endif
//	lcd.init(); // Initialize LovyanGFX
//	//lcd.setRotation(1);
//	lcd.initDMA(); // Init DMA
	//lv_init(); // Initialize lvglss

	if (lv_display_init() != ESP_OK) // Configure LVGL
	{
		ESP_LOGE(TAG, "LVGL setup failed!!!");
	}
#ifndef  AAAA	
	
	ui_init();
//	lv_label_set_text(ui_Splash_Screen_Title, TAG);
	lv_scr_load(ui_Splash_Screen);
	
	// Switch to the main application if OTA has not been started
	vTaskDelay(pdMS_TO_TICKS(5000));
	
	lv_scr_load(ui_Opc_Screen);
	lv_label_set_text_fmt(ipAddressLabel, "#ff00ff %d.%d.%d.%d #", IP2STR(&wifi_info.ip));
	InitTaskManager();
#endif
	
}
#ifdef AAA
string device_info()
{	
	
	/* Print chip information */
	string s_chip_info;
	esp_chip_info_t chip_info;
	uint32_t flash_size;
	esp_chip_info(&chip_info);

	// CPU Speed - 80Mhz / 160 Mhz / 240Mhz
	rtc_cpu_freq_config_t conf;
	rtc_clk_cpu_freq_get_config(&conf);

	multi_heap_info_t info;    
	heap_caps_get_info(&info, MALLOC_CAP_SPIRAM);
	float psramsize = (info.total_free_bytes + info.total_allocated_bytes) / (1024.0 * 1024.0);

	const esp_partition_t *running = esp_ota_get_running_partition();
	esp_app_desc_t running_app_info;
    
	if (esp_ota_get_partition_description(running, &running_app_info) == ESP_OK) {
		s_chip_info += "Project Name : \n" + running_app_info.project_name) + "\n";
		s_chip_info += fmt::format("Firmware Ver : {}\n", running_app_info.version);
	}
	s_chip_info += fmt::format("IDF Version  : {}\n\n", esp_get_idf_version());

	s_chip_info += fmt::format("Controller   : {} Rev.{}\n", CONFIG_IDF_TARGET, chip_info.revision);  
	//s_chip_info += fmt::format("\nModel         : {}",chip_info.model); // esp_chip_model_t type
	s_chip_info += fmt::format("CPU Cores    : {}\n", (chip_info.cores == 2) ? "Dual Core" : "Single Core");
	s_chip_info += fmt::format("CPU Speed    : {}Mhz\n", conf.freq_mhz);
	if (esp_flash_get_size(NULL, &flash_size) == ESP_OK) {
		s_chip_info += fmt::format("Flash Size   : {}MB {}\n",
			flash_size / (1024 * 1024),
			(chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "[embedded]" : "[external]");
	}
	s_chip_info += fmt::format("PSRAM Size   : {}MB {}\n",
		static_cast<int>(round(psramsize)),
		(chip_info.features & CHIP_FEATURE_EMB_PSRAM) ? "[embedded]" : "[external]");

	s_chip_info += fmt::format("Connectivity : {}{}{}\n",
		(chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "2.4GHz WIFI" : "NA",
		(chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
		(chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
	//s_chip_info += fmt::format("\nIEEE 802.15.4 : {}",string((chip_info.features & CHIP_FEATURE_IEEE802154) ? "YES" : "NA"));

	//ESP_LOGE(TAG,"\n%s",device_info().c_str());
	return s_chip_info;

}
#endif