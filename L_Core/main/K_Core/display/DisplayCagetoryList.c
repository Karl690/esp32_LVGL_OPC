#include <stddef.h>
#include "configure.h"
#include "K_Core/K_Core.h"
#include "DisplayCagetoryList.h"
#include "L_Core/wifi/wifi.h"
#include "RevisionHistory.h"

AmplifierInfo amplifierInfoList[GROUP_SIZE] = {};
DisplayGroupInfo displayGroupInfo[] = { 
	{ 
		.name = "Amplifer - 1",
		.LiveParameters = {
			.name = "Live",
			.parameters = {
				{ &amplifierInfoList[0].liveData.Unit, "Unit#", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE,0, NULL },
				{ &amplifierInfoList[0].liveData.Channel, "Channel#", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Power1, "Power1", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Power2, "Power2", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Frequence1, "Frequence1", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Frequence2, "Frequence2", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.BathTemperature, "BathTemperature", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.TC1, "TC1", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.TC2, "TC2", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.TC6, "TC6", FUNC_INT16, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Status, "Status1", FUNC_BOOLEAN, COLOR_WHITE, COLOR_RED, 0, READONLY, OPC_FALSE, 0, NULL },
				{ &amplifierInfoList[0].liveData.Status, "Status2", FUNC_BOOLEAN, COLOR_WHITE, COLOR_RED, 0, EDIALBE, OPC_TRUE, 0, NULL },
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