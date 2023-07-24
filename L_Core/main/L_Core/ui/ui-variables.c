#include <stdio.h>
#include "ui.h"
#include "ui-home.h"
#include "font/font.h"
#include "K_Core/display/DisplayCagetoryList.h"
lv_obj_t* ui_variables_screen;
lv_obj_t* title;
lv_obj_t* pages[GROUP_SIZE];
lv_obj_t* variables_active_page;
lv_obj_t* variables_menu;
uint8_t GroupIndex = 0;
LV_IMG_DECLARE(img_mark);
///////////////////// SCREENS ////////////////////

void ui_variable_reload_groups();
static void anim_x_cb(void * var, int32_t v)
{
	lv_obj_set_x((lv_obj_t*)var, v);
	
}
void event_variables_edit_cb(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t * obj = lv_event_get_target(e);
	DisplayVariableInfo* varInfo = (DisplayVariableInfo*)obj->user_data;
	if (code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED)
	{
		/*Focus on the clicked text area*/
		if (keyboard != NULL)
		{
			switch (varInfo->FuncType)
			{
			case FUNC_ASCII:
				lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_TEXT_LOWER);
				break;
			default:
				lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_NUMBER);
				break;			
			}
			lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
			lv_keyboard_set_textarea(keyboard, obj);
			lv_obj_set_height(variables_active_page, 125);
			lv_obj_refr_size(variables_active_page);
		}
	}

	else if (code == LV_EVENT_READY )
	{
		if (varInfo->VariablePointer)
		{
			const char* text = lv_textarea_get_text(obj);
			switch (varInfo->FuncType)
			{
			case FUNC_INT:
				*(int*)varInfo->VariablePointer = atoi(text);
				break;
			case FUNC_INT16:
				*(uint16_t*)varInfo->VariablePointer = atoi(text);
				break;
			case FUNC_INT32:
				*(uint32_t*)varInfo->VariablePointer = atoi(text);
				break;
			case FUNC_ASCII:
				strcpy((char*)varInfo->VariablePointer, text);
				break;
			case FUNC_FLOAT:
				*(float*)varInfo->VariablePointer = atof(text);
				break;
			default:
				break;
			}
		}
		lv_obj_set_height(variables_active_page, 285);
		lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
		lv_obj_refresh_self_size(variables_active_page);
	}
	else if (code == LV_EVENT_VALUE_CHANGED)
	{
		*(bool*)varInfo->VariablePointer = lv_obj_has_state(obj, LV_STATE_CHECKED);
	}
}
void event_variables_load_cb(lv_event_t* e)
{
	lv_obj_add_flag(variables_menu, LV_OBJ_FLAG_HIDDEN);
	if (LoadDisplayGroupList(AMPLIIFER_CSV_FILE))
	{
		ui_show_messagebox(MESSAGEBOX_INFO, "Successful load the amplifier data.", 3000);
		ui_variable_reload_groups();
	}
	else ui_show_messagebox(MESSAGEBOX_ERROR, "Falied load the amplifier data.", 3000);
}
void event_variables_save_cb(lv_event_t* e)
{
	lv_obj_add_flag(variables_menu, LV_OBJ_FLAG_HIDDEN);
	//lv_scr_load_anim(ui_home_screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
	if (SaveDisplayGroupList(AMPLIIFER_CSV_FILE))
		ui_show_messagebox(MESSAGEBOX_INFO, "Successful save the amplifier data.", 3000);
	else
	{
		ui_show_messagebox(MESSAGEBOX_ERROR, "Falied save the amplifier data.", 3000);
	}
}
void event_variables_showmenu_cb(lv_event_t* e)
{
	if (lv_obj_is_visible(variables_menu))
		lv_obj_add_flag(variables_menu, LV_OBJ_FLAG_HIDDEN);
	else
		lv_obj_clear_flag(variables_menu, LV_OBJ_FLAG_HIDDEN);
}
void event_variable_gesture_cb(lv_event_t* e)
{
	lv_obj_t * screen = lv_event_get_current_target(e);
	if (e->code == LV_EVENT_CLICKED || e->code == LV_EVENT_FOCUSED)
	{
		lv_obj_add_flag(variables_menu, LV_OBJ_FLAG_HIDDEN);
	}
	if (e->code == LV_EVENT_GESTURE)
	{
		if (lv_obj_is_visible(keyboard))
		{
			lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);	
			lv_obj_set_height(variables_active_page, 285);
		}
		
		lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
		if(lv_obj_is_visible(variables_menu)) lv_obj_add_flag(variables_menu, LV_OBJ_FLAG_HIDDEN);
		lv_coord_t start = 0, end = 0;		
		switch (dir)
		{
		case LV_DIR_LEFT:
			//lv_label_set_text_fmt(title, "LEFT");
			if (GroupIndex - 1 <= 0) GroupIndex = 0;
			else GroupIndex--;
			start = -100;
			end = 0;
			break;
		case LV_DIR_RIGHT:
			if (GroupIndex + 1 >= GROUP_SIZE) GroupIndex = GROUP_SIZE - 1;
			else GroupIndex++;
			start = 100;
			end = 0;
			break;
		case LV_DIR_TOP:
			//lv_label_set_text_fmt(title, "TOP");
			break;
		case LV_DIR_BOTTOM:
			//lv_label_set_text_fmt(title, "BOTTOM");
			break;
		default:
			break;
		}
		if (variables_active_page != pages[GroupIndex])
		{	
			lv_obj_add_flag(variables_active_page, LV_OBJ_FLAG_HIDDEN);
			variables_active_page = pages[GroupIndex];
			lv_obj_clear_flag(variables_active_page, LV_OBJ_FLAG_HIDDEN);
			lv_anim_t a;
			lv_anim_init(&a);
			lv_anim_set_var(&a, variables_active_page); //active_page
			lv_anim_set_values(&a, start, end);
			lv_anim_set_time(&a, 100);
			lv_anim_set_exec_cb(&a, anim_x_cb);
			lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
			lv_anim_start(&a);
			lv_label_set_text(title, displayGroupInfo[GroupIndex].name);
		}	
	}
}

void ui_variables_create_page(lv_obj_t* parent, DisplayParamInfo* paramInfo)
{
	uint8_t i = 0;
	lv_obj_t* item;
	lv_obj_t* label;
	lv_obj_t* value = NULL;
	label = lv_label_create(parent);
	lv_label_set_recolor(label, true);
	lv_label_set_text(label, paramInfo->name);
	//lv_obj_set_style_pad_left(label, LV_PCT(30), LV_PART_MAIN);
	lv_obj_set_style_text_font(label, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);		
	
	while (paramInfo->parameters[i].VariablePointer != 0)
	{	
		item = lv_obj_create(parent);
		lv_obj_set_size(item, LV_PCT(98), 30);
		lv_obj_set_style_bg_color(item, lv_color_hex(0x171717), LV_PART_MAIN);	
		//lv_obj_set_style_opa(item, 30, LV_PART_MAIN);
		lv_obj_set_style_border_width(item, 0, LV_PART_MAIN);		
		lv_obj_clear_flag(item, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE); /// Flags
		
		label = lv_label_create(item);
		lv_label_set_recolor(label, true);	
		lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
		lv_obj_set_style_text_font(label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);		
		lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
		lv_label_set_text(label, paramInfo->parameters[i].Label);
		
		//lv_obj_set_x(label, 10);
		//lv_obj_set_style_pad_left(label, 3, LV_PART_MAIN);
		if (!paramInfo->parameters[i].Editable)
		{
			value = lv_label_create(item);
			lv_label_set_recolor(value, true);	
			switch (paramInfo->parameters[i].FuncType)
			{
			case FUNC_INT:
				lv_label_set_text_fmt(value, "%d", *(int*)paramInfo->parameters[i].VariablePointer); //
				break;
			case FUNC_INT16:
				lv_label_set_text_fmt(value, "%d", (int)*(uint16_t*)paramInfo->parameters[i].VariablePointer); //
				break;
			case FUNC_INT32:				
				lv_label_set_text_fmt(value, "%d", (int)*(uint32_t*)paramInfo->parameters[i].VariablePointer); //
				break;
			case FUNC_FLOAT:
				lv_label_set_text_fmt(value, "%.3f", *(float*)paramInfo->parameters[i].VariablePointer); //
				break;
			case FUNC_HEX8:
			case FUNC_HEX16:
			case FUNC_HEX32:
				lv_label_set_text_fmt(value, "0x%X", *(int*)paramInfo->parameters[i].VariablePointer); //
				break;
			case FUNC_ASCII:
				lv_label_set_text_fmt(value, "%s", (char*)paramInfo->parameters[i].VariablePointer); //
				break;
			case FUNC_BOOLEAN:
				lv_label_set_text_fmt(value, "%s", *(bool*)paramInfo->parameters[i].VariablePointer?"TRUE":"FALSE"); //
				break;
			default:
				break;
			}
			
			lv_obj_set_style_text_color(value, lv_color_hex(paramInfo->parameters[i].Color_2), LV_PART_MAIN);
			lv_obj_set_style_text_font(value, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);			
			
		}
		else
		{
			char val[256] = {0};
			
			switch (paramInfo->parameters[i].FuncType)
			{
			case FUNC_INT:
			case FUNC_INT16:
			case FUNC_INT32:
			case FUNC_FLOAT:
			case FUNC_HEX8:
			case FUNC_HEX16:
			case FUNC_HEX32:	
				value = lv_textarea_create(item);
				lv_textarea_set_accepted_chars(value, "0123456789-.");
				lv_textarea_set_max_length(value, 5);
				lv_textarea_set_one_line(value, true);
				if (paramInfo->parameters[i].FuncType == FUNC_FLOAT)
					sprintf(val, "%.3f", *(float*)paramInfo->parameters[i].VariablePointer);
				else {
					switch (paramInfo->parameters[i].FuncType)
					{
					case FUNC_INT:
						sprintf(val, "%d", *(int*)paramInfo->parameters[i].VariablePointer);
						break;
					case FUNC_INT16:
					case FUNC_HEX16:
						sprintf(val, "%d", (int)*(uint16_t*)paramInfo->parameters[i].VariablePointer);
						break;
					case FUNC_INT32:					
					case FUNC_HEX32:
						sprintf(val, "%d", (int)*(uint32_t*)paramInfo->parameters[i].VariablePointer);
						break;
					default:
						break;
					}
				}
				lv_textarea_set_text(value, val);
				lv_obj_set_width(value, 100);
				lv_obj_add_event_cb(value, event_variables_edit_cb, LV_EVENT_ALL, NULL);				
				break;
			case FUNC_ASCII:
				value = lv_textarea_create(item);
				lv_textarea_set_one_line(value, true);
				lv_textarea_set_max_length(value, 10);
				lv_textarea_set_text(value, (char*)paramInfo->parameters[i].VariablePointer);
				lv_obj_add_event_cb(value, event_variables_edit_cb, LV_EVENT_ALL, NULL);
				break;
			case FUNC_BOOLEAN:
				value = lv_switch_create(item);
				lv_obj_add_state(value, *(bool*)paramInfo->parameters[i].VariablePointer ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
				lv_obj_add_event_cb(value, event_variables_edit_cb, LV_EVENT_VALUE_CHANGED, NULL);
				break;
			default:
				break;
			}	
		}
		if (value) {
			value->user_data = &paramInfo->parameters[i];
			paramInfo->parameters[i].lv_object = value;
			lv_obj_align(value, LV_ALIGN_LEFT_MID, 200, 0);
		}
		
		//lv_obj_set_y(value, lv_obj_get_y(label));
		i++;	
	}
}
lv_obj_t* ui_variables_create_group(DisplayGroupInfo* groupInfo)
{
	lv_obj_t*container = lv_obj_create(ui_variables_screen);
	lv_obj_set_size(container, LV_PCT(100), 285);
	lv_obj_set_style_border_width(container, 0, LV_PART_MAIN);
	lv_obj_set_style_bg_color(container, lv_color_hex(0x0), LV_PART_MAIN);
	lv_obj_set_y(container, 33);
	lv_obj_set_style_pad_all(container, 0, LV_PART_MAIN);	
	lv_obj_set_style_pad_left(container, 10, LV_PART_MAIN);	
	lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
	ui_variables_create_page(container, &groupInfo->LiveParameters);
	ui_variables_create_page(container, &groupInfo->ReceipeParameters);
	ui_variables_create_page(container, &groupInfo->FrequenceParameters);
	return container;
}

void ui_variable_reload_groups()
{
	for (uint8_t i = 0; i < GROUP_SIZE; i++)
	{
		lv_obj_clean(pages[i]);
		ui_variables_create_page(pages[i], &displayGroupInfo[i].LiveParameters);
		ui_variables_create_page(pages[i], &displayGroupInfo[i].ReceipeParameters);
		ui_variables_create_page(pages[i], &displayGroupInfo[i].FrequenceParameters);
	}
}
void ui_variables_screen_init(void)
{
	ui_variables_screen = ui_create_screen();
	lv_obj_add_event_cb(ui_variables_screen, event_variable_gesture_cb, LV_EVENT_ALL, NULL);
	GroupIndex = 0;
	for (uint8_t i = 0; i < GROUP_SIZE; i++) {
		pages[i] = ui_variables_create_group(&displayGroupInfo[i]);
		if (i != 0)
		{
			lv_obj_add_flag(pages[i], LV_OBJ_FLAG_HIDDEN);
		}
	}
	variables_active_page = pages[0];
	
	lv_obj_t* titlebar = ui_create_titlebar(ui_variables_screen, TITLEBAR_BACKGROUND_COLOR);
	title = lv_label_create(titlebar);	
	lv_obj_set_width(title, LV_SIZE_CONTENT);
	lv_obj_set_height(title, LV_SIZE_CONTENT);
	lv_label_set_recolor(title, true);
	lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_label_set_text(title, displayGroupInfo[0].name);
	lv_obj_set_style_text_font(title, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);	
	lv_obj_align(title, LV_ALIGN_CENTER, 0, 0);
	
	
	lv_obj_t* obj = ui_create_label(ui_variables_screen, LV_SYMBOL_LIST, &lv_font_montserrat_20);
	lv_obj_set_style_text_color(obj, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_set_size(obj, 80, 30);
	lv_obj_set_pos(obj, 450, 5);
	lv_obj_add_event_cb(obj, event_variables_showmenu_cb, LV_EVENT_CLICKED, NULL);	
	
	variables_menu = lv_obj_create(ui_variables_screen);
	lv_obj_clear_flag(variables_menu, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_pad_all(variables_menu, 10, LV_PART_MAIN);
	lv_obj_set_size(variables_menu, 110, 90);
	lv_obj_set_pos(variables_menu, 370, 40);
	lv_obj_set_flex_flow(variables_menu, LV_FLEX_FLOW_COLUMN);
	
	lv_obj_t * item = ui_create_label(variables_menu, LV_SYMBOL_REFRESH " LOAD", &lv_font_montserrat_20);	
	lv_obj_set_size(item, LV_PCT(100), 30);
	lv_obj_add_flag(item, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_event_cb(item, event_variables_load_cb, LV_EVENT_CLICKED, NULL);
	item = ui_create_label(variables_menu, LV_SYMBOL_SAVE " SAVE", &lv_font_montserrat_20);
	lv_obj_set_size(item, LV_PCT(100), 40);
	lv_obj_add_flag(item, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_event_cb(item, event_variables_save_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_add_flag(variables_menu, LV_OBJ_FLAG_HIDDEN);
}

