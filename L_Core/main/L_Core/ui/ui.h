#pragma once
#include "lvgl.h"
#include "font/font.h"
#define UI_BACKGROUND_COLOR			0x0

#define MENU_BACKGROUND_COLOR		0xffffff

#define TITLEBAR_BACKGROUND_COLOR	0x0B72AB
#define TITLEBAR_FORE_COLOR			0xFFFFFF
#define TITLEBAR_HEIGHT				30
#define PAGE_BACKGROUND_COLOR		0x222222
#define BUTTON_BACKGROUND_COLOR		0x0B72AB

#define INFO_COLOR					0x477E00
#define WARNING_COLOR				0xEEBA34
#define ERROR_COLOR					0xEE3455

typedef enum
{
	MESSAGEBOX_WARNING,
	MESSAGEBOX_INFO,
	MESSAGEBOX_ERROR,
}MESSAGEBOX_TYPE;

typedef enum
{
	SCREEN_HOME,
	SCREEN_VARIABLE,
	SCREEN_OPC,
	SCREEN_SETTINGS,
	SCREEN_CONTROLS,
	SCREEN_QUALITY,
	SCREEN_SDCARD,
}SCREEN_TYPE;


extern lv_obj_t * keyboard;
void InitUI(void);

lv_obj_t* ui_create_screen();
lv_obj_t* ui_create_titlebar(lv_obj_t* screen, uint32_t color);
lv_obj_t* ui_create_label(lv_obj_t* parent, char* text, const lv_font_t* font);
lv_obj_t* ui_create_button(lv_obj_t* parent,
	char* text,
	uint16_t w,
	uint16_t h, 
	uint16_t radius,
	uint32_t color,
	const lv_font_t* font,
	lv_event_cb_t event_button_handler,
	void* event_data);

void ui_transform_screen(SCREEN_TYPE screen);
void ui_show_messagebox(MESSAGEBOX_TYPE type, char* msg, uint16_t delay);
void event_go_home_cb(lv_event_t* e);

