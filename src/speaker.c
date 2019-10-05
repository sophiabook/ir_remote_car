/*
 * speaker.c
 *
 *  Created on: 2019/01/03
 *      Author: iLand
 */

#include "stm32f3xx.h"
#include "speaker.h"

void speaker_pwm_init(void) {

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // IO portA clock enable

	// PA7 を Alternative Function に設定する
	GPIOA->MODER &= ~(1 << 14);
	GPIOA->MODER |= 1 << 15;
	// PA7 を AF1に設定する
	GPIOA->AFR[0] |= (GPIO_AF1_TIM17 << GPIO_AFRL_AFRL7_Pos);

	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN; // Clock supply enable

	TIM17->CR1 = TIM_CR1_CEN;						//タイマ有効
	TIM17->CR2 = 0;
	TIM17->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0 |
			TIM_CCMR1_OC1PE;	//PWMモード2,CH1
	TIM17->CCER = TIM_CCER_CC1E;		//TIM17_CH1出力有効
	TIM17->BDTR = TIM_BDTR_MOE;

	TIM17->CNT = 0;					//タイマカウンタ値を0にリセット
	TIM17->PSC = 64-1;					//タイマのクロック周波数をシステムクロック/64=1MHzに設定
	TIM17->ARR = 0;	//タイマカウンタの上限値。取り敢えず
	TIM17->CCR1 = 0;				//タイマカウンタの比較一致値
}
