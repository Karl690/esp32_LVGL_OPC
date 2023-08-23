#include "configure.h"
#include "main.h"

#include "serial.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/select.h>

//#include "esp_vfs.h"
//#include "esp_vfs_dev.h"
int serial_uart_fd = -1;

uint8_t serial_rs485_rx_buffer[SERIAL_RX_BUF_SIZE];
uint8_t serial_rs485_rx_urgent_buffer[SERIAL_RX_BUF_SIZE];
uint8_t serial_rs485_tx_buffer[SERIAL_TX_BUF_SIZE];

uint8_t serial_uart_rx_buffer[SERIAL_RX_BUF_SIZE];
uint8_t serial_uart_rx_urgent_buffer[SERIAL_RX_BUF_SIZE];
uint8_t serial_uart_tx_buffer[SERIAL_TX_BUF_SIZE];

COMPORT ComUart, Com485;

uint8_t serial_uart_last_read_buffer[256];
uint8_t serial_rs485_last_read_buffer[256];
void AddSerialBufferToBuffer(ComBuffer *targetBuffer, uint8_t* buf, uint16_t size)
{
	uint16_t index = 0;
	for (index = 0; index < size; index++)
	{
		targetBuffer->buffer[targetBuffer->Head] = buf[index];
		targetBuffer->Head++;
		targetBuffer->Head &= targetBuffer->Buffer_Size;
	}
}

void AddSerialStringToBuffer(ComBuffer *targetBuffer, char* SourceString)
{
	uint16_t size = strlen(SourceString);
	AddSerialBufferToBuffer(targetBuffer, (uint8_t*)SourceString, size);
}

void AddSerialCharToBuffer(ComBuffer *targetBuffer, uint8_t RawChar)
{
	targetBuffer->buffer[targetBuffer->Head] = RawChar;
	targetBuffer->Head++;
	targetBuffer->Head &= targetBuffer->Buffer_Size;
}
void serial_rs485_init()
{
	const uart_config_t uart_config = {
		.baud_rate = SERIAL_BAUD_RATE,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
		.source_clk = UART_SCLK_APB,
	};

	// We won't use a buffer for sending data.
	uart_driver_install(SERIAL_RS485, SERIAL_RX_BUF_SIZE * 2, 0, 0, NULL, 0);
	uart_param_config(SERIAL_RS485, &uart_config);
	uart_set_pin(SERIAL_RS485, SERIAL_485_TXD_PIN, SERIAL_485_RXD_PIN, SERIAL_485_RTS_PIN, UART_PIN_NO_CHANGE);
	// Set RS485 half duplex mode
	ESP_ERROR_CHECK(uart_set_mode(SERIAL_RS485, UART_MODE_RS485_HALF_DUPLEX));
}

void serial_buffers_init(uint8_t UartIndex, COMPORT* ComPort, uint8_t* RxBuffer, uint8_t* RxUgrentBuffer, uint8_t* TxBuffer)
{	
	//Initialize Secs serial's buffers
	ComPort->uart_id = UartIndex;
	ComPort->ComType                = COMTYPE_AUX; //primary control port for PC and REPETREL comm
	ComPort->RxBuffer.buffer     	= RxBuffer;
	ComPort->RxBuffer.Buffer_Size  = SERIAL_RX_BUF_SIZE; //this number is used to keep in bounds
	ComPort->RxBuffer.Head          = 0; //start of que
	ComPort->RxBuffer.Tail          = 0; //end of the que
	ComPort->RxBuffer.RxLineCount = 0; // if there is a valid command waiting
	memset(ComPort->RxBuffer.buffer, 0, SERIAL_RX_BUF_SIZE);
	ComPort->AcksWaiting            = 0;
	
	ComPort->TxBuffer.buffer     	= TxBuffer;
	ComPort->TxBuffer.Buffer_Size  = SERIAL_TX_BUF_SIZE; //this number is used to keep in bounds
	ComPort->TxBuffer.Head		    = 0; // index of where to put the next char
	ComPort->TxBuffer.Tail	        = 0; // index of where to pull the next char
	memset(ComPort->TxBuffer.buffer, 0, SERIAL_TX_BUF_SIZE);	
	
	ComPort->RxUrgentBuffer.buffer      = RxUgrentBuffer;
	ComPort->RxUrgentBuffer.Buffer_Size  = SERIAL_RX_URGENT_BUF_SIZE; //this number is used to keep in bounds
	ComPort->RxUrgentBuffer.Head        = 0; //start of que
	ComPort->RxUrgentBuffer.Tail        = 0; //end of the que
	ComPort->RxUrgentBuffer.RxLineCount = 0; // if there is a valid command waiting
	ComPort->UrgentFlag					= 0;
	ComPort->AcksWaiting				= 0;
	memset(ComPort->RxUrgentBuffer.buffer, 0, SERIAL_RX_BUF_SIZE);
}
void serial_uart_init()
{
	uart_config_t uart_config = {
		.baud_rate = SERIAL_BAUD_RATE,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
		.source_clk = UART_SCLK_DEFAULT,
	};
	uart_driver_install(SERIAL_UART, SERIAL_RX_BUF_SIZE * 2, 0, 0, NULL, 0);
	uart_param_config(SERIAL_UART, &uart_config);
	uart_set_pin(SERIAL_UART, SERIAL_UART_TXD_PIN, SERIAL_UART_RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	ESP_ERROR_CHECK(uart_set_mode(SERIAL_UART, UART_MODE_UART));
}
bool serial_uart_write_byte(int uart_port, char byte)
{
	if (uart_write_bytes(uart_port, &byte, 1) != 1) {
		ESP_LOGE(TAG, "Send data critical failure.");
		// add your code to handle sending failure here
		return false;
	}
	return true;
}
char serial_uart_read_byte(int uart_port)
{
	char byte;
	if(uart_read_bytes(uart_port, &byte, 1, (100 / portTICK_PERIOD_MS)) == 0) return 0;
	return byte;
}

void serial_rs485_check_rxtx()
{
	serial_uart_write_byte(2, 0x78);
	return;
	if (Com485.AcksWaiting)
	{
		serial_uart_write_byte(Com485.uart_id, ASCII_ACK);
		Com485.AcksWaiting--;
	}
	else if (Com485.TxBuffer.Head != Com485.TxBuffer.Tail)
	{
		serial_uart_write_byte(Com485.uart_id, Com485.TxBuffer.buffer[Com485.TxBuffer.Tail]);
		Com485.TxBuffer.Tail++;
		Com485.TxBuffer.Head &= Com485.TxBuffer.Buffer_Size;
	}
	
	
	
}
bool a;
void serial_uart_check_rxtx()
{
	serial_uart_write_byte(1, 0x77);
//	
//	if (ComUart.AcksWaiting)
//	{
//		serial_uart_write_byte(ComUart.uart_id, ASCII_ACK);
//		ComUart.AcksWaiting--;
//	}
//	else if (ComUart.TxBuffer.Head != ComUart.TxBuffer.Tail)
//	{
//		 a = serial_uart_write_byte(ComUart.uart_id, ComUart.TxBuffer.buffer[ComUart.TxBuffer.Tail]);
//		ComUart.TxBuffer.Tail++;
//		ComUart.TxBuffer.Head &= ComUart.TxBuffer.Buffer_Size;
//	}	
}

void* serial_uart_read_task(void* param)
{
	uint8_t buffer[256];
	while (1)
	{
		int len = uart_read_bytes(SERIAL_UART, buffer, 256, (100 / portTICK_PERIOD_MS));	
		if (len == 0) {
			buffer[0] = 0;
			continue;
		}
		memcpy(serial_uart_last_read_buffer, buffer, len);
		serial_uart_last_read_buffer[len] = 0;
		for (int i = 0; i < len; i++)
		{
			ComUart.RxBuffer.buffer[ComUart.RxBuffer.Head] = buffer[i];
			ComUart.RxBuffer.Head++;
			ComUart.RxBuffer.Head &= ComUart.RxBuffer.Buffer_Size;			
		}
	}
	return NULL;
}

void* serial_rs485_read_task(void* param)
{
	uint8_t buffer[256];
	while (1)
	{
		int len = uart_read_bytes(SERIAL_RS485, buffer, 256, (100 / portTICK_PERIOD_MS));	
		if (len == 0) {
			buffer[0] = 0;
			continue;
		}
		memcpy(serial_rs485_last_read_buffer, buffer, len);
		serial_rs485_last_read_buffer[len] = 0;
		for(int i = 0; i < len; i ++)
		{
			Com485.RxBuffer.buffer[Com485.RxBuffer.Head] = buffer[i];
			Com485.RxBuffer.Head++;
			Com485.RxBuffer.Head &= Com485.RxBuffer.Buffer_Size;			
		}
	}
	return NULL;
}

void serial_init()
{
	pthread_t rx_thread, rx485_thread;
	// initialize uart devices
	serial_uart_init();
	serial_rs485_init();
	// initialize buffers
	serial_buffers_init(SERIAL_UART, &ComUart, serial_uart_rx_buffer, serial_uart_rx_urgent_buffer, serial_uart_tx_buffer);
	pthread_create(&rx_thread, NULL, serial_uart_read_task, NULL);
	serial_buffers_init(SERIAL_RS485, &Com485, serial_rs485_rx_buffer, serial_rs485_rx_urgent_buffer, serial_rs485_tx_buffer);
	pthread_create(&rx485_thread, NULL, serial_rs485_read_task, NULL);
}
