#pragma once
#include <stdint.h>
typedef struct
{
	uint16_t	process_number;			//Range: 00001-00009, Default: 00000, Normal: 00001
	uint16_t	password;				//Range: 00000-65535, Normal: 00000, Value: 00000 to 00250	(User - defined value.	We recommend using this range.Values higher than 00250 are reserved for factory use only.)
	uint16_t	process_temperature;	//Range: 00000-00070, Normal: 00015-00070
	uint16_t	min_temperature;		//Range: 00000-00070, Normal: 00020-00070
	uint16_t	max_temperature;		//Range: 00000-00070, Normal: 00001-00060  , 00060 recommanded
	uint16_t	process_time;			//Range: 00000-65535, Normal: 00300, 00600, 000900, for 5, 10, 15 minute processes
	uint16_t	power_level;			//Range: 00000-00100, Normal: 00100
	uint16_t	min_qualify_power_array_1; //Range: 00000-00500, Normal: 00100
	uint16_t	min_qualify_power_array_2; //Range: 00000-00500, Normal: 00100
	uint16_t	transducer_type; //Range: 00000-00001, Normal: 00000, 
										//00000 = RTD; accurate sensing during the process.	00001 = Embedded thermocouple; non - intrusive temperature measurement.
	uint16_t	remote_interface_type; //Range: 00000-00001, Normal: 00000, 	
										//00000 = Normal 00001 = Quick Off
	uint16_t	heater_power_factor; //Range: 00200-00900, Normal: 00900,  recommanded
}PCT_PROGRAMMING_INFO;

typedef struct
{
	uint16_t	liquid_level_set_point; //Range: 00000-00001, Normal: 00000, value: 00000=Normally open state, 00001=Normally closed state 	
}PCT_LEVEL_SENSOR_INFO;

typedef struct
{
	uint16_t	serial_interface;// 0000, 000001, 000002
	uint16_t	datalog_flag;	//00000, 000001
	uint16_t	baud_rate; //Range: 00300,00600, 02400, 04800,09600, Normal: 09600
	uint16_t	device_id; //Range: 00000-32767, value: 00000
	uint16_t	transmission_character_pause; //Range: 00000-00500, value: 00003 , default setting
	uint16_t	transmission_message_pause; //Range: 00000-00500, value: 00010 , default setting
	uint16_t	transmission_retry_pause; //Range: 00000-00031, value: 000005, default setting
	uint16_t	dupe_block;	//Range: 00000-00001, value: 00001=Enables checking of incomming system byte values to validate the message
}PCT_SECS_INFO;

typedef struct
{
	uint16_t	mulitplexer_dwell_time; //00001-00003
	uint16_t	crystal_count;			//00004-00008
	uint16_t	array1_min_frequency;			//05000-07000, normal: 06850
	uint16_t	array1_max_frequency; //05750-08500, normal: 07500
	uint16_t	array2_min_frequency; //05000-07000, normal: 06850
	uint16_t	array2_max_frequency; //05750-08500, normal: 07500
	uint16_t	tuning_speed;			//00001-00050, normal: 0035, 00001=fastest speed, 00050=slowest speed
}PCT_TRANSDUCER_PARAM_INFO;

typedef struct
{
	uint16_t	array1_freqency;	//06250-08500
	uint16_t	array2_freqency;	//06250-08500
	uint16_t	password;			//00000-65535, normal: 00000
									//00000 to 00250	(User - defined value.	We recommend using this range.Values higher than 00250 are reserved for factory use only.)
	uint16_t	array1_w_factor;
	uint16_t	array2_w_factor;
}PCT_FREQUENCY_INFO;


extern PCT_PROGRAMMING_INFO			pct_progamming_info;
extern PCT_LEVEL_SENSOR_INFO		pct_level_senser_info;
extern PCT_SECS_INFO				pct_secs_info;
extern PCT_TRANSDUCER_PARAM_INFO	pct_transducer_param_info;
extern PCT_FREQUENCY_INFO			pct_frequency_info;