#include "ui.h"
#include "ui-variables.h"
lv_obj_t* ui_home_screen;

static void event_variables_cb(lv_event_t* e)
{
	lv_scr_load_anim(ui_variables_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
}

void ui_home_screen_init(void)
{
	
	LV_IMG_DECLARE(btn_wifi);
	LV_IMG_DECLARE(btn_bluetooth);
	LV_IMG_DECLARE(btn_opc);
	LV_IMG_DECLARE(btn_quality);
	LV_IMG_DECLARE(btn_variables);
	LV_IMG_DECLARE(btn_automation);
	LV_IMG_DECLARE(btn_about);
	
	ui_home_screen = lv_obj_create(NULL);
	//lv_obj_clear_flag(ui_home_screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_bg_color(ui_home_screen, lv_color_hex(UI_BACKGROUND_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_home_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	lv_obj_t* obj = lv_imgbtn_create(ui_home_screen);
	lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &btn_about, NULL);
	lv_obj_set_size(obj, 17, 17);
	lv_obj_set_pos(obj, 457, 6);
	
	obj = lv_imgbtn_create(ui_home_screen);
	lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &btn_wifi, NULL);
	lv_obj_set_size(obj, 124, 83);
	lv_obj_set_pos(obj, 41, 59); 
	
	obj = lv_imgbtn_create(ui_home_screen);
	lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &btn_bluetooth, NULL);
	lv_obj_set_size(obj, 124, 83);
	lv_obj_set_pos(obj, 177, 59);
	
	obj = lv_imgbtn_create(ui_home_screen);
	lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &btn_opc, NULL);
	lv_obj_set_size(obj, 124, 83);
	lv_obj_set_pos(obj, 313, 59);
	
	obj = lv_imgbtn_create(ui_home_screen);
	lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &btn_quality, NULL);
	lv_obj_set_size(obj, 124, 83);
	lv_obj_set_pos(obj, 41, 164);

	obj = lv_imgbtn_create(ui_home_screen);
	lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &btn_automation, NULL);
	lv_obj_set_size(obj, 124, 83);
	lv_obj_set_pos(obj, 177, 164);
	
	obj = lv_imgbtn_create(ui_home_screen);
	lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &btn_variables, NULL);
	lv_obj_set_size(obj, 124, 83);
	lv_obj_set_pos(obj, 313, 164);
	lv_obj_add_event_cb(obj, event_variables_cb, LV_EVENT_CLICKED, NULL);
	
	
	lv_obj_t* banner = ui_create_label(ui_home_screen, "#ffffff ©2023, PCT Systems. All rights reserved. #", &lv_font_montserrat_14);
	lv_obj_align(banner, LV_ALIGN_BOTTOM_MID, 0, -10);
	

}