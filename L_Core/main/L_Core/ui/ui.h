#include "lvgl.h"

void InitUI(void);

lv_obj_t* ui_create_label(lv_obj_t* parent, char* text, const lv_font_t* font);
lv_obj_t* ui_create_button(lv_obj_t* parent,
	char* text,
	uint16_t w,
	uint16_t h, 
	uint16_t radius,
	uint32_t color,
	const lv_font_t* font,
	lv_event_cb_t event_button_handler);