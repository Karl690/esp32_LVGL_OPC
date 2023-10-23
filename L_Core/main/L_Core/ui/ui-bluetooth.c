#include "main.h"
#include "ui-bluetooth.h"

lv_obj_t* ui_bluetooth_screen;
lv_obj_t* ui_bluetooth_btn_scan;
lv_obj_t* ui_bluetooth_spinner_scan;
lv_obj_t* ui_bluetooth_device_list;
lv_obj_t* ui_bluetooth_device_detail;
lv_obj_t* ui_bluetooth_pair_button;
lv_obj_t* ui_bluetooth_device_name;
lv_obj_t* ui_bluetooth_device_address;
lv_obj_t* ui_bluetooth_send;
lv_obj_t* ui_bluetooth_receive;
lv_obj_t* ui_bluetooth_total;


BleRemoteDevice* selected_device = NULL;
void ui_ble_scan_event_cb(lv_event_t* e) 
{
	//lv_obj_t * label = lv_obj_get_child(target, 0);
	switch (ble_scan_status)
	{
	case BLE_CLIENT_SCAN_READY: ble_scan_start();break;
	case BLE_CLIENT_SCANNING: ble_scan_stop();break;
	default: break;
	}
}

void ui_ble_event_device_item_cb(lv_event_t* e) 
{
	lv_obj_t * target = lv_event_get_target(e);
	BleRemoteDevice* device = (BleRemoteDevice*)lv_event_get_user_data(e);
	lv_label_set_text(ui_bluetooth_device_name, device->device_name);
	lv_label_set_text(ui_bluetooth_device_address, device->address);
	selected_device = device;
	ui_ble_set_device_status(selected_device);
}

void ui_bluetooth_send_event_cb(lv_event_t* e)
{
	
}

void ui_bluetooth_pair_event_cb(lv_event_t* e)
{
	if(!selected_device) return;
	if(!selected_device->is_connected)
		ble_client_connect_device(selected_device);
	else
		ble_client_disconnect_device(selected_device);
}


void ui_ble_set_device_status(BleRemoteDevice* dev)
{
	lv_obj_t* item = ui_bluetooth_get_item_by_device(dev);
	lv_obj_t* label = lv_obj_get_child(item, 0);
	if(dev->is_connected) {
		lv_label_set_text_fmt(label, "#66d800 " LV_SYMBOL_BLUETOOTH " %s #", dev->device_name);
		if(selected_device == dev) {
			lv_obj_set_style_bg_color(ui_bluetooth_pair_button, lv_color_hex(0x3e8300), LV_PART_MAIN);
			label = lv_obj_get_child(ui_bluetooth_pair_button, 0);
			lv_label_set_text(label, "Unpaire device");
		}
	}else {
		lv_label_set_text_fmt(label, "#c4c4c4 " LV_SYMBOL_BLUETOOTH " %s #", dev->device_name);
		if(selected_device == dev) {
			lv_obj_set_style_bg_color(ui_bluetooth_pair_button, lv_color_hex(0x4b4b4b), LV_PART_MAIN);
			label = lv_obj_get_child(ui_bluetooth_pair_button, 0);
			lv_label_set_text(label, "Paire device");
		}
	}
}
void ui_bluetooth_screen_init()
{
	ui_bluetooth_screen = ui_create_screen();	
	lv_obj_t* titlebar = ui_create_titlebar(ui_bluetooth_screen, TITLEBAR_BACKGROUND_COLOR);
	
	lv_obj_t* title_label = lv_label_create(titlebar);	
	lv_obj_set_width(title_label, LV_SIZE_CONTENT);
	lv_obj_set_height(title_label, LV_SIZE_CONTENT);
	lv_label_set_recolor(title_label, true);
	lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_label_set_text(title_label, "BLUETOOTH");
	lv_obj_set_style_text_font(title_label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);	
	lv_obj_align(title_label, LV_ALIGN_CENTER, 0, 0);
	
	uint16_t x, y;
	x = 10; y = 40;
	lv_obj_t* obj = ui_create_button(ui_bluetooth_screen, "SCAN", 100, 30, 3, UI_MENU_ACTIVE_ITEM_COLOR, &lv_font_montserrat_14, ui_ble_scan_event_cb, NULL);	
	lv_obj_set_pos(obj, x, y);	ui_bluetooth_btn_scan = obj;
	
	obj = ui_create_button(ui_bluetooth_screen, "PARING DEVICE", 280, 30, 3, UI_MENU_ACTIVE_ITEM_COLOR, &lv_font_montserrat_14, ui_bluetooth_pair_event_cb, NULL);
	lv_obj_set_pos(obj, 190, y); ui_bluetooth_pair_button = obj;
	
	x = 120; 
	obj = lv_spinner_create(ui_bluetooth_screen, 1000, 60);
	lv_obj_set_size(obj, 30, 30);	
	lv_obj_set_pos(obj, x, y); ui_bluetooth_spinner_scan = obj;
	lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
	x = 10; y = 80;
	ui_bluetooth_device_list = lv_obj_create(ui_bluetooth_screen);
	lv_obj_set_size(ui_bluetooth_device_list, 170, 236);
	lv_obj_set_pos(ui_bluetooth_device_list, x, y); 
	lv_obj_set_style_pad_all(ui_bluetooth_device_list, 2, LV_PART_MAIN);
	
	x = 190;
	ui_bluetooth_device_detail = lv_obj_create(ui_bluetooth_screen);
	lv_obj_set_size(ui_bluetooth_device_detail, 280, 236);
	lv_obj_set_pos(ui_bluetooth_device_detail, x, y); 
	lv_obj_set_style_pad_all(ui_bluetooth_device_detail, 2, LV_PART_MAIN);
	
	x = 10; y = 10;	
	obj = ui_create_label(ui_bluetooth_device_detail, "NAME: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, x, y); 
	obj = ui_create_label(ui_bluetooth_device_detail, "", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 100, y); ui_bluetooth_device_name = obj;
	
	
	x = 10; y += 30;	
	obj = ui_create_label(ui_bluetooth_device_detail, "ADDRESS: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, x, y); 
	obj = ui_create_label(ui_bluetooth_device_detail, "", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 100, y); ui_bluetooth_device_address = obj;
	
	y += 30;
	obj = lv_textarea_create(ui_bluetooth_device_detail);
	lv_obj_set_style_border_color(obj, lv_color_hex(UI_MENU_ACTIVE_ITEM_COLOR), LV_PART_MAIN);
	lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
	lv_textarea_set_one_line(obj, true);
	lv_obj_set_width(obj, 150);
	lv_obj_set_pos(obj, 0, y);
	lv_obj_add_event_cb(obj, ui_event_edit_cb, LV_EVENT_ALL, NULL);	
	
	obj = ui_create_button(ui_bluetooth_device_detail, "SEND", 100, 30, 3, UI_MENU_ACTIVE_ITEM_COLOR, &lv_font_montserrat_14, ui_bluetooth_send_event_cb, NULL);	
	lv_obj_set_pos(obj, 160, y);
	y += 45;
	obj = ui_create_label(ui_bluetooth_device_detail, "RECEIVED: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, x, y); 
	obj = ui_create_label(ui_bluetooth_device_detail, "", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 200, y);  ui_bluetooth_receive = obj;
	
	
	y += 30;
	obj = ui_create_label(ui_bluetooth_device_detail, "TOTAL: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, x, y);
	obj = ui_create_label(ui_bluetooth_device_detail, "", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 200, y); ui_bluetooth_total = obj;
	
	
}

void ui_bluetooth_changed_ble_status(uint8_t status)
{
	if(!ui_initialized) return; // Do nothing util UI is initialized.
	lv_obj_t * label = lv_obj_get_child(ui_bluetooth_btn_scan, 0);
	if (status == BLE_CLIENT_SCANNING)
	{
		lv_obj_clean(ui_bluetooth_device_list);
		selected_device = NULL;
		lv_obj_clear_flag(ui_bluetooth_spinner_scan, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(label, "Stop");
	}
	else
	{
		lv_obj_add_flag(ui_bluetooth_spinner_scan, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(label, "Scan");
	}
}

void ui_bluetooth_add_device(void* dev) {
	if(!ui_initialized) return; // Do nothing util UI is initialized.
	BleRemoteDevice* device = (BleRemoteDevice*)dev;
	lv_obj_t* obj = lv_obj_create(ui_bluetooth_device_list);
	lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_all(obj, 2, LV_PART_MAIN);
	lv_obj_set_size(obj, LV_PCT(100), 30);
	lv_obj_set_pos(obj, 5, (30 + 5) * device->id);
	
	lv_obj_t* label = lv_label_create(obj);
	lv_label_set_recolor(label, true);
	lv_label_set_text_fmt(label, "#c4c4c4 " LV_SYMBOL_BLUETOOTH " %s #", device->device_name);
	lv_obj_align(label, LV_ALIGN_LEFT_MID, 0, 0);
	obj->user_data = (void*)device;
	lv_obj_add_event_cb(obj, ui_ble_event_device_item_cb, LV_EVENT_CLICKED, device);
}

lv_obj_t* ui_bluetooth_get_item_by_device(BleRemoteDevice* dev)
{
	for (uint8_t i = 0; i < lv_obj_get_child_cnt(ui_bluetooth_device_list); i++) {
		lv_obj_t* child = lv_obj_get_child(ui_bluetooth_device_list, i);
		if(child->user_data == dev) {
			return child;
		}
	}
	return NULL;
}

void ui_bluetooth_refresh_devices()
{
	lv_obj_clean(ui_bluetooth_device_list); //remove all device items
	for(uint8_t i = 0; i < ble_client_scaned_device_num; i ++) 
	{
		ui_bluetooth_add_device(&ble_client_remote_device[i]);
	}
}




