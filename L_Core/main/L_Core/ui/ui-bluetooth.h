#pragma once
#include "ui.h"
#include "../bluetooth/ble.h"
extern lv_obj_t* ui_bluetooth_screen;
void ui_bluetooth_screen_init();
void ui_bluetooth_changed_ble_status(uint8_t status);
void ui_bluetooth_add_device(void* dev);
void ui_bluetooth_refresh_devices();
lv_obj_t* ui_bluetooth_get_item_by_device(BleRemoteDevice* dev);
void ui_ble_set_device_status(BleRemoteDevice* dev);
void ui_bluetooth_set_received_data(BleRemoteDevice* dev);