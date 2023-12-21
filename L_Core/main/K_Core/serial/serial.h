#pragma once
#include "driver/uart.h"
#include "K_Core/communication/communication.h"


#define SERIAL_485_TXD_PIN	(GPIO_NUM_42)
#define SERIAL_485_RXD_PIN	(GPIO_NUM_1)
#define SERIAL_485_RTS_PIN	(GPIO_NUM_2)

#define SERIAL_UART1_TXD_PIN	(GPIO_NUM_14)  //GPIO_NUM_43= U0TXD //GPIO_NUM_14
#define SERIAL_UART1_RXD_PIN	(GPIO_NUM_21)   //GPIO_NUM_44= U0RXD //GPIO_NUM_21
#define SERIAL_UART1_RTS_PIN	(UART_PIN_NO_CHANGE)
#define SERIAL_UART1_CTS_PIN	(UART_PIN_NO_CHANGE)

#define SERIAL_UART2_TXD_PIN	(GPIO_NUM_12) 
#define SERIAL_UART2_RXD_PIN	(GPIO_NUM_13) 
#define SERIAL_UART2_RTS_PIN	(UART_PIN_NO_CHANGE)
#define SERIAL_UART2_CTS_PIN	(UART_PIN_NO_CHANGE)

#define SERIAL_UART UART_NUM_1
#define SERIAL_RS485 UART_NUM_2

#define SERIAL_BAUD_RATE 115200


extern uint8_t serial_uart1_rx_buffer[RX_BUF_SIZE];
extern uint8_t serial_uart1_rx_urgent_buffer[RX_BUF_SIZE];
extern uint8_t serial_uart1_tx_buffer[TX_BUF_SIZE];

extern uint8_t serial_uart2_rx_buffer[RX_BUF_SIZE];
extern uint8_t serial_uart2_rx_urgent_buffer[RX_BUF_SIZE];
extern uint8_t serial_uart2_tx_buffer[TX_BUF_SIZE];

extern COMPORT ComUart1;
extern COMPORT ComUart2;
extern COMPORT* MasterCommPort;
extern uint8_t serial_uart1_last_read_buffer[256];
extern uint8_t serial_uart2_last_read_buffer[256];
void serial_init();
void serial_uart_read_slice();
bool serial_uart_write_byte(int uart_port, char byte);
