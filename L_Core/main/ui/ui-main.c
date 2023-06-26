#include "ui-main.h"
lv_obj_t *ui_main_screen;


LV_IMG_DECLARE(img_hyrel_mark);
LV_IMG_DECLARE(img_hyrel_splash);
///////////////////// SCREENS ////////////////////
void ui_main_screen_init(void)
{
	ui_main_screen = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_main_screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_bg_color(ui_main_screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_main_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	lv_obj_t * img = lv_img_create(ui_main_screen); //lv_scr_act()
	lv_img_set_src(img, &img_hyrel_mark);
	lv_obj_align(img, LV_ALIGN_CENTER, 0, -100);
	
	lv_obj_t * preload = lv_spinner_create(ui_main_screen, 1000, 100);	
	lv_obj_set_size(preload, 50, 50);
	static lv_style_t style_spinner;
	lv_style_init(&style_spinner);
	lv_style_set_arc_color(&style_spinner, lv_color_hex(0x00A3FF));
	lv_style_set_bg_color(&style_spinner, lv_color_hex(0x0000ff));
	lv_obj_add_style(preload, &style_spinner, LV_PART_INDICATOR);
	lv_obj_align(preload, LV_ALIGN_CENTER, 0, 50);	
}
