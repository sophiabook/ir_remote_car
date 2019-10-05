/*
 * interrupt.c
 *
 *  Created on: 2018/11/16
 *      Author: iLand
 */

#include "global.h"

void tim6_init(void) {

	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // Clock supply enable
	TIM6->CR1 = TIM_CR1_CEN;		//タイマ有効
	TIM6->CR2 = 0;
	TIM6->DIER = TIM_DIER_UIE;		//タイマ更新割り込みを有効に
	TIM6->CNT = 0;					//タイマカウンタ値を0にリセット
	TIM6->PSC = 64-1;				//タイマのクロック周波数をシステムクロック/64=1MHzに設定
	TIM6->ARR = 1000-1;				//タイマカウンタの上限値。1000に設定。ゆえに1msごとに割り込み発生

	TIM6->EGR = TIM_EGR_UG;			//タイマ設定を反映させるためにタイマ更新イベントを起こす
}

void ms_interrupt_start(){
	NVIC_EnableIRQ(TIM6_DAC1_IRQn);			//タイマ更新割り込みハンドラを有効に
	NVIC_SetPriority(TIM6_DAC1_IRQn, 2);	//タイマ更新割り込みの割り込み優先度を設定
}

void TIM6_DAC1_IRQHandler(void){

	if( !(TIM6->SR & TIM_SR_UIF) ){
		return;
	}

	if(AF.FLAG.SOUND){
		sound_counter++;
		TIM17->ARR = FREQ2PWMPERIOD(combat_march[0][score_index]);
		TIM17->CCR1 = TIM17->ARR / 2;
		if(sound_counter > combat_march[1][score_index]){
			sound_counter = 0;
			score_index++;
		}
		if(score_index == 141){
			score_index = 74;
		}
	}else if(AF.FLAG.SOUND == 0) {
		sound_counter = 0;
		score_index = 0;
		TIM17->CCR1 = 0;
	}

	TIM6->SR &= ~TIM_SR_UIF;
}
