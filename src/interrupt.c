/*
 * interrupt.c
 *
 *  Created on: 2018/11/16
 *      Author: iLand
 */

#include "global.h"

void tim6_init(void) {

	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // Clock supply enable
	TIM6->CR1 = TIM_CR1_CEN;		//�^�C�}�L��
	TIM6->CR2 = 0;
	TIM6->DIER = TIM_DIER_UIE;		//�^�C�}�X�V���荞�݂�L����
	TIM6->CNT = 0;					//�^�C�}�J�E���^�l��0�Ƀ��Z�b�g
	TIM6->PSC = 64-1;				//�^�C�}�̃N���b�N���g�����V�X�e���N���b�N/64=1MHz�ɐݒ�
	TIM6->ARR = 1000-1;				//�^�C�}�J�E���^�̏���l�B1000�ɐݒ�B�䂦��1ms���ƂɊ��荞�ݔ���

	TIM6->EGR = TIM_EGR_UG;			//�^�C�}�ݒ�𔽉f�����邽�߂Ƀ^�C�}�X�V�C�x���g���N����
}

void ms_interrupt_start(){
	NVIC_EnableIRQ(TIM6_DAC1_IRQn);			//�^�C�}�X�V���荞�݃n���h����L����
	NVIC_SetPriority(TIM6_DAC1_IRQn, 2);	//�^�C�}�X�V���荞�݂̊��荞�ݗD��x��ݒ�
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
