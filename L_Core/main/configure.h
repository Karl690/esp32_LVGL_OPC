//#define USE_OPC
#pragma once
#include <stdint.h>

#define SDCARD_MOUNT_POINT "/sd-card"
#define SYSTEM_CONFIG_FILE SDCARD_MOUNT_POINT"/config.ini"
#define AMPLIIFER_CSV_FILE SDCARD_MOUNT_POINT"/amplifier.csv"

typedef struct
{
	uint8_t ssid[32];
	uint8_t password[32];
	uint8_t autoconnect;
	uint8_t status; //1: connected, 0: disconnected
	uint8_t ip[30];
	uint8_t subnet[30];
} WIFI_CONFIG;

typedef struct
{
	uint8_t autostart; 
	uint8_t status; //1: connected, 0: disconnected	
} BLUETOOTH_CONFIG;
typedef struct
{
	uint8_t automount; 
	uint8_t status; //1: connected, 0: disconnected	
} SDCARD_CONFIG;

typedef struct
{
	uint8_t username[30]; 
	uint8_t userpassword[30]; 
	uint8_t autostart; 
	uint8_t status; //1: connected, 0: disconnected	
} OPC_CONFIG;
typedef struct 
{
	WIFI_CONFIG wifi;
	BLUETOOTH_CONFIG bluetooth;
	OPC_CONFIG opc;
	SDCARD_CONFIG sdcard;
}SYSTEMCONFIG;
