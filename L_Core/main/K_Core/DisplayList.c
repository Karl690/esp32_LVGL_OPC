#include "DisplayList.h"
#include "taskmanager.h"
#include "K_Core.h"
#include "../open62541/opc.h"
#include "../wifi/wifi.h"
#include "../ui/ui.h"
#include "../ui/ui-opc.h"
#include "RevisionHistory.h"

DisplayVariableInfo LcdVarsTable[] = {
	{ (void*)SYSTEMINFO, "SystemInfo", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ (void*)SYSTEMVERSION, "Version", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ (void*)WIFI_SSID, "WIFI SSID", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ ipAddress, "WIFI IP", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &wifi_is_connected, "WIFI Status", FUNC_BOOLEAN, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &OpcRunning, "OPC Status", FUNC_BOOLEAN, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &OpcHeartBeat, "OPC HeartBeat", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ 0 },
};


DisplayVariableInfo Lcd1VarsTable[] = {
	{ &ipAddress, "WIFI IP", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &OpcRunning, "OPC Status", FUNC_BOOLEAN, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ 0 },
};

DisplayVariableInfo Lcd2VarsTable[] = {
	{ &HeartBeat, "TITLE2", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &ipAddress, "WIFI IP", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &OpcRunning, "OPC Status", FUNC_BOOLEAN, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ 0 },
};
DisplayVariableInfo Lcd3VarsTable[] = {
	{ &HeartBeat, "TITLE3", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &ipAddress, "WIFI IP", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ &OpcRunning, "OPC Status", FUNC_BOOLEAN, COLOR_WHITE, COLOR_RED, 0, NULL },
	{ 0 },
};
int GetDisplayVariableSize(DisplayVariableInfo* variableInfo)
{
	int i = 0;
	while (1)
	{
		if (variableInfo[i].VariablePointer == 0) break;
		i++;
	}
	return i;
}

