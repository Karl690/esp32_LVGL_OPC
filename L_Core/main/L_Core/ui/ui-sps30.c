#include <stdio.h>
#include "ui.h"
#include "K_Core/sps30/sps30.h"
lv_obj_t* ui_sps30_screen;
lv_obj_t* ui_sps30_checksum;
lv_obj_t* ui_sps30_received_size;
lv_obj_t* ui_sps30_start;
lv_obj_t* ui_sps30_stop;
lv_obj_t* ui_sps30_loopread;
lv_obj_t* ui_sps30_mass_pm10;
lv_obj_t* ui_sps30_mass_pm25;
lv_obj_t* ui_sps30_mass_pm40;
lv_obj_t* ui_sps30_mass_pm100;
lv_obj_t* ui_sps30_number_of_pm05;
lv_obj_t* ui_sps30_number_of_pm10;
lv_obj_t* ui_sps30_number_of_pm25;
lv_obj_t* ui_sps30_number_of_pm40;
lv_obj_t* ui_sps30_number_of_pm100;
lv_obj_t* ui_sps30_typical_particle_size;

void ui_sps30_button_click_handler(lv_event_t* e)
{
	uint8_t cmd = (uint8_t)(int) e->user_data;
	sps30_send_command(cmd);
}
void ui_sps30_refresh_timer_handler(lv_timer_t* timer)
{	
	lv_obj_set_style_bg_color(ui_sps30_loopread, lv_color_hex(sps30_config.auto_read ? UI_BUTTON_ACTIVE_COLOR : UI_BUTTON_DISABLE_COLOR), LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui_sps30_start, lv_color_hex(sps30_config.status == SPS30_STATUS_STARTED ? UI_BUTTON_ACTIVE_COLOR : UI_BUTTON_DISABLE_COLOR), LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui_sps30_stop, lv_color_hex(sps30_config.status != SPS30_STATUS_STARTED ? UI_BUTTON_ACTIVE_COLOR : UI_BUTTON_DISABLE_COLOR), LV_PART_MAIN);
	sprintf(ui_temp_string, "%d: %d", sps30_config.checkSum, sps30_config.calcSum);
	lv_label_set_text(ui_sps30_checksum, ui_temp_string);
	sprintf(ui_temp_string, "%d", sps30_config.receivedDataSize);
	lv_label_set_text(ui_sps30_received_size, ui_temp_string);
	
	sprintf(ui_temp_string, "%.3f", sps30_data_info.MassPM10);
	lv_label_set_text(ui_sps30_mass_pm10, ui_temp_string);
	sprintf(ui_temp_string, "%.3f", sps30_data_info.MassPM25);
	lv_label_set_text(ui_sps30_mass_pm25, ui_temp_string);
	sprintf(ui_temp_string, "%.3f", sps30_data_info.MassPM40);
	lv_label_set_text(ui_sps30_mass_pm40, ui_temp_string);
	sprintf(ui_temp_string, "%.3f", sps30_data_info.MassPM100);
	lv_label_set_text(ui_sps30_mass_pm100, ui_temp_string);
	
	sprintf(ui_temp_string, "%.3f", sps30_data_info.NumberOfConnectionPM05);
	lv_label_set_text(ui_sps30_number_of_pm05, ui_temp_string);
	sprintf(ui_temp_string, "%.3f", sps30_data_info.NumberOfConnectionPM10);
	lv_label_set_text(ui_sps30_number_of_pm10, ui_temp_string);
	sprintf(ui_temp_string, "%.3f", sps30_data_info.NumberOfConnectionPM25);
	lv_label_set_text(ui_sps30_number_of_pm25, ui_temp_string);
	sprintf(ui_temp_string, "%.3f", sps30_data_info.NumberOfConnectionPM40);
	lv_label_set_text(ui_sps30_number_of_pm40, ui_temp_string);
	sprintf(ui_temp_string, "%.3f", sps30_data_info.NumberOfConnectionPM100);
	lv_label_set_text(ui_sps30_number_of_pm100, ui_temp_string);
	
	sprintf(ui_temp_string, "%.3f", sps30_data_info.TypicalParticleSize);
	lv_label_set_text(ui_sps30_typical_particle_size, ui_temp_string);
}
void ui_sps30_screen_init(void)
{
	ui_sps30_screen = ui_create_screen();
	lv_obj_t* titlebar = ui_create_titlebar(ui_sps30_screen, TITLEBAR_BACKGROUND_COLOR);
	
	lv_obj_t* title_label = lv_label_create(titlebar);	
	lv_obj_set_width(title_label, LV_SIZE_CONTENT);
	lv_obj_set_height(title_label, LV_SIZE_CONTENT);
	lv_label_set_recolor(title_label, true);
	lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_label_set_text(title_label, "SPS 30");
	lv_obj_set_style_text_font(title_label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);	
	lv_obj_align(title_label, LV_ALIGN_CENTER, 0, 0);
	
	lv_obj_t* panel = lv_obj_create(ui_sps30_screen);
	lv_obj_set_size(panel, LV_PCT(100), 285);
	lv_obj_set_pos(panel, 0, 33);
	
	uint16_t x = 10, y = 10;
	
	lv_obj_t* obj = ui_create_button(panel, "RESET", 60, 30, 3, UI_BUTTON_ACTIVE_COLOR, &lv_font_montserrat_14, ui_sps30_button_click_handler, (void*)SPS30_RESET);
	lv_obj_set_pos(obj, x, y);
	obj = ui_create_button(panel, "START", 60, 30, 3, UI_BUTTON_ACTIVE_COLOR, &lv_font_montserrat_14, ui_sps30_button_click_handler, (void*)SPS30_START);
	x += 70; lv_obj_set_pos(obj, x, y);  ui_sps30_start = obj;
	obj = ui_create_button(panel, "STOP", 60, 30, 3, UI_BUTTON_ACTIVE_COLOR, &lv_font_montserrat_14, ui_sps30_button_click_handler, (void*)SPS30_STOP);
	x += 70; lv_obj_set_pos(obj, x, y);  ui_sps30_stop = obj;
	obj = ui_create_button(panel, "READ", 60, 30, 3, UI_BUTTON_ACTIVE_COLOR, &lv_font_montserrat_14, ui_sps30_button_click_handler, (void*)SPS30_READ);
	x += 70; lv_obj_set_pos(obj, x, y);  
	obj = ui_create_button(panel, "READ LOOP", 90, 30, 3, UI_BUTTON_ACTIVE_COLOR, &lv_font_montserrat_14, ui_sps30_button_click_handler, (void*)SPS30_LOOPREAD);
	x += 70; lv_obj_set_pos(obj, x, y);  ui_sps30_loopread = obj;
	
	y += 35;
	obj = ui_create_label(panel, "CheckSum", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "##", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_checksum = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Received data size:", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_received_size = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Mass Concentration PM1.0 [痢/m設:", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y);  ui_sps30_mass_pm10 = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Mass Concentration PM2.5 [痢/m設:", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_mass_pm25 = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Mass Concentration PM4.0 [痢/m設:", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_mass_pm40 = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Mass Concentration PM10 [痢/m設:", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_mass_pm100 = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Number Concentration PM0.5 [#/cm設", &lv_font_montserrat_14);
	lv_obj_set_width(obj, 300);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_number_of_pm05 = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Number Concentration PM1.0 [#/cm設", &lv_font_montserrat_14);
	lv_obj_set_width(obj, 300);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_number_of_pm10 = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Number Concentration PM2.5 [#/cm設", &lv_font_montserrat_14);
	lv_obj_set_width(obj, 300);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_number_of_pm25 = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Number Concentration PM4.0 [#/cm設", &lv_font_montserrat_14);
	lv_obj_set_width(obj, 300);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_number_of_pm40 = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Number Concentration PM10 [#/cm設", &lv_font_montserrat_14);
	lv_obj_set_width(obj, 300);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_number_of_pm100 = obj;
	
	y += 35;
	obj = ui_create_label(panel, "Typical Particle Size8 [痠]", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 0, y);
	obj = ui_create_label(panel, "###.###", &lv_font_montserrat_14);
	lv_obj_set_pos(obj, 330, y); ui_sps30_typical_particle_size = obj;
	
	lv_timer_create(ui_sps30_refresh_timer_handler, 500, NULL);
}
