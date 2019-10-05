/*
 * uart.h
 *
 *  Created on: 2018/08/29
 *      Author: iLand
 */

#ifndef UART_H_
#define UART_H_

volatile char buf[50];

/*============================================================
		関数プロトタイプ宣言
============================================================*/
void usart_io_init(void);
void usart_init(uint32_t baudrate);
void send_char(char c);
void send_str(const char *str);
char get_char(void);
void get_str(char *str);
void uart_printf(const char* format, ...);

#endif /* UART_H_ */
