#include "configure.h"
#include "main.h"

#include "serial.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/select.h>

#include "K_Core/communication/communication.h"
int serial_uart_fd = -1;

	
uint8_t serial_uart1_rx_buffer[RX_BUF_SIZE];
uint8_t serial_uart1_rx_urgent_buffer[RX_BUF_SIZE];
uint8_t serial_uart1_tx_buffer[TX_BUF_SIZE];

uint8_t serial_uart2_rx_buffer[RX_BUF_SIZE];
uint8_t serial_uart2_rx_urgent_buffer[RX_BUF_SIZE];
uint8_t serial_uart2_tx_buffer[TX_BUF_SIZE];

uint8_t serial_rx_buffer[256];
COMPORT ComUart1, ComUart2;
COMPORT* MasterCommPort = &ComUart1;

uint8_t serial_uart1_last_read_buffer[256];
uint8_t serial_uart2_last_read_buffer[256];
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
	uart_driver_install(port, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
	uart_param_config(port, &uart_config);
	uart_set_pin(port, tx_pin, rx_pin, rts_pin, cts_pin);
	if (is485)
	{
		// Set RS485 half duplex mode	
		ESP_ERROR_CHECK(uart_set_mode(port, UART_MODE_RS485_HALF_DUPLEX));
	}
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


void serial_uart_read(COMPORT* uart)
{	
	int len = uart_read_bytes(uart->id, serial_rx_buffer, 256, (100 / portTICK_PERIOD_MS));	
	if (len == 0) return;
	comm_add_buffer_to_buffer(&uart->RxBuffer, serial_rx_buffer, len);	
	//comm_process_rx_characters(uart, serial_rx_buffer, len);	
}

void serial_uart_read_task(void* args)
{
	while (1)
	{
		serial_uart_read(&ComUart1);
		serial_uart_read(&ComUart2);
	}
	//return NULL;
}
void serial_init()
{
	// initialize uart devices
	serial_uart_init(UART_NUM_1, SERIAL_UART1_TXD_PIN, SERIAL_UART1_RXD_PIN, SERIAL_UART1_RTS_PIN, SERIAL_UART1_CTS_PIN, false);
	serial_uart_init(UART_NUM_2, SERIAL_UART2_TXD_PIN, SERIAL_UART2_RXD_PIN, SERIAL_UART2_RTS_PIN, SERIAL_UART2_CTS_PIN, false);
	// initialize buffers
	ComUart1.id = COMM_TYPE_UART1;
	ComUart2.id = COMM_TYPE_UART2;
	
	//pthread_t uart_thread;
	//pthread_create(&uart_thread, NULL, serial_uart_read_task, NULL);	
	xTaskCreatePinnedToCore(serial_uart_read_task, "forground_task", 1024 * 2, NULL, 10, NULL, 1);
}
