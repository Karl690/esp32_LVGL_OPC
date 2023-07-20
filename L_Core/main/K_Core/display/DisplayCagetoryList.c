#include "K_Core/K_Core.h"
#include "DisplayCagetoryList.h"
#include "L_Core/wifi/wifi.h"
#include "RevisionHistory.h"

AmplifierInfo amplifierInfoList[GROUP_SIZE] = {};
DisplayGroupInfo displayGroupInfo[GROUP_SIZE] = { 
	{ 
		.name = "Amplifer - 1",
		.LiveParameters = {
			.name = "Live",
			.parameters = {
				{ &amplifierInfoList[0].liveData.Unit,				"Unit#",					FUNC_INT16,		COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE,0, NULL },
				{ &amplifierInfoList[0].liveData.Channel,			"Channel#",					FUNC_ASCII,		COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Power1,			"Power1",					FUNC_INT16,		COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Power2,			"Power2",					FUNC_INT16,		COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Frequence1,		"Frequence1",				FUNC_INT16,		COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Frequence2,		"Frequence2",				FUNC_INT16,		COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.BathTemperature,	"BathTemperature",			FUNC_INT16,		COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.TC1,				"TC1",						FUNC_INT16,		COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.TC2,				"TC2",						FUNC_INT16,		COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.TC6,				"TC6",						FUNC_INT16,		COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Status,			"Status1",					FUNC_BOOLEAN,	COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_FALSE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Status,			"Status2",					FUNC_BOOLEAN,	COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{0},
			},
		},
		.ReceipeParameters = {
			.name = "Reciepe data",
			.parameters = {
				{ &amplifierInfoList[0].reciepeData.ProcessTime,	"ProcessTime", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, 0, 0, 0, NULL },
				{ &amplifierInfoList[0].reciepeData.DesiredPower, "Desired Power", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, 0, 0, 0, NULL },				
				{0},
			}
		},
		.FrequenceParameters = {
			.name = "Frequence data",
			.parameters = {
				{ &amplifierInfoList[0].freqData.Frequence1, "Frequence1", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, 0, 0, 0, NULL },
				{ &amplifierInfoList[0].freqData.Frequence2, "Frequence2", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, 0, 0, 0, NULL },
				{ &amplifierInfoList[0].freqData.Frequence3, "Frequence3", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, 0, 0, 0, NULL },
				{ &amplifierInfoList[0].freqData.Frequence4, "Frequence4", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, 0, 0, 0, NULL },
				{ &amplifierInfoList[0].freqData.Frequence5, "Frequence5", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, 0, 0, 0, NULL },
				{ &amplifierInfoList[0].freqData.Frequence6, "Frequence6", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, 0, 0, 0, NULL },
				{ &amplifierInfoList[0].freqData.Frequence7, "Frequence7", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, 0, 0, 0, NULL },
				{0},
			}
		},
	},
	
	{ 
		.name = "Amplifer - 2",
		.LiveParameters = {
			.name = "Live",
			.parameters = {
				{ &amplifierInfoList[1].liveData.Unit, "Unit#", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[1].liveData.Channel, "Channel#", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{0},
			},
		},
		.ReceipeParameters = {
			.name = "Reciepe data",
			.parameters = {
				{ &amplifierInfoList[1].reciepeData.ProcessTime, "ProcessTime", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[1].reciepeData.DesiredPower, "Desired Power", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{0},
			}
		},
		.FrequenceParameters = {
			.name = "Frequence data",
			.parameters = {
				{ &amplifierInfoList[1].freqData.Frequence1, "Frequence1", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[1].freqData.Frequence2, "Frequence2", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },				
				{ &amplifierInfoList[1].freqData.Frequence3, "Frequence3", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[1].freqData.Frequence4, "Frequence4", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[1].freqData.Frequence5, "Frequence5", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[1].freqData.Frequence6, "Frequence6", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[1].freqData.Frequence7, "Frequence7", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{0},
			}
		},
	},
	
	{ 
		.name = "Amplifer - 3",
		.LiveParameters = {
			.name = "Live",
			.parameters = {
				{ &amplifierInfoList[2].liveData.Unit, "Unit#", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[2].liveData.Channel, "Channel#", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{0},
			},
		},
		.ReceipeParameters = {
			.name = "Reciepe data",
			.parameters = {
				{ &amplifierInfoList[2].reciepeData.ProcessTime, "ProcessTime", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[2].reciepeData.DesiredPower, "Desired Power", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{0},
			}
		},
		.FrequenceParameters = {
			.name = "Frequence data",
			.parameters = {
				{ &amplifierInfoList[2].freqData.Frequence1, "Frequence1", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[2].freqData.Frequence2, "Frequence2", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{0},
			}
		},
	},
	
	{ 
		.name = "Amplifer - 4",
		.LiveParameters = {
			.name = "Live",
			.parameters = {
				{ &amplifierInfoList[3].liveData.Unit, "Unit#", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[3].liveData.Channel, "Channel#", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{0},
			},
		},
		.ReceipeParameters = {
			.name = "Reciepe data",
			.parameters = {
				{ &amplifierInfoList[3].reciepeData.ProcessTime, "ProcessTime", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[3].reciepeData.DesiredPower, "Desired Power", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{0},
			}
		},
		.FrequenceParameters = {
			.name = "Frequence data",
			.parameters = {
				{ &amplifierInfoList[3].freqData.Frequence1, "Frequence1", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[3].freqData.Frequence2, "Frequence2", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{0},
			}
		},
	},
};

void Init_GroupList()
{
	
}

void WriteParams(FILE* fp, DisplayVariableInfo* vars)
{
	char item[256] = { 0 };
	switch (vars->FuncType)
	{
	case FUNC_INT:
		sprintf(item, "%d,%s", *(int*)vars->VariablePointer, "INT");
		break;
	case FUNC_INT16:
		sprintf(item, "%d,%s", *(int*)vars->VariablePointer,"INT16");
		break;
	case FUNC_INT32:
		sprintf(item, "%d,%s", *(int*)vars->VariablePointer, "INT32");
		break;
	case FUNC_ASCII:
		sprintf(item, "%s,%s", (char*)vars->VariablePointer, "ASCII");
		break;
	case FUNC_FLOAT:
		sprintf(item, "%.3f,%s", *(float*)vars->VariablePointer, "FLOAT");
		break;
	case FUNC_BOOLEAN:
		sprintf(item, "%s,%s", *(char*)vars->VariablePointer?"TRUE":"FALSE", "BOOL");
		break;
	default:
		break;
	}
	fwrite(item, strlen(item), 1, fp);
	sprintf(item, ",%d,%d,%d,%s,%s\n", (int)vars->Color_1, (int)vars->Color_2, (int)vars->Offset, vars->Editable ? "EDITABLE" : "READONLY", vars->ExposedOpc ? "EXPOSED" : "NONE");
	fwrite(item, strlen(item), 1, fp);
	
}

bool SaveDisplayGroupList(const char* path)
{
	FILE* fp = fopen(path, "w");
	if (fp == NULL) return false;
	char line[1024] = "Group name, params,name, value,type,var_color,var_offset,editable,opc_exposed\n";
	fwrite(line, strlen(line), 1, fp);
	int param_index = 0;
	for(uint16_t i = 0; i < GROUP_SIZE; i ++)
	{
		param_index = 0;
		DisplayVariableInfo* vars = displayGroupInfo[i].LiveParameters.parameters;		
		while (vars[param_index].VariablePointer)
		{
			sprintf(line, "%s,%s,%s,", displayGroupInfo[i].name, displayGroupInfo[i].LiveParameters.name, vars[param_index].Label);
			fwrite(line, strlen(line), 1, fp);
			WriteParams(fp, &vars[param_index]);	
			param_index++;
		}
		param_index = 0;
		vars = displayGroupInfo[i].ReceipeParameters.parameters;
		while (vars[param_index].VariablePointer)
		{
			sprintf(line, "%s,%s,%s,", displayGroupInfo[i].name, displayGroupInfo[i].ReceipeParameters.name, vars[param_index].Label);
			fwrite(line, strlen(line), 1, fp);
			WriteParams(fp, &vars[param_index]);
			param_index++;
		}
		param_index = 0;
		vars = displayGroupInfo[i].FrequenceParameters.parameters;
		while (vars[param_index].VariablePointer)
		{
			sprintf(line, "%s,%s,%s,", displayGroupInfo[i].name, displayGroupInfo[i].FrequenceParameters.name, vars[param_index].Label);
			fwrite(line, strlen(line), 1, fp);
			WriteParams(fp, &vars[param_index]);
			param_index++;
		}
	}
	fclose(fp);
	return true;
}

const char* getfield(char* line, int num)
{
	const char* tok;
	for (tok = strtok(line, ";");
	        tok && *tok;
	        tok = strtok(NULL, ";\n"))
	{
		if (!--num)
			return tok;
	}
	return NULL;
}


bool LoadDisplayGroupList(const char* path)
{
	FILE* fp = fopen(path, "r");
	if (fp == NULL) return false;
	char line[1024];
	while (fgets(line, 1024, fp))
	{
		char* tmp = strdup(line);
		printf("Field 3 would be %s\n", getfield(tmp, 3));
		// NOTE strtok clobbers tmp
		free(tmp);
	}
	return true;
}