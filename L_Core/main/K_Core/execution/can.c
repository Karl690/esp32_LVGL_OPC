#include "can.h"
#include "L_Core/bluetooth/ble.h"
#include "K_Core/communication/communication.h"
#include "K_Core/tools/tools.h"
CANMsg canInMsg;
CANMsg canOutMsg;
uint32_t can_msg_process_count = 0;

char can_temp_string[256] = { 0 };
void can_convert_can2asscii(CANMsg* canMsg)
{
	memset(can_temp_string, 0, 256);
	sprintf(can_temp_string,
		"CAN%d %d %d %d %d %d %d "
		"%d %d "
		"%d\n",
		(int)canMsg->ID, //0
		canMsg->Immediate, //1
		canMsg->TargetAddress, //2
		canMsg->SourceAddress, //3
		canMsg->MsgType, // 4
		canMsg->MsgId,//5
		canMsg->Page, //6
		(int)(*(uint32_t*)canMsg->Data),//7
		(int)(*(uint32_t*)(canMsg->Data + 4)), //11
		canMsg->DataSize); //15
}

uint8_t can_convert_asscii2can(char* cmd)
{
	if (strncmp(cmd, "CAN", 3)) return 0;
	cmd += 3;
	
	strcpy(can_temp_string, cmd);
	char * token = strtok(can_temp_string, " ");
	char item[10][20];
	// loop through the string to extract all other tokens
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (token == NULL) break;
		stpcpy(item[i], token);
		token = strtok(NULL, " ");
	}
	if (i != 10) return 0;//invalid format
	
	
	canInMsg.ID = atoi(item[0]);
	canInMsg.Immediate = atoi(item[1]);
	canInMsg.TargetAddress = atoi(item[2]);
	canInMsg.SourceAddress = atoi(item[3]);
	canInMsg.MsgType = atoi(item[4]);
	canInMsg.MsgId = atoi(item[5]);
	canInMsg.Page = atoi(item[6]);
	uint32_t a = atoi(item[7]);	
	uint32_t b = atoi(item[8]);
	memcpy(canInMsg.Data, &a, 4);
	memcpy(canInMsg.Data + 4, &b, 4);
	canInMsg.DataSize = atoi(item[9]);
	return 1;
}


void can_process_message(SimpleCommand* cmd)
{
	if (!can_convert_asscii2can((char*)cmd->cmd))  return;
	
	switch (canInMsg.MsgType)
	{
	case CAN_WRITE:
		// send this to ble head
		comm_add_string_to_buffer(&bleDevice.TxBuffer, (char*)cmd->cmd);
		break;
	case CAN_READ:
		// send this to PH407
		comm_add_string_to_buffer(&ComUart1.TxBuffer, "M999;");
		comm_add_string_to_buffer(&ComUart1.TxBuffer, (char*)cmd->cmd);
		break;
	}
}

