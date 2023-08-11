#include "ui.h"
#include "ui-pct.h"
#include <dirent.h> 
#include <stdio.h>
#include <pthread.h>
#include "main.h"
#include "../pct/pct.h"

char ui_pct_prog_titles[][40] = { 
	"PROGRAM PARAMETERS", "LEVEL SENSOR", "SECS INTERFACE", "FREQUENCY", "TRANSDUCER"
};


UI_PCT_DISPLAY_INFO ui_pct_prog_param_displays[] = { 
	{"ENTER NEW PROCESS NUMBER IF DESIRED", "", &pct_progamming_info.process_number},
	{"ENTER PASSWORD PLEASE", "(ANY NUMBER BETWEEN 0 AND 65535)", &pct_progamming_info.password},	
	{"PROCESS TEMPERATURE (IN DEGREES C)", "", &pct_progamming_info.process_temperature},
	{"MINIMUM TEMPERATURE TO START A PROCESS", "(IN DEGREES C)", &pct_progamming_info.min_temperature},
	{"MAXIMUM TEMPERATURE TO START A PROCESS", "(IN DEGREES C)", &pct_progamming_info.max_temperature},
	{"ENTER PROCESS TIME IN SECONDS", "IE 10 MINUTES = 600 SECONDS", &pct_progamming_info.process_time},
	{"ENTER POWER IN PERCENT (IE 1 TO 100%) ", "(ANYTHING OVER 100 IS SAME AS 100)", &pct_progamming_info.power_level},
	{"ENTER MINIMUM POWER VALUE TO QUALIFY", "ARRAY1 PROCESS (100 TO 500 TYPICAL)", &pct_progamming_info.min_qualify_power_array_1},
	{"ENTER MINIMUM POWER VALUE TO QUALIFY", "ARRAY2 PROCESS (100 TO 500 TYPICAL)", &pct_progamming_info.min_qualify_power_array_2},
	{"TYPE OF TRANSDUCER FOR SENSING HEAT", "0=RTD 1=(TC EMBEDDED IN BATH)", &pct_progamming_info.transducer_type},
	{"TYPE OF REMOTE ON/OFF SIGNAL", "0=NORMAL 1=QUICK OFF", &pct_progamming_info.remote_interface_type},
	{"HEATER POWER FACTOR (USUALLY 200 TO 900)", "", &pct_progamming_info.heater_power_factor},
};


UI_PCT_DISPLAY_INFO ui_pct_level_senser_displays[] = { 
	{ "LL SWITCH POLARITY FOR NORMAL OPERATION", "(0 = N.O. SWITCH 1 = N.C. SWITCH)", &pct_level_senser_info.liquid_level_set_point},
};

UI_PCT_DISPLAY_INFO ui_pct_secs_displays[] = { 
	{ "TYPE OF SERIAL NTERFACE 0=REMOTE PANEL", "1=REMOTE RS232/QC 2=SECSII", &pct_secs_info.serial_interface},
	{ "AUTOMATIC DATA LOGGING DURING PROCESS", "0=OFF 1=ON (ONCE PER SECOND)", &pct_secs_info.datalog_flag},
	{ "ENTER DESIRED BAUD RATE", "300, 600, 1200, 2400, 4800, 9600", &pct_secs_info.baud_rate},
	{ "ENTER MEGASONIC SECS 1 DEVICE ID", "(0 TO 32767)", &pct_secs_info.device_id},
	{ "ENTER T1 FOR SECS 1 (1 TO 100 IN .1 SEC)", "(INTER CHARACTER TIME-OUT)", &pct_secs_info.transmission_character_pause},
	{ "ENTER T2 FOR SECS 1 (2 TO 250 IN .1 SEC)", "(REPLY TIME-OUT)", &pct_secs_info.transmission_message_pause},
	{ "ENTER NUMBER OF RETRIES WHILE SENDING A", "SECS 2 MESSAGE (0 TO 31)", &pct_secs_info.transmission_retry_pause},
	{ "DUPE BLOCK CHECKING ", "0=NO 1=YES", &pct_secs_info.dupe_block},
};

UI_PCT_DISPLAY_INFO ui_pct_frequency_displays[] = { 
	{ "ENTER DESIRED FREQUENCY FOR ARRAY 1", "XTAL 1 (IN .1 KILO HERTZ)", &pct_frequency_info.array1_freqency },
	{ "ENTER DESIRED FREQUENCY FOR ARRAY 2", "XTAL 1 (IN .1 KILO HERTZ)", &pct_frequency_info.array2_freqency},
	{ "ENTER NEW PASSWORD NOW, IF DESIRED", "(ANY NUMBER BETWEEN 0 AND 65534)", &pct_frequency_info.password},
	{ "FREQUENCY WOBBLE FACTOR FOR ARRAY1 ", "(0 TO 10, 10 IS NORMAL)", &pct_frequency_info.array1_w_factor},
	{ "FREQUENCY WOBBLE FACTOR FOR ARRAY2 ", "(0 TO 10, 10 IS NORMAL)", &pct_frequency_info.array2_freqency},
};

UI_PCT_DISPLAY_INFO ui_pct_transducer_displays[] = { 
	{ "ENTER TIME IN SECONDS FOR THE AMP TO BE", "ON BEFORE MUXING (1 NORMAL 3 MAX)", &pct_transducer_param_info.mulitplexer_dwell_time},
	{ "ENTER NUMBER OF CRYSTALS PER ARRAY", "CAUTION!!! MAKE SURE YOU KNOW", &pct_transducer_param_info.crystal_count},
	{ "MINIMUM FREQUENCY FOR TUNING ARRAY1", "IN .1 KHZ (05000 TYPICAL)", &pct_transducer_param_info.array1_min_frequency},
	{ "MAXIMUM FREQUENCY FOR TUNING ARRAY1", "IN .1 KHZ (07500 TYPICAL)", &pct_transducer_param_info.array1_max_frequency},
	{ "MINIMUM FREQUENCY FOR TUNING ARRAY2", "IN .1 KHZ (05000 TYPICAL)", &pct_transducer_param_info.array2_min_frequency},
	{ "MAXIMUM FREQUENCY FOR TUNING ARRAY2", "IN .1 KHZ (07500 TYPICAL)", &pct_transducer_param_info.array2_max_frequency},
	{ "SPEED WHEN AUTO TUNING THE XTALS", "1 TO 50. 35 NORMAL	50 IS SLOW", &pct_transducer_param_info.tuning_speed},
};

UI_PCT_DISPLAY_INFO ui_pct_status_displays[] = { 
	{ "HYPER-CLEAN READY TO RUN PROCESS #%02d TIME=%04d POWER=%03d PERCENT", "", NULL },
	{ "PROCESSING AT XXX PERCENT POWER %04d SECONDS REMAINING IN PROCESS MUX = %d", "", NULL },
	{ "TANK LIQUID LEVEL LOW, PLEASE FILL BEFORE STARTING PROCESS", "", NULL },
	{ "HYPER CLEAN PROCESS ABORTED, CHECK LIQUID LEVEL, (PRESS STOP TO CLEAR ALARM)", "", NULL },
	{ "HYPER CLEAN PROCESS COMPLETE WAFERS ARE CLEAN, PRESS `STOP` TO STOP ALARM", "", NULL },
	{ "HYPER CLEAN SYSTEM DETECTED OVERTEMP CONDITION,	!!! PROCESS ABORTED !!!", "", NULL },
	{ "HEATER DISABLED PRESS `F2` TO RE_ENABLE", "", NULL },
	{ "TUNING XTAL X ARRAY1, PWR=%05d FREQ=%05d PEAK FREQ=%05d PEAK POWER=%04d TIME=%03d", "0=NO 1=YES", NULL },
	{ "TUNING XTAL X ARRAY2, PWR=%05d FREQ=%05d PEAK FREQ=%05d PEAK POWER=%04d TIME=%03d", "0=NO 1=YES", NULL },
	{ "HYPERCLEAN FINISHED TUNING TRANSDUCERS PRESS `STOP`", "", NULL},
	{ "HYPER CLEAN SYSTEM DETECTED LOW POWER CONDITION, ON ARRAY1 ! ! PROCESS ABORTED ! ! ", "", NULL},
	{ "HYPER CLEAN SYSTEM DETECTED LOW POWER CONDITION, FOR ARRAY2 ! ! PROCESS ABORTED ! ! ", "", NULL},
	{ "CAUTION! SYSTEM DETECTED MEMORY LOSS! NOW USING FACTORY DEFAULT SETTINGS ", "", NULL},
	{ "SYSTEM INITIALIZATION IN PROGRESS PLEASE WAIT...XX SECONDS REMAINING ", "", NULL},
};

UI_PCT_DISPLAY_INFO ui_pct_diagnostic_displays[] = { 
	{ "ARRAY1=%03d ARRAY2=%03d PTEMP=%02d ATEMP=%02d", "LIQUID=%03d OT=%01d CONTACTOR=%03d DUTY=%03d", NULL},
	{ "FRQ1 PRG=%05d ACT=%05d DAC=%04d LOCK=%01d", "FRQ2 PRG=%05d ACT=%05d DAC=%04d LOCK=%01d", NULL},
	{ "ARAY1 FPOWER=%05d", "ARAY2 FPOWER=%05d", NULL},
	{ "XT1A=%05d XT2A=%05d XT3A=%05d XT4A=%05d", "XT5A=%05d XT6A=%05d XT7A=%05d XT8A=%05d", NULL},
	{ "XT1B=%05d XT2B=%05d XT3B=%05d XT4B=%05d", "XT5B=%05d XT6B=%05d XT7B=%05d XT8B=%05d", NULL},
	{ "PWR1=%05d PWR2=%05d PWR3=%05d PWR4=%05d", "PWR5=%05d PWR6=%05d PWR7=%05d PWR8=%05d", NULL},
	{ "PWR1=%05d PWR2=%05d PWR3=%05d PWR4=%05d", "PWR5=%05d PWR6=%05d PWR7=%05d PWR8=%05d", NULL},
	{ "OVERTEMP SET=%04d OT-TC=%04d OT-SENSE=%01d", "LIQUID LEVEL=%01d RTD=%04d TEMP=%03d CF=%01d", NULL},
	{ "PTEMP=%03d ATEMP=%03d PFACT=%05d DUTY=%03d", "ADJUSTED FACTOR=%05d DELTA FACTOR=%05d", NULL},
	{ "ALARM=%01d LL INTERLOCK=%02d LLSENSE=%04d", "RAW LIQUID LEVEL INPUT %04d", NULL},
	{ "MUXTIMER=%02d MUX=%01d DAC3=%04d DAC4=%04d", "POWER=%01d FREQ=%05d MUXTIME=%05d", NULL},
	{ "HYPERSONIC SOFTWARE VER FTUNE1JB 05-12-98", "PCT SYSTEMS TEL#510-657-4412 FAX-0112", NULL}
};

int8_t	  ui_pct_prog_display_index = 0;
int8_t	  ui_pct_prog_display_variable_index = 0;

int8_t	  ui_pct_diag_display_variable_index = 0;

lv_obj_t* ui_pct_screen;
lv_obj_t* ui_pct_panel_title_01;
lv_obj_t* ui_pct_panel_title_02;
lv_obj_t* ui_pct_panel_01; //display program or status
lv_obj_t* ui_pct_panel_02; //display diagnostic

lv_obj_t* ui_pct_panel_01_line_01;
lv_obj_t* ui_pct_panel_01_line_02;
lv_obj_t* ui_pct_panel_01_value;

lv_obj_t* ui_pct_panel_02_line_01;
lv_obj_t* ui_pct_panel_02_line_02;

lv_obj_t* ui_pct_btn_prog;
lv_obj_t* ui_pct_btn_diag;

lv_obj_t* ui_pct_btn_prog_left;
lv_obj_t* ui_pct_btn_prog_right;

lv_obj_t* ui_pct_keyboard[UI_PCT_KEYBOARD_RIGHT+1];

char digit[10];
uint8_t ui_pct_active_display = UI_PCT_DISPLAY_STATUS;
uint8_t ui_pct_active_prog_array_size = 0;

UI_PCT_DISPLAY_INFO* prog_display = NULL;
uint16_t prog_value = 0;

uint8_t ui_pct_active_status = UI_PCT_STATUS_RIQUID_LEVEL;


void ui_pct_keyboard_enable(bool enable)
{
	for (uint8_t i = 0; i < UI_PCT_KEYBOARD_RIGHT; i++) {
		//lv_obj_t * label = lv_obj_get_child(ui_pct_keyboard[i], 0);
		if (i == UI_PCT_KEYBOARD_PROG || i == UI_PCT_KEYBOARD_DIAG || i == UI_PCT_KEYBOARD_LEFT || i == UI_PCT_KEYBOARD_RIGHT) continue;
		if (enable) {
			lv_obj_add_flag(ui_pct_keyboard[i], LV_OBJ_FLAG_CLICKABLE);			
		}
		else {
			lv_obj_clear_flag(ui_pct_keyboard[i], LV_OBJ_FLAG_CLICKABLE);
		}
	}
}

void ui_pct_update_status_display()
{
	lv_label_set_text(ui_pct_panel_01_line_01, (const char*)ui_pct_status_displays[ui_pct_active_status].line_one);
	lv_label_set_text(ui_pct_panel_01_line_02, (const char*)ui_pct_status_displays[ui_pct_active_status].line_two);		
	lv_label_set_text(ui_pct_panel_01_value, "");	
}

void ui_pct_update_diagnostic_display()	
{
	lv_label_set_text(ui_pct_panel_02_line_01, (const char*)ui_pct_diagnostic_displays[ui_pct_diag_display_variable_index].line_one);
	lv_label_set_text(ui_pct_panel_02_line_02, (const char*)ui_pct_diagnostic_displays[ui_pct_diag_display_variable_index].line_two);		
	//lv_label_set_text(ui_pct_panel_02_value, "");	
}

void ui_pct_update_prog_display()
{	
	switch (ui_pct_prog_display_index)
	{
	case UI_PCT_PROG_PARAM_DISPLAY:				
		prog_display = ui_pct_prog_param_displays; 
		ui_pct_active_prog_array_size = sizeof(ui_pct_prog_param_displays) / sizeof(UI_PCT_DISPLAY_INFO);
		break;
	case UI_PCT_LEVEL_SENSOR_DISPLAY:			
		prog_display = ui_pct_level_senser_displays; 
		ui_pct_active_prog_array_size = sizeof(ui_pct_level_senser_displays) / sizeof(UI_PCT_DISPLAY_INFO);
		break;
	case UI_PCT_SECS_INFTERFACE_DISPLAY:		
		prog_display = ui_pct_secs_displays; 
		ui_pct_active_prog_array_size = sizeof(ui_pct_secs_displays) / sizeof(UI_PCT_DISPLAY_INFO);
		break;
	case UI_PCT_FREQUENCY_DISPLAY:				
		prog_display = ui_pct_frequency_displays; 
		ui_pct_active_prog_array_size = sizeof(ui_pct_frequency_displays) / sizeof(UI_PCT_DISPLAY_INFO);
		break;
	case UI_PCT_PROGRAMMING_TRANSDUCER_DISPLAY:	
		prog_display = ui_pct_transducer_displays;
		ui_pct_active_prog_array_size = sizeof(ui_pct_transducer_displays) / sizeof(UI_PCT_DISPLAY_INFO);
		break;		
	}
	
	lv_label_set_text(ui_pct_panel_01_line_01, "");
	lv_label_set_text(ui_pct_panel_01_line_02, "");
	lv_label_set_text(ui_pct_panel_01_value, "");
	
	if (prog_display && strlen((const char*)prog_display[ui_pct_prog_display_variable_index].line_one) > 0)
	{
		lv_label_set_text(ui_pct_panel_01_line_01, (const char*)prog_display[ui_pct_prog_display_variable_index].line_one);
		lv_label_set_text(ui_pct_panel_01_line_02, (const char*)prog_display[ui_pct_prog_display_variable_index].line_two);
		sprintf(digit, "%05d", *(int*)prog_display[ui_pct_prog_display_variable_index].value);	
		lv_label_set_text(ui_pct_panel_01_value, (const char*)digit);
		prog_value = *prog_display[ui_pct_prog_display_variable_index].value;
	}
}


void ui_pct_update_display_status()
{
	switch (ui_pct_active_display)
	{
	case UI_PCT_DISPLAY_STATUS:
		lv_label_set_text(ui_pct_panel_title_01, "PROGRAM STATUS");
		lv_obj_set_style_border_width(ui_pct_panel_01, 1, LV_PART_MAIN);
		lv_obj_set_style_border_width(ui_pct_panel_02, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_color(ui_pct_btn_prog, lv_color_hex(UI_PCT_BTN_BG_NORMAL_COLOR), LV_PART_MAIN);
		lv_obj_set_style_bg_color(ui_pct_btn_diag, lv_color_hex(UI_PCT_BTN_BG_NORMAL_COLOR), LV_PART_MAIN);
		lv_obj_add_flag(ui_pct_btn_prog_left, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(ui_pct_btn_prog_right, LV_OBJ_FLAG_HIDDEN);
		ui_pct_prog_display_variable_index = 0;
		ui_pct_prog_display_index = 0;
		ui_pct_update_status_display();
		ui_pct_keyboard_enable(false);
		break;
	case UI_PCT_DISPLAY_PROG:
		lv_label_set_text(ui_pct_panel_title_01, "PROGRAM PARAMETERS");
		lv_obj_set_style_border_width(ui_pct_panel_01, 1, LV_PART_MAIN);
		lv_obj_set_style_border_width(ui_pct_panel_02, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_color(ui_pct_btn_prog, lv_color_hex(UI_PCT_BTN_BG_ACTIVE_COLOR), LV_PART_MAIN);
		lv_obj_set_style_bg_color(ui_pct_btn_diag, lv_color_hex(UI_PCT_BTN_BG_NORMAL_COLOR), LV_PART_MAIN);
		lv_obj_clear_flag(ui_pct_btn_prog_left, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(ui_pct_btn_prog_right, LV_OBJ_FLAG_HIDDEN);
		ui_pct_prog_display_variable_index = 0;
		ui_pct_prog_display_index = 0;
		ui_pct_update_prog_display();
		ui_pct_keyboard_enable(true);
		break;
	case UI_PCT_DISPLAY_DIAG:
		lv_obj_set_style_border_width(ui_pct_panel_01, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(ui_pct_panel_02, 1, LV_PART_MAIN);
		lv_obj_set_style_bg_color(ui_pct_btn_prog, lv_color_hex(UI_PCT_BTN_BG_NORMAL_COLOR), LV_PART_MAIN);
		lv_obj_set_style_bg_color(ui_pct_btn_diag, lv_color_hex(UI_PCT_BTN_BG_ACTIVE_COLOR), LV_PART_MAIN);
		lv_obj_add_flag(ui_pct_btn_prog_left, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(ui_pct_btn_prog_right, LV_OBJ_FLAG_HIDDEN);
		ui_pct_update_diagnostic_display();
		ui_pct_keyboard_enable(false);
		break;
	}
}



void ui_pct_event_prog_direction_cb(lv_event_t* e)
{
	if (ui_pct_active_display != UI_PCT_DISPLAY_PROG) return;
	uint8_t code = (uint8_t)(int)lv_event_get_user_data(e);
	
	ui_pct_prog_display_variable_index = 0;
	if (code) //right
	{
		if (ui_pct_prog_display_index + 1 <= UI_PCT_PROGRAMMING_TRANSDUCER_DISPLAY) {
			ui_pct_prog_display_index++;
			lv_label_set_text(ui_pct_panel_title_01, ui_pct_prog_titles[ui_pct_prog_display_index]);
			ui_pct_update_prog_display();
		}
	}else //left
	{
		if (ui_pct_prog_display_index - 1 >= 0) {
			ui_pct_prog_display_index--;
			lv_label_set_text(ui_pct_panel_title_01, ui_pct_prog_titles[ui_pct_prog_display_index]);
			ui_pct_update_prog_display();
		}		
	}
	
}

void ui_pct_prog_display_update_value(uint8_t keycode)
{
	//uint16_t value = *(uint16_t*)prog_display[ui_pct_prog_display_variable_index].value;
	if (keycode >= UI_PCT_KEYBOARD_0 && keycode <= UI_PCT_KEYBOARD_9)
	{
		if (prog_value / 10000 > 0) return;
		prog_value = prog_value * 10 + keycode;
	}
	else if (keycode == UI_PCT_KEYBOARD_BACKSPACE)
	{
		prog_value /= 10;
	}
	else if (keycode == UI_PCT_KEYBOARD_ESC)
	{
		prog_value = 0;
	}
	else if (keycode == UI_PCT_KEYBOARD_ENTER)
	{
		*(uint16_t*)prog_display[ui_pct_prog_display_variable_index].value = prog_value;
		ui_show_messagebox(MESSAGEBOX_INFO, "Set the value successful.", 2000);
	}
	sprintf(digit, "%05d", prog_value);	
	lv_label_set_text(ui_pct_panel_01_value, digit);
	
}
void ui_pct_event_button_cb(lv_event_t* e)
{
	uint8_t code = (uint8_t)(int)lv_event_get_user_data(e);
	switch (code)
	{
	case UI_PCT_KEYBOARD_0:
	case UI_PCT_KEYBOARD_1:
	case UI_PCT_KEYBOARD_2:
	case UI_PCT_KEYBOARD_3:
	case UI_PCT_KEYBOARD_4:
	case UI_PCT_KEYBOARD_5:
	case UI_PCT_KEYBOARD_6:
	case UI_PCT_KEYBOARD_7:
	case UI_PCT_KEYBOARD_8:
	case UI_PCT_KEYBOARD_9:		
	case UI_PCT_KEYBOARD_ESC:
	case UI_PCT_KEYBOARD_BACKSPACE:
	case UI_PCT_KEYBOARD_ENTER:
		if (ui_pct_active_display == UI_PCT_DISPLAY_PROG)		ui_pct_prog_display_update_value(code);
		break;
	case UI_PCT_KEYBOARD_LEFT:
		if (ui_pct_active_display == UI_PCT_DISPLAY_PROG)
		{
			if (ui_pct_prog_display_variable_index - 1 >= 0) {
				ui_pct_prog_display_variable_index--;
				ui_pct_update_prog_display();
			}
		}
		else if (ui_pct_active_display == UI_PCT_DISPLAY_DIAG)
		{
			if (ui_pct_diag_display_variable_index - 1 >= 0) {				
				ui_pct_diag_display_variable_index--;
				ui_pct_update_diagnostic_display();
			}
		}
		break;
	case UI_PCT_KEYBOARD_RIGHT:
		if (ui_pct_active_display == UI_PCT_DISPLAY_PROG)
		{
			if (ui_pct_prog_display_variable_index + 1 < ui_pct_active_prog_array_size) {
				ui_pct_prog_display_variable_index++;
				ui_pct_update_prog_display();
			}
		}
		else if (ui_pct_active_display == UI_PCT_DISPLAY_DIAG)
		{
			if (ui_pct_diag_display_variable_index + 1 < sizeof(ui_pct_diagnostic_displays) / sizeof(UI_PCT_DISPLAY_INFO)) {
				ui_pct_diag_display_variable_index++;
				ui_pct_update_diagnostic_display();
			}
		}
		
		break;
	case UI_PCT_KEYBOARD_PROG:
		if (ui_pct_active_display == UI_PCT_DISPLAY_PROG) 
			ui_pct_active_display = UI_PCT_DISPLAY_STATUS;
		else ui_pct_active_display = UI_PCT_DISPLAY_PROG;
		ui_pct_update_display_status();
		break;
	case UI_PCT_KEYBOARD_DIAG:
		if (ui_pct_active_display == UI_PCT_DISPLAY_DIAG) ui_pct_active_display = UI_PCT_DISPLAY_STATUS;
		else ui_pct_active_display = UI_PCT_DISPLAY_DIAG;
		ui_pct_update_display_status();
		break;
	}
}



void ui_pct_screen_init(void)
{	
	ui_pct_screen = ui_create_screen();	
	lv_obj_t* titlebar = ui_create_titlebar(ui_pct_screen, TITLEBAR_BACKGROUND_COLOR);
	
	lv_obj_t* title_label = lv_label_create(titlebar);	
	lv_obj_set_width(title_label, LV_SIZE_CONTENT);
	lv_obj_set_height(title_label, LV_SIZE_CONTENT);
	lv_label_set_recolor(title_label, true);
	lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_label_set_text(title_label, "PCT");
	lv_obj_set_style_text_font(title_label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);	
	lv_obj_align(title_label, LV_ALIGN_CENTER, 0, 0);
	
	LV_IMG_DECLARE(img_mark);
	
	lv_obj_t * obj = lv_img_create(ui_pct_screen);
	lv_img_set_src(obj, &img_mark);
	lv_img_set_zoom(obj, 100);
	lv_obj_set_pos(obj, -30, 10);
	
	
	obj = ui_create_label(ui_pct_screen,"MEGASONIC\nHYPERCLEAN", &lv_font_montserrat_20);	
	lv_obj_set_pos(obj, 100, 40);
	
	obj = ui_create_button(ui_pct_screen, "#6DFF13 " LV_SYMBOL_LEFT " #", 26, 26, 2, UI_PCT_PANEL_BG_COLOR, &lv_font_montserrat_14, ui_pct_event_prog_direction_cb, (void*)0);
	lv_obj_set_pos(obj, 5, 100);
	ui_pct_btn_prog_left = obj; 
	obj = ui_create_button(ui_pct_screen, "#6DFF13 " LV_SYMBOL_RIGHT " #", 26, 26, 2, UI_PCT_PANEL_BG_COLOR, &lv_font_montserrat_14, ui_pct_event_prog_direction_cb, (void*)1);
	lv_obj_set_pos(obj, 310, 100);
	ui_pct_btn_prog_right = obj;
	
	ui_pct_panel_title_01 = ui_create_label(ui_pct_screen, "PROCESS PARAMETERS", &lv_font_montserrat_16);
	lv_obj_set_style_text_align(ui_pct_panel_title_01, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_size(ui_pct_panel_title_01, 280, 30);
	lv_obj_set_pos(ui_pct_panel_title_01, 40, 105);
	
	lv_obj_t* panel = lv_obj_create(ui_pct_screen);
	lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(panel, lv_color_hex(UI_PCT_PANEL_BG_COLOR), LV_PART_MAIN);
	lv_obj_set_style_border_color(panel, lv_color_hex(UI_PCT_PANEL_BORDER_COLOR), LV_PART_MAIN);
	lv_obj_set_style_border_width(panel, 1, LV_PART_MAIN);
	lv_obj_set_style_pad_all(panel, 0, LV_PART_MAIN);
	lv_obj_set_pos(panel, 5, 135);
	lv_obj_set_size(panel, 330, 70);
	
	ui_pct_panel_01 = panel;
	
	obj = ui_create_label(panel, "ENTER NEW PROCESS NUMBER IF DESIRED", &lv_font_montserrat_14);
	lv_obj_set_style_text_color(obj, lv_color_hex(UI_PCT_PANEL_FG_COLOR), LV_PART_MAIN);
	lv_obj_set_size(obj, 310, 40);
	lv_obj_set_pos(obj, 5, 5);
	ui_pct_panel_01_line_01 = obj;
	
	obj = ui_create_label(panel, "(0 = N.O. SWITCH 1 = N.C. SWITCH)", &lv_font_montserrat_14);
	lv_obj_set_style_text_color(obj, lv_color_hex(UI_PCT_PANEL_FG_COLOR), LV_PART_MAIN);
	lv_obj_set_size(obj, 240, 40);
	lv_obj_set_pos(obj, 5, 35);
	ui_pct_panel_01_line_02 = obj;
	
	obj = ui_create_label(panel, "00001", &lv_font_montserrat_20);
	lv_obj_set_style_text_color(obj, lv_color_hex(UI_PCT_PANEL_FG_COLOR), LV_PART_MAIN);
	lv_obj_set_pos(obj, 255, 40);
	ui_pct_panel_01_value = obj;
	
	
	ui_pct_panel_title_02 = ui_create_label(ui_pct_screen, "DIAGNOSTIC", &lv_font_montserrat_16);	
	lv_obj_set_style_text_align(ui_pct_panel_title_02, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_size(ui_pct_panel_title_02, 280, 30);
	lv_obj_set_pos(ui_pct_panel_title_02, 40, 220);
	
	panel = lv_obj_create(ui_pct_screen);
	lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(panel, lv_color_hex(UI_PCT_PANEL_BG_COLOR), LV_PART_MAIN);
	lv_obj_set_style_border_color(panel, lv_color_hex(UI_PCT_PANEL_BORDER_COLOR), LV_PART_MAIN);
	lv_obj_set_style_border_width(panel, 1, LV_PART_MAIN);
	lv_obj_set_style_pad_all(panel, 0, LV_PART_MAIN);
	lv_obj_set_pos(panel, 5, 240);
	lv_obj_set_size(panel, 330, 80);
	ui_pct_panel_02 = panel;
	
	obj = ui_create_label(panel, "PROGRAMMED TEMP=000 ACTUAL TEMP=000", &lv_font_montserrat_14);
	lv_obj_set_style_text_color(obj, lv_color_hex(UI_PCT_PANEL_FG_COLOR), LV_PART_MAIN);
	lv_obj_set_size(obj, 270, 40);
	lv_obj_set_pos(obj, 5, 5);
	ui_pct_panel_02_line_01 = obj;
	
	obj = ui_create_label(panel, "LIQUID=160 OT=0 CONTACTOR=030 DUTY=000", &lv_font_montserrat_14);
	lv_obj_set_style_text_color(obj, lv_color_hex(UI_PCT_PANEL_FG_COLOR), LV_PART_MAIN);
	lv_obj_set_size(obj, 270, 40);
	lv_obj_set_pos(obj, 5, 40);
	ui_pct_panel_02_line_02 = obj;
	
	panel = lv_obj_create(ui_pct_screen);
	lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(panel, lv_color_hex(0x0), LV_PART_MAIN);	
	lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_all(panel, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(panel, 0, LV_PART_MAIN);
	lv_obj_set_pos(panel, 340, 40);
	lv_obj_set_size(panel, 190, 280);
	int item_size = 45;
	int step = item_size + 2;
	const lv_font_t* font = &lv_font_montserrat_20;
	obj = ui_create_button(panel, "#6DFF13 0 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_0);
	lv_obj_set_pos(obj, 0, step * 4);		ui_pct_keyboard[UI_PCT_KEYBOARD_0] = obj;
	obj = ui_create_button(panel, "#6DFF13 1 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_1);
	lv_obj_set_pos(obj, 0, step * 3);		ui_pct_keyboard[UI_PCT_KEYBOARD_1] = obj;
	obj = ui_create_button(panel, "#6DFF13 2 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_2);
	lv_obj_set_pos(obj, step, step*3);		ui_pct_keyboard[UI_PCT_KEYBOARD_2] = obj;
	obj = ui_create_button(panel, "#6DFF13 3 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_3);
	lv_obj_set_pos(obj, step*2, step * 3);	ui_pct_keyboard[UI_PCT_KEYBOARD_3] = obj;
	obj = ui_create_button(panel, "#6DFF13 4 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_4);
	lv_obj_set_pos(obj, 0, step*2);			ui_pct_keyboard[UI_PCT_KEYBOARD_4] = obj;
	obj = ui_create_button(panel, "#6DFF13 5 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_5);
	lv_obj_set_pos(obj, step, step*2);		ui_pct_keyboard[UI_PCT_KEYBOARD_5] = obj;
	obj = ui_create_button(panel, "#6DFF13 6 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_6);
	lv_obj_set_pos(obj, step*2, step*2);	ui_pct_keyboard[UI_PCT_KEYBOARD_6] = obj;
	obj = ui_create_button(panel, "#6DFF13 7 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_7);
	lv_obj_set_pos(obj, 0, step);			ui_pct_keyboard[UI_PCT_KEYBOARD_7] = obj;
	obj = ui_create_button(panel, "#6DFF13 8 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_8);
	lv_obj_set_pos(obj, step, step);		ui_pct_keyboard[UI_PCT_KEYBOARD_8] = obj;
	obj = ui_create_button(panel, "#6DFF13 9 #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_9);
	lv_obj_set_pos(obj, step*2, step);		ui_pct_keyboard[UI_PCT_KEYBOARD_9] = obj;
	
	obj = ui_create_button(panel, "#6DFF13 " LV_SYMBOL_LEFT" #", item_size, item_size, 2, UI_PCT_PANEL_BG_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_LEFT);
	lv_obj_set_pos(obj, step, step * 4);	ui_pct_keyboard[UI_PCT_KEYBOARD_LEFT] = obj;
	
	obj = ui_create_button(panel, "#6DFF13 " LV_SYMBOL_RIGHT " #", item_size, item_size, 2, UI_PCT_PANEL_BG_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_RIGHT);
	lv_obj_set_pos(obj, step * 2, step * 4);	ui_pct_keyboard[UI_PCT_KEYBOARD_RIGHT] = obj;
	
	
	
	obj = ui_create_button(panel, "#6DFF13 C #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_ESC);
	lv_obj_set_pos(obj, 0, step * 5);	ui_pct_keyboard[UI_PCT_KEYBOARD_ESC] = obj;
	obj = ui_create_button(panel, "#6DFF13 " LV_SYMBOL_BACKSPACE " #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_BACKSPACE);
	lv_obj_set_pos(obj, step, step * 5);	ui_pct_keyboard[UI_PCT_KEYBOARD_BACKSPACE] = obj;
	obj = ui_create_button(panel, "#6DFF13 " LV_SYMBOL_OK " #", item_size, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_ENTER);
	lv_obj_set_pos(obj, step * 2, step * 5);	ui_pct_keyboard[UI_PCT_KEYBOARD_ENTER] = obj;
	
	obj = ui_create_button(panel, "#6DFF13 PROG #", (step * 3 /2) - 2, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_PROG);
	lv_obj_set_pos(obj, 0, 0);		ui_pct_keyboard[UI_PCT_KEYBOARD_PROG] = obj;
	ui_pct_btn_prog = obj;
	obj = ui_create_button(panel, "#6DFF13 DIAG #", (step * 3 / 2) - 2, item_size, 2, UI_PCT_BTN_BG_NORMAL_COLOR, font, ui_pct_event_button_cb, (void*)UI_PCT_KEYBOARD_DIAG);
	lv_obj_set_pos(obj, (step * 3 / 2), 0);	ui_pct_keyboard[UI_PCT_KEYBOARD_DIAG] = obj;
	ui_pct_btn_diag = obj;
	
	ui_pct_update_display_status();
	ui_pct_update_diagnostic_display();
}

