#include "sps30.h"

#include "K_Core/serial/serial.h"

uint8_t sps30_tx_buffer[SPS30_MAX_BUFFER_SIZE] = { 0 };
uint8_t sps30_rx_buffer[SPS30_MAX_BUFFER_SIZE] = { 0 };
uint8_t sps30_data[256] = { 0 };
uint8_t sps30_temp_data[256] = { 0 };
uint16_t sps30_rx_length = 0;
SPS30_DATA_INFO sps30_data_info;
SPS30_CONFIG sps30_config;
bool byte_stuff = false;

COMPORT* COMSPS30 = NULL; //Secs Serial Class

void sps30_init()
{
	//send the start request to start sps30
	COMSPS30 = &ComUart1;
	sps30_config.status = SPS30_STATUS_IDLE;
	sps30_config.auto_read = 1;
	size_t size = sps30_make_tx_package(SPS30_RESET, sps30_data, 0);
	commnuication_add_buffer_to_serial_buffer(&COMSPS30->TxBuffer, sps30_tx_buffer, size);
	//size = sps30_make_tx_package(SPS30_WAKEUP, sps30_data, 0);
	//commnuication_add_buffer_to_serial_buffer(&COMSPS30->TxBuffer, sps30_tx_buffer, size);
	
	//vTaskDelay(100);
	//size = sps30_make_tx_package(SPS30_STARTFAN, sps30_data, 0);
	//commnuication_add_buffer_to_serial_buffer(&COMSPS30->TxBuffer, sps30_tx_buffer, size);
	
	//sps30_data[0] = 0x1;
	//sps30_data[1] = 0x3;	//0x3: float, 0x5: 16bit
	//size = sps30_make_tx_package(SPS30_START, sps30_data, 2);
	//commnuication_add_buffer_to_serial_buffer(&COMSPS30->TxBuffer, sps30_tx_buffer, size);
}

void sps30_request_read()
{	
	if (!sps30_config.auto_read) return;
	if (sps30_config.status != SPS30_STATUS_STARTED) return;
	size_t size = sps30_make_tx_package(SPS30_READ, sps30_data, 0);
	commnuication_add_buffer_to_serial_buffer(&COMSPS30->TxBuffer, sps30_tx_buffer, size);
}

uint8_t sps30_make_checksum(uint8_t* data, uint8_t first, uint8_t last)
{
	uint8_t i;
	uint32_t ret = 0;

	for (i = first; i <= last; i++)   ret += data[i];
	return (~(ret & 0xff));
}
uint8_t sps30_valid_checksum(uint8_t* data, size_t size) 
{
	sps30_config.receivedDataSize = size;
	sps30_config.checkSum = 0;
	sps30_config.calcSum = 0;
	if (size < 4) return 0;	
	if (data[3] != 0) return 0; // third bit is status ,, if it is not 0, that means error 
	if (data[0] != SPS30_STARTEND_BIT || data[size - 1] != SPS30_STARTEND_BIT) return 0;
	uint8_t checksum = data[size - 2];
	uint8_t calcSum = sps30_make_checksum(data, 1, size-3); // first, last. checksum
	sps30_config.checkSum = checksum;
	sps30_config.calcSum = calcSum;
	if (calcSum != checksum) return false;
	return 1;
}
size_t sps30_make_tx_package(uint8_t cmd, uint8_t* data, size_t data_size)
{
	uint8_t size = 3;
	sps30_tx_buffer[1] = 0x0; //Address
	sps30_tx_buffer[2] = cmd; //Command
	sps30_tx_buffer[3] = (uint8_t)data_size; //data Length byte
	for (int i = 0; i < data_size; i++)
		sps30_tx_buffer[4 + i] = data[i];
	size += data_size;
	sps30_tx_buffer[size + 1] = sps30_make_checksum(sps30_tx_buffer, 1, size);
	size += 2;
	sps30_tx_buffer[0] = SPS30_STARTEND_BIT;
	sps30_tx_buffer[size] = SPS30_STARTEND_BIT;
	size += 1;
	return size;
}

bool sps30_parse_read_measure_value(uint8_t* data, size_t size)
{
	uint16_t len = data[4];
	if (len != 0x28 || size < len) return false; //read data's length must be 40bytes (0x28)
	uint8_t* pdata = (uint8_t*)&sps30_data_info;
	uint8_t buf[4] = { 0 };
	for (uint16_t i = 5; i < size - 2; i += 4)
	{
		//that is because of big endian
		buf[3] = data[i];
		buf[2] = data[i + 1];
		buf[1] = data[i + 2];
		buf[0] = data[i + 3];
		memcpy(pdata, buf, 4);
		pdata += 4;
	}
	return true;
}

bool sps30_parse_incomming_data(uint8_t* data, size_t size) 
{
	if (!sps30_valid_checksum(data, size)) return false; // do nothing if checksum is invalid
	uint8_t cmd = data[2];
	switch (cmd)
	{
	case SPS30_RESET:
		sps30_config.status = SPS30_STATUS_RESETED;
		sps30_send_command(SPS30_START); //start 
		break;
	case SPS30_START:
		sps30_config.status = SPS30_STATUS_STARTED;
		break;
	case SPS30_STOP:
		sps30_config.status = SPS30_STATUS_STOPED;
		break;
	case SPS30_READ:
		sps30_parse_read_measure_value(data, size);
		break;
	}
	return true;
}
void sps30_process_rx_data()
{
	uint8_t RxChar;
	if (!COMSPS30) return;
	while (COMSPS30->RxBuffer.Head != COMSPS30->RxBuffer.Tail)
	{
		//must be != because it is circular que.... can not simpley be less than
		RxChar = COMSPS30->RxBuffer.buffer[COMSPS30->RxBuffer.Tail];
		COMSPS30->RxBuffer.Tail++; //point to the next character
		COMSPS30->RxBuffer.Tail &= COMSPS30->RxBuffer.Buffer_Size; //circular que with even hex size....
		if (RxChar == SPS30_STARTEND_BIT)
		{
			if (sps30_rx_length > 4)
			{
				// received data is full.
				sps30_rx_buffer[sps30_rx_length] = RxChar;
				sps30_rx_length++;

				if (sps30_parse_incomming_data(sps30_rx_buffer, sps30_rx_length))
				{
					sps30_rx_length = 0; // reset the buffer point
				}
				else
				{
					if (sps30_rx_buffer[sps30_rx_length - 1] == SPS30_STARTEND_BIT) sps30_rx_length = 0; // reset the buffer point
				}
			}
			else
			{
				sps30_rx_length = 0;
				sps30_rx_buffer[sps30_rx_length] = RxChar;
				sps30_rx_length++;
			}
			byte_stuff = false;
		}
		else if (RxChar == 0x7D)
		{
			byte_stuff = true;
		}
		else
		{
			if (byte_stuff)
			{
				switch (RxChar)
				{
				case 0x31: RxChar = 0x11; break;
				case 0x33: RxChar = 0x13; break;
				case 0x5d: RxChar = 0x7d; break;
				case 0x5e: RxChar = 0x7e; break;
				}
			}
			sps30_rx_buffer[sps30_rx_length] = RxChar;
			sps30_rx_length++;
			if (sps30_rx_length > 0x7FF) //SPS30_MAX_BUFFER_SIZE
				sps30_rx_length = 0;
			
			byte_stuff = false;
		}
	}
}

void sps30_send_command(uint8_t command)
{
	size_t size = 0;
	switch (command)
	{
		
	case SPS30_RESET:
		size = sps30_make_tx_package(SPS30_RESET, sps30_data, 0);		
		break;
	case SPS30_START:
		sps30_data[0] = 0x1;
		sps30_data[1] = 0x3; //0x3: float, 0x5: 16bit
		size = sps30_make_tx_package(SPS30_START, sps30_data, 2);
		break;
	case SPS30_STOP:
		size = sps30_make_tx_package(SPS30_STOP, sps30_data, 0);
		break;
	case SPS30_READ:
		size = sps30_make_tx_package(SPS30_READ, sps30_data, 0);
		break;
	case SPS30_LOOPREAD:
		sps30_config.auto_read = !sps30_config.auto_read;
		break;
	}
	if(size > 0) commnuication_add_buffer_to_serial_buffer(&COMSPS30->TxBuffer, sps30_tx_buffer, size);
}