#include "ui.h"
#include "ui-sdcard.h"
#include <dirent.h> 
#include <stdio.h>
#include <pthread.h>
#include "main.h"
#include "../devices/display.h"
#include "../server/server.h"

lv_obj_t* ui_server_screen;
bool ui_server_is_screen_share = false;

static uint32_t user_data = 10;
pthread_t taskSnapshot = 0;

void ui_server_event_switch_cb(lv_event_t* e)
{
	lv_obj_t * obj = lv_event_get_target(e);
	bool state = lv_obj_has_state(obj, LV_STATE_CHECKED);
	if (state)
	{
		if (!server_start()) {
			lv_obj_clear_state(obj, LV_STATE_CHECKED);
		}
	}
	else
	{
		server_stop();
		//lv_obj_clear_state(obj, LV_STATE_CHECKED);
	}
	ui_server_is_screen_share = state;
}

void* ui_server_snapshot_handler(void* param)
{	
	char msg[256] = { 0 };
	
	ui_server_is_screen_share =  true;
	int block = 1024;
	while (ui_server_is_screen_share)
	{
		if (!display_screenshot_completed) continue; //nothing when screenshot buffer is not ready
		int fullbuffersize = SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_PIXEL_SIZE;
		sprintf(msg, "SCREEN_START");
		server_send_broadcast((uint8_t*)msg, strlen(msg));
		if (!ui_server_is_screen_share) break;
		vTaskDelay(50);
		for (int i = 0; i < fullbuffersize; i += block) {
			if (!ui_server_is_screen_share) {
				break;
			}
			int len = (i + block) < fullbuffersize ? block : fullbuffersize - i;
			server_send_broadcast((uint8_t*)dispaly_snapshot_buffer + i, len);
			vTaskDelay(0);
		}
		vTaskDelay(50);		
		sprintf(msg, "SCREEN_END");
		server_send_broadcast((uint8_t*)msg, strlen(msg));	
		if (!ui_server_is_screen_share) break;
		vTaskDelay(500);
	}	
	
	pthread_exit(0);
	return NULL;
}

void ui_server_event_screen_onoff_cb(lv_event_t* e)
{
	lv_obj_t * obj = lv_event_get_target(e);
	bool state = lv_obj_has_state(obj, LV_STATE_CHECKED);
	if (state)
	{	
		pthread_create(&taskSnapshot, NULL, ui_server_snapshot_handler, NULL);
		display_screenshot = true;
		lv_obj_invalidate(lv_scr_act());
	}
	else
	{	
		ui_server_is_screen_share  = false; 
	}
}

void ui_server_event_button_cb(lv_event_t* e)
{
	lv_obj_t* text = (lv_obj_t*)lv_event_get_user_data(e);		
	const char* msg = lv_textarea_get_text(text);
	server_send_broadcast((uint8_t*)msg, strlen(msg));
}
void ui_server_screen_init(void)
{	
	ui_server_screen = ui_create_screen();	
	lv_obj_t* titlebar = ui_create_titlebar(ui_server_screen, TITLEBAR_BACKGROUND_COLOR);
	
	lv_obj_t* title_label = lv_label_create(titlebar);	
	lv_obj_set_width(title_label, LV_SIZE_CONTENT);
	lv_obj_set_height(title_label, LV_SIZE_CONTENT);
	lv_label_set_recolor(title_label, true);
	lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_label_set_text(title_label, "SOCKET SERVER");
	lv_obj_set_style_text_font(title_label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);	
	lv_obj_align(title_label, LV_ALIGN_CENTER, 0, 0);
	
	lv_obj_t* panel = lv_obj_create(ui_server_screen);
	lv_obj_set_size(panel, LV_PCT(100), 285);
	lv_obj_set_pos(panel, 0, 33);
	
	
	uint16_t x = 10, y = 10;
	
	lv_obj_t* obj = ui_create_label(panel, "IP: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = ui_create_label(panel, (char*)systemconfig.wifi.ip, &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 160, y);
	
	
	y += 33;
	obj = ui_create_label(panel, "Status: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_switch_create(panel);
	lv_obj_set_pos(obj, 160, y);
	if (servier_is_status()) lv_obj_add_state(obj, LV_STATE_CHECKED);
	else lv_obj_add_state(obj, LV_STATE_CHECKED);
	lv_obj_add_event_cb(obj, ui_server_event_switch_cb, LV_EVENT_VALUE_CHANGED, NULL);
	
	
	y += 40;
	obj = ui_create_label(panel, "Screen Share: ", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y + 10);
	obj = lv_switch_create(panel);
	lv_obj_set_pos(obj, 160, y);
	if (ui_server_is_screen_share) lv_obj_add_state(obj, LV_STATE_CHECKED);
	else lv_obj_clear_state(obj, LV_STATE_CHECKED);
	lv_obj_add_event_cb(obj, ui_server_event_screen_onoff_cb, LV_EVENT_VALUE_CHANGED, NULL);
	
	y += 40;
	lv_obj_t* txt = lv_textarea_create(panel);
	lv_obj_set_size(txt, 300, LV_SIZE_CONTENT);
	lv_obj_set_pos(txt, x, y);
	lv_textarea_set_one_line(txt, true);
	lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
	lv_obj_set_style_border_color(obj, lv_color_hex(UI_TEXTAREA_BORDER_COLOR), LV_PART_MAIN);
	lv_obj_add_event_cb(txt, ui_event_edit_cb, LV_EVENT_ALL, NULL);
	
	obj = ui_create_button(panel, "Send", 60, 33, 2, 0xff0000, &lv_font_montserrat_14, ui_server_event_button_cb, txt);
	lv_obj_set_pos(obj, 320, y);
	
}

