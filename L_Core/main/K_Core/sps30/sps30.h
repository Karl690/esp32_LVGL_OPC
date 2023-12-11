#pragma once
#include "main.h"
#include "K_Core/communication/communication.h"
#define SPS30_MAX_BUFFER_SIZE	0x7ff
#define SPS30_STARTEND_BIT	0x7E

#define SPS30_START		0x0 //Start Measuremen
#define	SPS30_STOP		0x1	//Stop Measurement
#define	SPS30_READ		0x3	//Read Measured Value
#define	SPS30_SLEEP		0x10	//Sleep
#define SPS30_WAKEUP	0x11
#define SPS30_STARTFAN	0x56
#define SPS30_AUTO_RW	0x80  //Read/write auto cleaning interval
#define SPS30_DEVINFO	0xD0  //Device information
#define SPS30_VERSION	0xD1  //Read version
#define SPS30_STATUS	0xD2  //Read device status register
#define SPS30_RESET		0xD3  //Reset
#define SPS30_LOOPREAD	0xFF  //loop reading

enum
{
	SPS30_STATUS_IDLE,
	SPS30_STATUS_RESETED,
	SPS30_STATUS_STARTED,
	SPS30_STATUS_STOPED,
} ;
typedef struct
{
	uint8_t checkSum;
	uint8_t calcSum;
	uint16_t receivedDataSize;
	
	uint8_t status;
	uint8_t auto_read;
	
}SPS30_CONFIG;

typedef struct
{	
	float MassPM10; //Mass Concentration PM1.0 [痢/m設
	float MassPM25;  //Mass Concentration PM2.5 [痢/m設
	float MassPM40; //Mass Concentration PM4.0 [痢/m設
	float MassPM100; // Mass Concentration PM10 [痢/m設
	float NumberOfConnectionPM05; // Number Concentration PM0.5 [#/cm設
	float NumberOfConnectionPM10; // Number Concentration PM1.0 [#/cm設
	float NumberOfConnectionPM25; // Number Concentration PM2.5 [#/cm設
	float NumberOfConnectionPM40; // Number Concentration PM4.0 [#/cm設
	float NumberOfConnectionPM100; //Number Concentration PM10 [#/cm設
	float TypicalParticleSize;	// Typical Particle Size8 [痠]
}SPS30_DATA_INFO;


extern COMPORT* COMSPS30;
extern uint8_t sps30_tx_buffer[];
extern uint8_t sps30_rx_buffer[];
extern SPS30_DATA_INFO sps30_data_info;
extern SPS30_CONFIG sps30_config;
void sps30_init();
void sps30_request_read();
size_t sps30_make_tx_package(uint8_t cmd, uint8_t* data, size_t data_size);
void sps30_process_rx_data();
bool sps30_parse_incomming_data();
void sps30_send_command(uint8_t command);