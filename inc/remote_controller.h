/*
 * remote_controller.h
 *
 *  Created on: 2019/01/06
 *      Author: iLand
 */


#ifndef REMOTE_CONTROLLER_H_
#define REMOTE_CONTROLLER_H_

#include "global.h"

#define CUSTOM_CODE 0x10EF
#define POWER 0xD8
#define A 0xF8
#define B 0x78
#define C 0x58
#define UP 0xA0
#define DOWN 0x00
#define LEFT 0x10
#define RIGHT 0x80
#define SELECT 0x20
#define UP_LEFT 0xB1
#define DOWN_LEFT 0x11
#define UP_RIGHT 0x21
#define DOWN_RIGHT 0x81

//http://elm-chan.org/docs/ir_format.html
#define NEC_FORMAT_T 6

#define true 1
#define false 0

#define ON 1
#define OFF 0

#ifdef EXTERN
volatile uint8_t ir_data = 0;
volatile uint8_t ir_data_available = false;
#else
extern volatile uint8_t ir_data;
extern volatile uint8_t ir_data_available;
#endif

void receiver_init();
void hardware_exti_init();
void external_interrupt_mask(uint8_t is_mask);
void attach_external_interrupt();
uint8_t ir_get_data();
uint8_t ir_available();
void display_receive_data();


#endif /* REMOTE_CONTROLLER_H_ */
