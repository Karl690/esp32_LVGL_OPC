#include "../configure.h"
#include "../main.h"
#include "ui/ui-opc.h"
#include "K_Core.h"
#include "GPIO.h"
#include "taskmanager.h"
#include "DisplayList.h"
#include "RevisionHistory.h"
DisplayVariableInfo *ActiveVariableInfo = NULL;
void forground_task(void* arg);
void K_Core_Main()
{
	InitGPIO();
	InitTaskManager();
	xTaskCreatePinnedToCore(forground_task, "forground_task", 1024 * 2, NULL, 10, NULL, 1);
}

void forground_task(void* arg) {
	while (1)
	{	
		vTaskDelay(50);
		ui_opc_update_variableList();
	}
}

