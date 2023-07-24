#include "ui.h"
#include "ui-settings.h"
lv_obj_t* ui_settings_screen;
lv_obj_t* ui_settings_bluetooth_page;
lv_obj_t* ui_settings_wifi_page;
lv_obj_t* ui_settings_opc_page;
lv_obj_t* ui_settings_sdcard_page;
lv_obj_t* settings_active_menu = NULL;
lv_obj_t* settings_active_page = NULL;
bool ui_settings_initialized = false;
#define SETTINGS_LINE_SPACE 45
void event_settings_submenu_cb(lv_event_t* e)
{
	if (!ui_settings_initialized) return;
	lv_obj_t * target = lv_event_get_target(e);	
	SETTINGS_SUBMENU_TYPE type = (SETTINGS_SUBMENU_TYPE)(int) e->user_data;
	if (settings_active_menu  == target) return;
	if (settings_active_menu) lv_obj_set_style_bg_color(settings_active_menu, lv_color_hex(SUBMENU_NORMAL_ITEM_COLOR), LV_PART_MAIN);
	lv_obj_set_style_bg_color(target, lv_color_hex(SUBMENU_ACTIVE_ITME_COLOR), LV_PART_MAIN);
	
	if (settings_active_page) lv_obj_add_flag(settings_active_page, LV_OBJ_FLAG_HIDDEN);
	switch (type)
	{
	case SETTINGS_SUBMENU_BLUETOOTH:
		settings_active_page = ui_settings_bluetooth_page;
		lv_obj_clear_flag(ui_settings_bluetooth_page, LV_OBJ_FLAG_HIDDEN);
		break;
	case SETTINGS_SUBMENU_WIFI:
		settings_active_page = ui_settings_wifi_page;
		lv_obj_clear_flag(ui_settings_wifi_page, LV_OBJ_FLAG_HIDDEN);
		break;
	case SETTINGS_SUBMENU_OPC:
		settings_active_page = ui_settings_opc_page;
		lv_obj_clear_flag(ui_settings_opc_page, LV_OBJ_FLAG_HIDDEN);
		break;
	case SETTINGS_SUBMENU_SERIAL:
		//lv_obj_clear_flag(ui_settings_bluetooth_page, LV_OBJ_FLAG_HIDDEN);
		break;
	case SETTINGS_SUBMENU_SDCARD:
		settings_active_page = ui_settings_sdcard_page;
		lv_obj_clear_flag(ui_settings_sdcard_page, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
	settings_active_menu = target;
}

void event_settings_edit_cb(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t * obj = lv_event_get_target(e);
	if (code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED)
	{
		if (keyboard != NULL)
		{
			lv_keyboard_set_textarea(keyboard, obj);
			lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
		}
		
	}
	else if (code == LV_EVENT_READY)
	{
		lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
	}
}

void ui_settings_bluetooth_page_init()
{
	ui_settings_bluetooth_page = lv_obj_create(ui_settings_screen);
	lv_obj_set_size(ui_settings_bluetooth_page, 375, 290);//480-105
	lv_obj_set_pos(ui_settings_bluetooth_page, 102, 32); 
	lv_obj_set_style_pad_all(ui_settings_bluetooth_page, 10, LV_PART_MAIN);
	lv_obj_t* obj = ui_create_label(ui_settings_bluetooth_page, "Bluetooth", &lv_font_montserrat_20);
	lv_obj_set_align(obj, LV_ALIGN_TOP_MID);
	
	uint16_t x = 0, y = 40;
	obj = ui_create_label(ui_settings_bluetooth_page, "Status: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y+10);
	obj = lv_switch_create(ui_settings_bluetooth_page);
	lv_obj_set_pos(obj, 160, y);
	y += SETTINGS_LINE_SPACE;
	obj = ui_create_label(ui_settings_bluetooth_page, "Autostart: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y+10);
	obj = lv_switch_create(ui_settings_bluetooth_page);
	lv_obj_set_pos(obj, 160, y);
}

void ui_settings_wifi_page_init()
{
	ui_settings_wifi_page = lv_obj_create(ui_settings_screen);
	lv_obj_set_size(ui_settings_wifi_page, 375, 290); //480-105
	lv_obj_set_pos(ui_settings_wifi_page, 102, 32); 
	lv_obj_set_style_pad_all(ui_settings_wifi_page, 10, LV_PART_MAIN);
	lv_obj_t* obj = ui_create_label(ui_settings_wifi_page, "WIFI", &lv_font_montserrat_20);
	lv_obj_set_align(obj, LV_ALIGN_TOP_MID);
	
	uint16_t x = 0, y = 40;
	obj = ui_create_label(ui_settings_wifi_page, "Wifi SSID: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	
	obj = lv_textarea_create(ui_settings_wifi_page);
	lv_obj_set_style_border_color(obj, lv_color_hex(SETTINGS_TEXTAREA_BORDER_COLOR), LV_PART_MAIN);
	lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
	lv_textarea_set_one_line(obj, true);	
	lv_obj_set_width(obj, 150);
	lv_obj_set_pos(obj, 160, y);
	lv_obj_add_event_cb(obj, event_settings_edit_cb, LV_EVENT_ALL, NULL);
	
	y += SETTINGS_LINE_SPACE;
	obj = ui_create_label(ui_settings_wifi_page, "Wifi PASSWORD: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_textarea_create(ui_settings_wifi_page);	
	lv_obj_set_style_border_color(obj, lv_color_hex(SETTINGS_TEXTAREA_BORDER_COLOR), LV_PART_MAIN);
	lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
	lv_textarea_set_one_line(obj, true);
	lv_textarea_set_password_mode(obj, true);
	lv_obj_set_width(obj, 150);
	lv_obj_set_pos(obj, 160, y);
	lv_obj_add_event_cb(obj, event_settings_edit_cb, LV_EVENT_ALL, NULL);
	
	y += SETTINGS_LINE_SPACE;
	obj = ui_create_label(ui_settings_wifi_page, "Status: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_switch_create(ui_settings_wifi_page);
	lv_obj_set_pos(obj, 160, y);
	
	y += SETTINGS_LINE_SPACE;
	obj = ui_create_label(ui_settings_wifi_page, "Autostart: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 5);
	obj = lv_switch_create(ui_settings_wifi_page);
	lv_obj_set_pos(obj, 160, y);
}

void ui_settings_opc_page_init()
{
	ui_settings_opc_page = lv_obj_create(ui_settings_screen);
	lv_obj_set_size(ui_settings_opc_page, 375, 290); //480-105
	lv_obj_set_pos(ui_settings_opc_page, 102, 32); 
	lv_obj_set_style_pad_all(ui_settings_opc_page, 10, LV_PART_MAIN);
	lv_obj_t* obj = ui_create_label(ui_settings_opc_page, "OPC", &lv_font_montserrat_20);
	lv_obj_set_align(obj, LV_ALIGN_TOP_MID);
	
	uint16_t x = 0, y = 40;
	obj = ui_create_label(ui_settings_opc_page, "User name: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_textarea_create(ui_settings_opc_page);
	lv_obj_set_style_border_color(obj, lv_color_hex(SETTINGS_TEXTAREA_BORDER_COLOR), LV_PART_MAIN);
	lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
	lv_textarea_set_one_line(obj, true);
	lv_obj_set_width(obj, 150);
	lv_obj_set_pos(obj, 160, y);
	lv_obj_add_event_cb(obj, event_settings_edit_cb, LV_EVENT_ALL, NULL);
	
	y += SETTINGS_LINE_SPACE;
	obj = ui_create_label(ui_settings_opc_page, "User password: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_textarea_create(ui_settings_opc_page);
	lv_obj_set_style_border_color(obj, lv_color_hex(SETTINGS_TEXTAREA_BORDER_COLOR), LV_PART_MAIN);
	lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
	lv_textarea_set_one_line(obj, true);
	lv_textarea_set_password_mode(obj, true);
	lv_obj_set_width(obj, 150);
	lv_obj_set_pos(obj, 160, y);
	lv_obj_add_event_cb(obj, event_settings_edit_cb, LV_EVENT_ALL, NULL);
	
	y += SETTINGS_LINE_SPACE;
	obj = ui_create_label(ui_settings_opc_page, "Status: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_switch_create(ui_settings_opc_page);
	lv_obj_set_pos(obj, 160, y);
	
	y += SETTINGS_LINE_SPACE;
	obj = ui_create_label(ui_settings_opc_page, "Autostart: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_switch_create(ui_settings_opc_page);
	lv_obj_set_pos(obj, 160, y);
}

void ui_settings_sdcard_page_init()
{
	ui_settings_sdcard_page = lv_obj_create(ui_settings_screen);
	lv_obj_set_size(ui_settings_sdcard_page, 375, 290); //480-105
	lv_obj_set_pos(ui_settings_sdcard_page, 102, 32); 
	lv_obj_set_style_pad_all(ui_settings_sdcard_page, 10, LV_PART_MAIN);
	lv_obj_t* obj = ui_create_label(ui_settings_sdcard_page, "SD Card", &lv_font_montserrat_20);
	lv_obj_set_align(obj, LV_ALIGN_TOP_MID);
	
	uint16_t x = 0, y = 40;
	obj = ui_create_label(ui_settings_sdcard_page, "Status: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_switch_create(ui_settings_sdcard_page);
	lv_obj_set_pos(obj, 160, y);
	y += SETTINGS_LINE_SPACE;
	obj = ui_create_label(ui_settings_sdcard_page, "Automount: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_switch_create(ui_settings_sdcard_page);
	lv_obj_set_pos(obj, 160, y);
}

void ui_settings_screen_init()
{
	ui_settings_screen = ui_create_screen();	
	lv_obj_t* titlebar = ui_create_titlebar(ui_settings_screen, TITLEBAR_BACKGROUND_COLOR);
	
	lv_obj_t* title_label = lv_label_create(titlebar);	
	lv_obj_set_width(title_label, LV_SIZE_CONTENT);
	lv_obj_set_height(title_label, LV_SIZE_CONTENT);
	lv_label_set_recolor(title_label, true);
	lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_label_set_text(title_label, "SETTINGS");
	lv_obj_set_style_text_font(title_label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);	
	lv_obj_align(title_label, LV_ALIGN_CENTER, 0, 0);
	
	lv_obj_t* submenu = lv_obj_create(ui_settings_screen);
	lv_obj_clear_flag(submenu, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_size(submenu, 100, 290);
	lv_obj_set_pos(submenu, 0, 30);
	lv_obj_set_style_radius(submenu, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_all(submenu, 2, LV_PART_MAIN);
	
	int y = 2, step = 35;
	lv_obj_t* obj = ui_create_button(submenu, "Bluetooth", LV_PCT(100), 30, 3, SUBMENU_ACTIVE_ITME_COLOR, &lv_font_montserrat_14, event_settings_submenu_cb, (void*)SETTINGS_SUBMENU_BLUETOOTH);
	lv_obj_set_user_data(obj, (void*)SETTINGS_SUBMENU_BLUETOOTH);
	lv_obj_set_pos(obj, 0, y);
	settings_active_menu = obj;
	obj = ui_create_button(submenu, "WIFI", LV_PCT(100), 30, 3, SUBMENU_NORMAL_ITEM_COLOR, &lv_font_montserrat_14, event_settings_submenu_cb, (void*)SETTINGS_SUBMENU_WIFI);
	lv_obj_set_user_data(obj, (void*)SETTINGS_SUBMENU_BLUETOOTH);
	y += step; 	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_button(submenu, "OPC", LV_PCT(100), 30, 3, SUBMENU_NORMAL_ITEM_COLOR, &lv_font_montserrat_14, event_settings_submenu_cb, (void*)SETTINGS_SUBMENU_OPC);
	lv_obj_set_user_data(obj, (void*)SETTINGS_SUBMENU_OPC);
	y += step; lv_obj_set_pos(obj, 0, y);
	obj = ui_create_button(submenu, "SERIAL", LV_PCT(100), 30, 3, SUBMENU_NORMAL_ITEM_COLOR, &lv_font_montserrat_14, event_settings_submenu_cb, (void*)SETTINGS_SUBMENU_SERIAL);
	lv_obj_set_user_data(obj, (void*)SETTINGS_SUBMENU_SERIAL);
	y += step; lv_obj_set_pos(obj, 0, y);
	
	obj = ui_create_button(submenu, "SD CARD", LV_PCT(100), 30, 3, SUBMENU_NORMAL_ITEM_COLOR, &lv_font_montserrat_14, event_settings_submenu_cb, (void*)SETTINGS_SUBMENU_SDCARD);
	lv_obj_set_user_data(obj, (void*)SETTINGS_SUBMENU_SDCARD);
	y += step; lv_obj_set_pos(obj, 0, y);

	ui_settings_bluetooth_page_init();
	settings_active_page = ui_settings_bluetooth_page;
	ui_settings_wifi_page_init();
	lv_obj_add_flag(ui_settings_wifi_page, LV_OBJ_FLAG_HIDDEN);
	ui_settings_opc_page_init();
	lv_obj_add_flag(ui_settings_opc_page, LV_OBJ_FLAG_HIDDEN);
	ui_settings_sdcard_page_init();
	lv_obj_add_flag(ui_settings_sdcard_page, LV_OBJ_FLAG_HIDDEN);
	ui_settings_initialized = true;
	
}

