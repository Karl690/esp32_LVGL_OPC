#pragma once
#include "ui.h"
#include "../bluetooth/ble.h"
extern lv_obj_t* ui_ble_screen;
extern lv_obj_t* ui_ble_server_client_text;
extern lv_obj_t* ui_ble_sever_send_text;
extern lv_obj_t* ui_ble_sever_receive_text;
extern lv_obj_t* ui_ble_server_total_text;

void ui_ble_screen_init();
void ui_ble_changed_ble_status(uint8_t status);
void ui_ble_add_device(void* dev);
void ui_ble_refresh_devices();
lv_obj_t* ui_ble_get_item_by_device(BleRemoteDevice* dev);
void ui_ble_set_device_status(BleRemoteDevice* dev);
void ui_ble_set_received_data(BleRemoteDevice* dev);