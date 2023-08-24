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


uint8_t serial_uart1_rx_buffer[SERIAL_RX_BUF_SIZE];
uint8_t serial_uart1_rx_urgent_buffer[SERIAL_RX_BUF_SIZE];
uint8_t serial_uart1_tx_buffer[SERIAL_TX_BUF_SIZE];

uint8_t serial_uart2_rx_buffer[SERIAL_RX_BUF_SIZE];
uint8_t serial_uart2_rx_urgent_buffer[SERIAL_RX_BUF_SIZE];
uint8_t serial_uart2_tx_buffer[SERIAL_TX_BUF_SIZE];


COMPORT ComUart1, ComUart2;

uint8_t serial_uart1_last_read_buffer[256];
uint8_t serial_uart2_last_read_buffer[256];
void serial_add_buffer_to_buffer(ComBuffer *targetBuffer, uint8_t* buf, uint16_t size)
{
	uint16_t index = 0;
	for (index = 0; index < size; index++)
	{
		targetBuffer->buffer[targetBuffer->Head] = buf[index];
		targetBuffer->Head++;
		targetBuffer->Head &= targetBuffer->Buffer_Size;
	}
}

void serial_add_string_to_buffer(ComBuffer *targetBuffer, char* SourceString)
{
	uint16_t size = strlen(SourceString);
	serial_add_buffer_to_buffer(targetBuffer, (uint8_t*)SourceString, size);
}

void serial_add_char_to_buffer(ComBuffer *targetBuffer, uint8_t RawChar)
{
	targetBuffer->buffer[targetBuffer->Head] = RawChar;
	targetBuffer->Head++;
	targetBuffer->Head &= targetBuffer->Buffer_Size;
}
void serial_uart_init(uint8_t port, int tx_pin, int rx_pin, int rts_pin, int cts_pin, bool is485)
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
	uart_driver_install(port, SERIAL_RX_BUF_SIZE * 2, 0, 0, NULL, 0);
	uart_param_config(port, &uart_config);
	uart_set_pin(port, tx_pin, rx_pin, rts_pin, cts_pin);
	if (is485)
	{
		// Set RS485 half duplex mode	
		ESP_ERROR_CHECK(uart_set_mode(port, UART_MODE_RS485_HALF_DUPLEX));
	}
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


void serial_uart1_check_tx()
{
//	serial_uart_write_byte(1, 0x77);
//	return;
	if (ComUart1.AcksWaiting)
	{
		serial_uart_write_byte(ComUart1.uart_id, ASCII_ACK);
		ComUart1.AcksWaiting--;
	}
	else if (ComUart1.TxBuffer.Head != ComUart1.TxBuffer.Tail)
	{
		serial_uart_write_byte(ComUart1.uart_id, ComUart1.TxBuffer.buffer[ComUart1.TxBuffer.Tail]);
		ComUart1.TxBuffer.Tail++;
		ComUart1.TxBuffer.Head &= ComUart1.TxBuffer.Buffer_Size;
	}	
}
void serial_uart2_check_tx()
{
	//serial_uart_write_byte(1, 0x77);
	if (ComUart2.AcksWaiting)
	{
		serial_uart_write_byte(ComUart2.uart_id, ASCII_ACK);
		ComUart2.AcksWaiting--;
	}
	else if (ComUart2.TxBuffer.Head != ComUart2.TxBuffer.Tail)
	{
		serial_uart_write_byte(ComUart2.uart_id, ComUart2.TxBuffer.buffer[ComUart2.TxBuffer.Tail]);
		ComUart2.TxBuffer.Tail++;
		ComUart2.TxBuffer.Head &= ComUart2.TxBuffer.Buffer_Size;
	}	
}

void* serial_uart1_read_task(void* param)
{
	uint8_t buffer[256];
	while (1)
	{
		int len = uart_read_bytes(UART_NUM_1, buffer, 256, (100 / portTICK_PERIOD_MS));	
		if (len == 0) {
			buffer[0] = 0;
			continue;
		}
		memcpy(serial_uart1_last_read_buffer, buffer, len);
		serial_uart1_last_read_buffer[len] = 0;
		for (int i = 0; i < len; i++)
		{
			ComUart1.RxBuffer.buffer[ComUart1.RxBuffer.Head] = buffer[i];
			ComUart1.RxBuffer.Head++;
			ComUart1.RxBuffer.Head &= ComUart1.RxBuffer.Buffer_Size;			
		}
	}
	return NULL;
}
void* serial_uart2_read_task(void* param)
{
	uint8_t buffer[256];
	while (1)
	{
		int len = uart_read_bytes(UART_NUM_2, buffer, 256, (100 / portTICK_PERIOD_MS));	
		if (len == 0) {
			buffer[0] = 0;
			continue;
		}
		memcpy(serial_uart2_last_read_buffer, buffer, len);
		serial_uart2_last_read_buffer[len] = 0;
		for (int i = 0; i < len; i++)
		{
			ComUart2.RxBuffer.buffer[ComUart2.RxBuffer.Head] = buffer[i];
			ComUart2.RxBuffer.Head++;
			ComUart2.RxBuffer.Head &= ComUart2.RxBuffer.Buffer_Size;			
		}
	}
	return NULL;
}

void serial_init()
{
	pthread_t uart1_thread, uart2_thread;
	// initialize uart devices
	serial_uart_init(UART_NUM_1, SERIAL_UART1_TXD_PIN, SERIAL_UART1_RXD_PIN, SERIAL_UART1_RTS_PIN, SERIAL_UART1_CTS_PIN, false);
	serial_uart_init(UART_NUM_2, SERIAL_UART2_TXD_PIN, SERIAL_UART2_RXD_PIN, SERIAL_UART2_RTS_PIN, SERIAL_UART2_CTS_PIN, false);
	// initialize buffers
	serial_buffers_init(UART_NUM_1, &ComUart1, serial_uart1_rx_buffer, serial_uart1_rx_urgent_buffer, serial_uart1_tx_buffer);
	serial_buffers_init(UART_NUM_2, &ComUart2, serial_uart2_rx_buffer, serial_uart2_rx_urgent_buffer, serial_uart2_tx_buffer);
	pthread_create(&uart1_thread, NULL, serial_uart1_read_task, NULL);
	pthread_create(&uart2_thread, NULL, serial_uart2_read_task, NULL);
}
