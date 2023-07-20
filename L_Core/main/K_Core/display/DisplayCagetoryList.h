#pragma once
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "configure.h"
#include "DisplayList.h"

#define GROUP_SIZE 4
#define PARAM_SIZE 15


typedef struct
{
	uint16_t Unit; //Amplifier unit
	uint16_t Channel;
	uint16_t Frequence1;
	uint16_t Frequence2;
	uint16_t TC6;
	uint16_t Power1;
	uint16_t Power2;
	uint16_t BathTemperature;
	uint16_t TC1;
	uint16_t TC2;
	uint16_t Status;
}AmplifierLiveDataInfo;

typedef struct
{	
	uint16_t Frequence1;
	uint16_t Frequence2;
	uint16_t Frequence3;
	uint16_t Frequence4;
	uint16_t Frequence5;
	uint16_t Frequence6;
	uint16_t Frequence7;
	uint16_t Frequence8;
}AmplifierFrequenceDataInfo;

typedef struct
{	
	uint16_t ProcessTime;
	uint16_t DesiredPower;
	uint16_t DesiredTemperature;
	uint16_t MinTemperature;
	uint16_t MaxTemperature;
}AmplifierReciepeDataInfo;

typedef struct
{
	char name[30];
	AmplifierLiveDataInfo liveData;
	AmplifierFrequenceDataInfo freqData;
	AmplifierReciepeDataInfo reciepeData;
} AmplifierInfo;

typedef struct
{
	char* name; // ex: Live Data
	DisplayVariableInfo parameters[PARAM_SIZE];
}DisplayParamInfo;

typedef struct
{
	char* name; //ex: Amplifier - 1
	DisplayParamInfo LiveParameters;
	DisplayParamInfo ReceipeParameters;
	DisplayParamInfo FrequenceParameters;
	DisplayParamInfo SecsParameters;
}DisplayGroupInfo;


extern DisplayGroupInfo displayGroupInfo[];
void Init_GroupList();
bool SaveDisplayGroupList(const char* path);
bool LoadDisplayGroupList(const char* path);