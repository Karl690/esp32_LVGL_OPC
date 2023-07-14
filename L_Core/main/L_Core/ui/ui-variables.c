#include "ui.h"
#include "K_Core/display/DisplayCagetoryList.h"
lv_obj_t* ui_variables_screen;
lv_obj_t* pages[GROUP_SIZE];
lv_obj_t* active_page;
lv_obj_t * keyboard;
uint8_t GroupIndex = 0;
LV_IMG_DECLARE(img_mark);
///////////////////// SCREENS ////////////////////
static void anim_x_cb(void * var, int32_t v)
{
	lv_obj_set_x((lv_obj_t*)var, v);
	
}
void obj_event_cb(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t * obj = lv_event_get_target(e);
	if (code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED) {
		/*Focus on the clicked text area*/
		if (keyboard != NULL) {
			if (lv_obj_check_type(obj, &lv_spinbox_class))
			{	
				lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_NUMBER);
			}
			else
			{
				lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_TEXT_LOWER);
			}
			lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
			lv_keyboard_set_textarea(keyboard, obj);
		}
	}

	else if (code == LV_EVENT_READY) {
		LV_LOG_USER("Ready, current text: %s", lv_textarea_get_text(ta));
		lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
	}
}
void screen_event_cb(lv_event_t* e)
{
	lv_obj_t * screen = lv_event_get_current_target(e);
	lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
	lv_coord_t start =0 , end = 0;
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
		if (GroupIndex + 1 >= GROUP_SIZE) GroupIndex = GROUP_SIZE -1;
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
	if (active_page != pages[GroupIndex])
	{
		lv_obj_add_flag(active_page, LV_OBJ_FLAG_HIDDEN);
		active_page = pages[GroupIndex];
		lv_obj_clear_flag(active_page, LV_OBJ_FLAG_HIDDEN);
		lv_anim_t a;
		lv_anim_init(&a);
		lv_anim_set_var(&a, active_page);
		lv_anim_set_values(&a, start, end);
		lv_anim_set_time(&a, 100);
		lv_anim_set_exec_cb(&a, anim_x_cb);
		lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
		lv_anim_start(&a);
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
		lv_obj_set_style_text_font(label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);		
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
			case FUNC_INT16:
			case FUNC_INT32:
				lv_label_set_text_fmt(value, "%d", *(int*)paramInfo->parameters[i].VariablePointer); //
				break;
			case FUNC_FLOAT:
				lv_label_set_text_fmt(value, "%.3f", *(float*)paramInfo->parameters[i].VariablePointer); //
				break;
			case FUNC_HEX8:
			case FUNC_HEX16:
			case FUNC_HEX32:
				lv_label_set_text_fmt(value, "%x", *(int*)paramInfo->parameters[i].VariablePointer); //
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
			switch (paramInfo->parameters[i].FuncType)
			{
			case FUNC_INT:
			case FUNC_INT16:
			case FUNC_INT32:
			case FUNC_FLOAT:
			case FUNC_HEX8:
			case FUNC_HEX16:
			case FUNC_HEX32:
				value = lv_spinbox_create(item);
				lv_spinbox_set_digit_format(value, 5, 0);
				lv_obj_set_width(value, 100);
				lv_spinbox_set_range(value, -1000, 25000);
				lv_obj_add_event_cb(value, obj_event_cb, LV_EVENT_ALL, NULL);
				//lv_keyboard_set_textarea(keyboard, value);
				//lv_textarea_set_one_line(value, false);			
				break;
			case FUNC_ASCII:
				value = lv_textarea_create(item);
				lv_textarea_set_one_line(value, true);	
				lv_obj_add_event_cb(value, obj_event_cb, LV_EVENT_ALL, NULL);
				//lv_keyboard_set_textarea(keyboard, value);
				break;
			case FUNC_BOOLEAN:
				value = lv_switch_create(item);
				lv_obj_add_state(value, *(bool*)paramInfo->parameters[i].VariablePointer ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
				break;
			default:
				break;
			}	
		}
		if(value) lv_obj_align(value, LV_ALIGN_LEFT_MID, 200, 0);
		
		//lv_obj_set_y(value, lv_obj_get_y(label));
		i++;	
	}
}
lv_obj_t* ui_variables_create_group(DisplayGroupInfo* groupInfo)
{
	lv_obj_t* page = lv_obj_create(ui_variables_screen);
	lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE); /// Flags
	lv_obj_set_style_bg_color(page, lv_color_hex(PAGE_BACKGROUND_COLOR), LV_PART_MAIN);
	lv_obj_set_width(page, LV_PCT(100));
	lv_obj_set_height(page, LV_PCT(100));
	lv_obj_set_style_pad_all(page, 0, LV_PART_MAIN);
	
	lv_obj_t* titlebar = lv_obj_create(page);	
	lv_obj_clear_flag(titlebar, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE); /// Flags
	lv_obj_set_style_border_width(titlebar, 0, LV_PART_MAIN);
	lv_obj_set_width(titlebar, LV_PCT(100));
	lv_obj_set_height(titlebar, 40); 
	
	lv_obj_set_style_bg_color(titlebar, lv_color_hex(TITLEBAR_BACKGROUND_COLOR), LV_PART_MAIN);
	lv_obj_align(titlebar, LV_ALIGN_TOP_MID, 0, 0);
	lv_obj_t* obj = lv_label_create(titlebar);	
	
	lv_obj_set_width(obj, LV_SIZE_CONTENT);
	lv_obj_set_height(obj, LV_SIZE_CONTENT);
	lv_label_set_recolor(obj, true);
	lv_label_set_text_fmt(obj, "#fffff %s #", groupInfo->name);
	lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);	
	lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
	
	lv_obj_t*container = lv_obj_create(page);
	lv_obj_set_width(container, LV_PCT(100));
	lv_obj_set_height(container, 320 - 50);
	lv_obj_set_style_bg_color(container, lv_color_hex(0x0), LV_PART_MAIN);
	lv_obj_set_y(container, 45);
	lv_obj_set_style_pad_all(container, 0, LV_PART_MAIN);	
	lv_obj_set_style_pad_left(container, 10, LV_PART_MAIN);	
	lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
	ui_variables_create_page(container, &groupInfo->LiveParameters);
	ui_variables_create_page(container, &groupInfo->ReceipeParameters);
	return page;
}

void ui_variables_screen_init(void)
{
	ui_variables_screen = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_variables_screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_bg_color(ui_variables_screen, lv_color_hex(UI_BACKGROUND_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_variables_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_add_event_cb(ui_variables_screen, screen_event_cb, LV_EVENT_GESTURE, NULL);
	GroupIndex = 0;
	for (uint8_t i = 0; i < GROUP_SIZE; i++) {
		pages[i] = ui_variables_create_group(&displayGroupInfo[i]);
		if (i != 0)
		{
			lv_obj_add_flag(pages[i], LV_OBJ_FLAG_HIDDEN);
		}
	}
	active_page = pages[0];
	keyboard = lv_keyboard_create(ui_variables_screen);
	lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
}

