#include "configure.h"
#include "main.h"
#include "L_Core/ui/ui-opc.h"
#include "K_Core.h"
#include "gpio/GPIO.h"
#include "taskmanager.h"
#include "display/DisplayList.h"
#include "RevisionHistory.h"
#include "adc/adc.h"
DisplayVariableInfo *ActiveVariableInfo = NULL;
void forground_task(void* arg);
void K_Core_Main()
{
	// Init_RCC();
	Init_GPIO();
	Init_ADC();
	
	// InitSerialBuffers();
	// Init_Uart();
	// Init_CAN();
	// Init_SPI();
	// Init_Motor_parameters(); //set up the defults for the motor parameters
	// Init_MotionTimers();  
	// Init_USB_DEVICE(); //DO NOT call this BEFORE SYSTICK_Config, it will freeze in a loop because of hal_Delay()
	
	Init_TaskManager();
	//xTaskCreatePinnedToCore(forground_task, "forground_task", 1024 * 2, NULL, 10, NULL, 1);
	while (1)
	{	
		vTaskDelay(50);
		//ui_opc_update_variableList();
	}
}

void forground_task(void* arg) {
	while (1)
	{	
		vTaskDelay(50);
		//ui_opc_update_variableList();
	}
}

