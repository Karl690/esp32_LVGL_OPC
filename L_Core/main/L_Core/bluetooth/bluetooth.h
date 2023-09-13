#pragma once

#include "esp_bt.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"


#define spp_sprintf(s,...)         sprintf((char*)(s), ##__VA_ARGS__)
#define SPP_DATA_MAX_LEN           (512)
#define SPP_CMD_MAX_LEN            (20)
#define SPP_STATUS_MAX_LEN         (20)
#define SPP_DATA_BUFF_MAX_LEN      (2*1024)
///Attributes State Machine
enum {
	SPP_IDX_SVC,

	SPP_IDX_SPP_DATA_RECV_CHAR,
	SPP_IDX_SPP_DATA_RECV_VAL,

	SPP_IDX_SPP_DATA_NOTIFY_CHAR,
	SPP_IDX_SPP_DATA_NTY_VAL,
	SPP_IDX_SPP_DATA_NTF_CFG,

	SPP_IDX_SPP_COMMAND_CHAR,
	SPP_IDX_SPP_COMMAND_VAL,

	SPP_IDX_SPP_STATUS_CHAR,
	SPP_IDX_SPP_STATUS_VAL,
	SPP_IDX_SPP_STATUS_CFG,

#ifdef SUPPORT_HEARTBEAT
	SPP_IDX_SPP_HEARTBEAT_CHAR,
	SPP_IDX_SPP_HEARTBEAT_VAL,
	SPP_IDX_SPP_HEARTBEAT_CFG,
#endif

	SPP_IDX_NB,
};

void ble_init();

bool ble_enable();
void ble_disable();
bool ble_send_data(uint8_t* data, uint16_t size);