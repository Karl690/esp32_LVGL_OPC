#include "configure.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include <inttypes.h>
#include <string.h>
#include <esp_chip_info.h>
#include <esp_event.h>
#include <esp_flash.h>
#include <esp_ota_ops.h>
#include <soc/rtc.h>
//#include <fmt/core.h>
//#include <fmt/format.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <string>
#include "devices/conf_WT32SCO1-Plus.h"
using namespace std;

//
//extern const char *TAG;
////
//// Semaphore to handle concurrent call to lvgl and other shared stuff
////
//// If you wish to call *any* lvgl function from other threads/tasks
//// you should lock on the very same semaphore!
////
//
//typedef enum { LVGL, BLE } SemaphoreInstance_t;
//
//template<SemaphoreInstance_t I>
//	class lockGuard
//	{
//		static SemaphoreHandle_t sSem;
//
//	public:
//		static bool init()
//		{
//			sSem = xSemaphoreCreateRecursiveMutex();
//			return sSem;
//		}
//
//		lockGuard()
//		{
//			xSemaphoreTakeRecursive(sSem, portMAX_DELAY);
//		}
//
//		~lockGuard()
//		{
//			xSemaphoreGiveRecursive(sSem);
//		}
//	};
//template<SemaphoreInstance_t I> SemaphoreHandle_t lockGuard<I>::sSem;
//
//typedef lockGuard<LVGL>    lvglLock;
//typedef lockGuard<BLE>     bleLock;

#include "helpers/helper_display.hpp"
#include "helpers/helper_ui.hpp"
#include "helpers/helper_ota.hpp"
#include "helpers/ui_callbacks.hpp"
