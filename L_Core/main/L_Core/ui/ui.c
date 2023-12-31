// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ui.h"
#include "ui_helpers.h"
#include "images/resource_img.h"

#include "ui-splash.h"
#include "ui-home.h"
#include "ui-variables.h"
#include "ui-sdcard.h"
#include "ui-settings.h"
#include "ui-control.h"
#include "ui-server.h"
#include "ui-pct.h"
#include "ui-bluetooth.h"
#include "ui-sps30.h"

lv_obj_t * keyboard;
lv_obj_t* msgbox;
lv_obj_t* msgbox_label;
uint8_t ui_initialized = 0;
char ui_temp_string[256];

SCREEN_TYPE current_screen;

lv_obj_t* ui_create_screen()
{
	lv_obj_t* screen = lv_obj_create(NULL);
	lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_bg_color(screen, lv_color_hex(UI_BACKGROUND_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	return screen;
}

lv_obj_t* ui_create_titlebar(lv_obj_t* screen, uint32_t color)
{
	lv_obj_t* titlebar = lv_obj_create(screen);	
	lv_obj_clear_flag(titlebar, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE); /// Flags
	lv_obj_set_style_border_width(titlebar, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(titlebar, 0, LV_PART_MAIN);
	lv_obj_set_width(titlebar, LV_PCT(100));
	lv_obj_set_height(titlebar, 30); 
	lv_obj_set_style_bg_color(titlebar, lv_color_hex(color), LV_PART_MAIN);
	lv_obj_align(titlebar, LV_ALIGN_TOP_MID, 0, 0);
	
	lv_obj_t* btnback = ui_create_label(screen, LV_SYMBOL_LEFT, &lv_font_montserrat_14);
	lv_obj_set_style_text_color(btnback, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_obj_add_flag(btnback, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_set_size(btnback, 30, 30);
	lv_obj_add_event_cb(btnback, ui_event_go_home_cb, LV_EVENT_CLICKED, NULL);	
	lv_obj_align(btnback, LV_ALIGN_TOP_LEFT, 10, 5);
	return titlebar;
}

lv_obj_t* ui_create_label(lv_obj_t* parent, char* text, const lv_font_t* font)
{
	lv_obj_t* obj = lv_label_create(parent);	
	lv_obj_set_width(obj, LV_SIZE_CONTENT); /// 1
	lv_obj_set_height(obj, LV_SIZE_CONTENT); /// 1
	lv_label_set_recolor(obj, true);	
	lv_label_set_text_fmt(obj, "%s", text);	
	lv_obj_set_style_text_font(obj, font, LV_PART_MAIN | LV_STATE_DEFAULT);
	return obj;
}


lv_obj_t* ui_create_button(lv_obj_t* parent,
	char* text,
	uint16_t w,
	uint16_t h, 
	uint16_t radius,
	uint32_t color,
	const lv_font_t* font,
	lv_event_cb_t event_button_handler, 
	void* event_data)
{
	lv_obj_t* button = lv_btn_create(parent);
	
	lv_obj_set_width(button, w); /// 1
	lv_obj_set_height(button, h); /// 1
	
	lv_obj_add_flag(button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
	lv_obj_clear_flag(button, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_radius(button, radius, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(button, lv_color_hex(color), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(button, 2, LV_PART_MAIN);
	
	lv_obj_t* label = lv_label_create(button);	
	lv_obj_set_width(label, w-4); /// 1
	lv_obj_set_x(label, 0);
	lv_obj_set_height(label, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(label, LV_ALIGN_CENTER);
	
	lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
	
	lv_label_set_recolor(label, true);
	lv_label_set_text_fmt(label, text);
	lv_obj_set_style_text_font(label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
	if (event_button_handler)	lv_obj_add_event_cb(button, event_button_handler, LV_EVENT_CLICKED, event_data);	
	return button;
}


void messagebox_delay_timer(lv_timer_t * timer)
{
	lv_obj_t* msgbox = (lv_obj_t*)timer->user_data;
	lv_obj_add_flag(msgbox, LV_OBJ_FLAG_HIDDEN);
}

void ui_show_messagebox(MESSAGEBOX_TYPE type, char* msg, uint16_t delay)
{
	lv_color_t color = lv_color_hex(INFO_COLOR);
	if (type == MESSAGEBOX_WARNING) {
		color = lv_color_hex(WARNING_COLOR);
	}
	else if (type == MESSAGEBOX_ERROR) {
		color = lv_color_hex(ERROR_COLOR);
	}
	else {
		
	}
	lv_obj_set_style_bg_color(msgbox, color, LV_PART_MAIN);
	lv_label_set_text(msgbox_label, msg);
	
	if (delay > 0)
	{	
		lv_timer_t * timer = lv_timer_create(messagebox_delay_timer, delay, msgbox);
		lv_timer_set_repeat_count(timer, 1);		
	}
	lv_obj_set_width(msgbox, LV_SIZE_CONTENT);
	lv_obj_clear_flag(msgbox, LV_OBJ_FLAG_HIDDEN);
}
void ui_create_messagebox()
{
	msgbox = lv_obj_create(lv_scr_act());
	lv_obj_clear_flag(msgbox, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE); /// Flags
	lv_obj_set_style_border_width(msgbox, 0, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(msgbox, 128, LV_PART_MAIN);
	lv_obj_set_size(msgbox, LV_PCT(60), 50);
	msgbox_label = ui_create_label(msgbox, "", &font_en_16);
	lv_obj_center(msgbox);	
	lv_obj_add_flag(msgbox, LV_OBJ_FLAG_HIDDEN);
}

void ui_transform_screen(SCREEN_TYPE screen)
{
	if (lv_obj_is_visible(keyboard)) lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
	if (lv_obj_is_visible(msgbox)) lv_obj_add_flag(msgbox, LV_OBJ_FLAG_HIDDEN);
	current_screen = screen;
	switch (screen)
	{
	case SCREEN_HOME:
		lv_scr_load_anim(ui_home_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
		break;
	case SCREEN_SETTINGS:
		lv_scr_load_anim(ui_settings_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
		lv_obj_set_parent(keyboard, ui_settings_screen);
		lv_obj_set_parent(msgbox, ui_settings_screen);	
		break;
	case SCREEN_VARIABLE:
		lv_scr_load_anim(ui_variables_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
		lv_obj_set_parent(keyboard, ui_variables_screen);
		lv_obj_set_parent(msgbox, ui_variables_screen);	
		break;
	case SCREEN_SERVER:
		lv_scr_load_anim(ui_server_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
		lv_obj_set_parent(keyboard, ui_server_screen);
		lv_obj_set_parent(msgbox, ui_server_screen);	
		break;
	case SCREEN_SDCARD:
		lv_scr_load_anim(ui_sdcard_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
		lv_obj_set_parent(keyboard, ui_sdcard_screen);
		lv_obj_set_parent(msgbox, ui_sdcard_screen);
		break;
	case SCREEN_CONTROLS:
		lv_scr_load_anim(ui_control_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
		lv_obj_set_parent(keyboard, ui_control_screen);
		lv_obj_set_parent(msgbox, ui_control_screen);
		break;
	case SCREEN_PCT:
		lv_scr_load_anim(ui_pct_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
		lv_obj_set_parent(keyboard, ui_pct_screen);
		lv_obj_set_parent(msgbox, ui_pct_screen);
		break;
	case SCREEN_BLUETOOTH:
		lv_scr_load_anim(ui_ble_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
		lv_obj_set_parent(keyboard, ui_ble_screen);
		lv_obj_set_parent(msgbox, ui_ble_screen);
		break;
	case SCREEN_SPS30:
		lv_scr_load_anim(ui_sps30_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
		lv_obj_set_parent(keyboard, ui_ble_screen);
		lv_obj_set_parent(msgbox, ui_ble_screen);
		break;
	default:
		break;
	}
}

void ui_timer_handler(lv_timer_t* timer)
{
	switch (current_screen)
	{
	case SCREEN_HOME:
		break;
	case SCREEN_SETTINGS:
		ui_settings_screen_refresh();
		break;
	case SCREEN_VARIABLE:
		break;
	case SCREEN_SERVER:
		break;
	case SCREEN_SDCARD:
		break;
	case SCREEN_CONTROLS:
		break;
	case SCREEN_PCT:
		break;
	case SCREEN_BLUETOOTH:
		ui_bluetooth_screen_refresh();
		break;
	case SCREEN_SPS30:
		break;
	default:
		break;
	}
}

void ui_event_go_home_cb(lv_event_t* e)
{
	ui_transform_screen(SCREEN_HOME);
}

void ui_event_edit_cb(lv_event_t* e)
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
		char* value = (char*)lv_event_get_user_data(e);
		lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
		if(value) strcpy(value, lv_textarea_get_text(obj));
	}
}

float b = 43.555;
void InitUI( void )
{
	lv_disp_t *dispp = lv_disp_get_default();
	lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
	ui_splash_screen_init();
	ui_home_screen_init();
	ui_variables_screen_init();
	ui_server_screen_init();
	ui_sdcard_screen_init();
	ui_settings_screen_init();
	ui_control_screen_init();
	ui_pct_screen_init();
	ui_ble_screen_init();
	ui_sps30_screen_init();

	keyboard = lv_keyboard_create(ui_home_screen);
	lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
	ui_create_messagebox();
	
	lv_scr_load_anim(ui_splash_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
	ui_initialized = 1;	
    //lv_disp_load_scr(ui_main_screen);
	
	// Switch to the main application if OTA has not been started
	vTaskDelay(pdMS_TO_TICKS(2000));
	//lv_scr_load(ui_variables_screen);
	//lv_scr_load_anim(ui_home_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
	ui_transform_screen((SCREEN_TYPE)systemconfig.screen.defaultScreen);

	lv_timer_create(ui_timer_handler, 100, NULL);
	
}
