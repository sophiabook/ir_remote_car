/*
 * remote_controller.c
 *
 *  Created on: 2019/01/06
 *      Author: iLand
 */

#include "global.h"

void receiver_init()
{
	// distribute clock
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	// GPIOB6 Input mode
	GPIOB->MODER &= ~GPIO_MODER_MODER6_Msk; // initialize PB6 function
	GPIOB->MODER |= (GPIO_MODE_INPUT << GPIO_MODER_MODER6_Pos); // set PB6 as GPIO for input
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6_Msk;//GPIOx_PUPDRレジスタのPB6の部分を初期化
	GPIOB->PUPDR |= (GPIO_PULLUP << GPIO_PUPDR_PUPDR6_Pos);//PB6プルアップ抵抗有効化
}

void hardware_exti_init()
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI6_PB;//EXTI6の外部割り込みソースにPBピンを設定。
	EXTI->IMR |= EXTI_IMR_MR6;//ライン6からの割り込みリクエストはマスクされない
    EXTI->FTSR |= EXTI_FTSR_TR6;//割り込みのトリガ選択　立ち下がり
}


void external_interrupt_mask(uint8_t is_mask){
	if(is_mask == ON){
		EXTI->IMR &= ~EXTI_IMR_MR6;//ライン6からの割り込みリクエストはマスクされる
	}else if(is_mask == OFF){
		EXTI->IMR |= EXTI_IMR_MR6;//ライン6からの割り込みリクエストはマスクされない
	}
}

void attach_external_interrupt(){
	NVIC_EnableIRQ(EXTI9_5_IRQn);			//外部割り込みハンドラを有効に
	NVIC_SetPriority(EXTI9_5_IRQn, 3);	//外部割り込みの割り込み優先度を設定
}


uint8_t ir_get_data(){
	ir_data_available = false;
	return ir_data;
}

uint8_t ir_available(){
	return ir_data_available;
}

//http://gadget.renesas.com/ja/product/cotton_sp9.html
void EXTI9_5_IRQHandler()
{
	EXTI->PR |= EXTI_PR_PR6; // clear pending bit of line 6
	external_interrupt_mask(ON);
	uint32_t last_time = time_cnt;
    uint32_t signal_start = time_cnt;
    // confirm if reader code is correct
    uint8_t err = false;
    while(!(GPIOB->IDR & GPIO_IDR_6)){ // until change from low to high
    	if(time_interval(time_cnt, last_time) > (NEC_FORMAT_T * 16) * 10.0 / 9.0){ // interval low should be 9ms or less
    		err = true;
    		break;
    	}
    }
    while(!!(GPIOB->IDR & GPIO_IDR_6)){ // until change from high to low
    	if(time_interval(time_cnt, last_time) > (NEC_FORMAT_T * 24) * 10.0 / 9.0){ // interval of reader code should be 13.5ms or less
    		err = true;
    		break;
    	}
    }
    if((time_interval(time_cnt, last_time) < (NEC_FORMAT_T * 24) * 9.0 / 10.0) || (err == true)){ //if too short or too long
    	// Unknown code
    	external_interrupt_mask(OFF);
    	return; // not available remote controller
    }
    // get data
    uint8_t receive_count = 0;
    uint8_t temp_ir_data[4] = {0};
    ir_data = 0;
    while(32 > receive_count){
    	last_time = time_cnt;
    	while((!(GPIOB->IDR & GPIO_IDR_6)) && (time_interval(time_cnt, last_time) < NEC_FORMAT_T * 10.0 / 9.0)){
    		// interval of low state is about 0.56ms.
    	}
    	while((!!(GPIOB->IDR & GPIO_IDR_6)) && (time_interval(time_cnt, last_time) < (NEC_FORMAT_T * 4) * 10.0 / 9.0)){
    		// interval of a bit is between 1.125ms and 2.25ms
    	}
    	if(time_interval(time_cnt, last_time) > (NEC_FORMAT_T * 4 + NEC_FORMAT_T * 2) / 2.0){
    		temp_ir_data[receive_count / 8] |= (1 << (receive_count % 8));
    	}
    	receive_count++;
    }
    last_time = time_cnt;
    while(!(GPIOB->IDR & GPIO_IDR_6)){ // until change from low to high
    	// interval of low state is about 0.56ms.
    	if(time_interval(time_cnt, last_time) > NEC_FORMAT_T * 10.0 / 9.0){
    		err = true;
    		break; // not stop bit
    	}
    }
    uint32_t signal_span = time_interval(time_cnt, signal_start);
    if((signal_span > (NEC_FORMAT_T * 137) * 10.0 / 9.0) || (signal_span < (NEC_FORMAT_T * 105) * 9.0 / 10.0) || (err == true)){
    	// interval of a frame data should be 76.5ms or less
    	// interval of a frame data should be 58.5ms or more
    	// stop bit is too long
    	return;
    }
    if((((uint16_t)temp_ir_data[0] << 8) | temp_ir_data[1]) == CUSTOM_CODE){ // confirm if custom code is correct
    	if(temp_ir_data[2] == (uint8_t)~temp_ir_data[3]){ // confirm data code
    		ir_data = temp_ir_data[2]; // set actual data
    		ir_data_available = true; // available remote controller
    	}
    }
    external_interrupt_mask(OFF);
}

void display_receive_data(){
	//display result
	if(ir_available() == true){
		switch (ir_get_data()) {
		case POWER: // POWER BUTTON
			uart_printf("%s\r", "POWER");
			break;
		case A: // A BUTTON
			uart_printf("%s\r", "A");
			break;
		case B: // B BUTTON
			uart_printf("%s\r", "B");
			break;
		case C: // C BUTTON
			uart_printf("%s\r", "C");
			break;
		case UP:
			uart_printf("%s\r", "UP");
			break;
		case DOWN:
			uart_printf("%s\r", "DOWN");
			break;
		case LEFT:
			uart_printf("%s\r", "LEFT");
			break;
		case RIGHT:
			uart_printf("%s\r", "RIGHT");
			break;
		case SELECT:
			uart_printf("%s\r", "SELECT");
			break;
		case UP_LEFT:
			uart_printf("%s\r", "UP_LEFT");
			break;
		case DOWN_LEFT:
			uart_printf("%s\r", "DOWN_LEFT");
			break;
		case UP_RIGHT:
			uart_printf("%s\r", "UP_RIGHT");
			break;
		case DOWN_RIGHT:
			uart_printf("%s\r", "DOWN_RIGHT");
			break;
		default:
			uart_printf("%s\r", "TRUE");
			break;
		}
		ir_data_available = false;
	}
}
