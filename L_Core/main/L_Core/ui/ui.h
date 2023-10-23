#pragma once
#include "lvgl.h"
#include "font/font.h"

#define SCREEN_WIDTH				480
#define SCREEN_HEIGHT				320
#define SCREEN_PIXEL_SIZE			2
#define SCREEN_LINE_PIXCELS			SCREEN_WIDTH * SCREEN_PIXEL_SIZE

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

#define UI_PANEL_BACGROUND_COLOR		0x333333
#define UI_MENU_ACTIVE_ITEM_COLOR	0x579804
#define UI_MENU_NORMAL_ITEM_COLOR	0x494949
#define UI_TEXTAREA_BORDER_COLOR	0x0B72AB

#define SETTINGS_LINE_SPACE 45

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
	SCREEN_SERVER,
	SCREEN_SETTINGS,
	SCREEN_CONTROLS,
	SCREEN_QUALITY,
	SCREEN_SDCARD,
	SCREEN_PCT,
	SCREEN_BLUETOOTH,
}SCREEN_TYPE;

extern uint8_t ui_initialized;
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
void ui_event_go_home_cb(lv_event_t* e);
void ui_event_edit_cb(lv_event_t* e);

