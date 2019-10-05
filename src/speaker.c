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

	// PA7 �� Alternative Function �ɐݒ肷��
	GPIOA->MODER &= ~(1 << 14);
	GPIOA->MODER |= 1 << 15;
	// PA7 �� AF1�ɐݒ肷��
	GPIOA->AFR[0] |= (GPIO_AF1_TIM17 << GPIO_AFRL_AFRL7_Pos);

	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN; // Clock supply enable

	TIM17->CR1 = TIM_CR1_CEN;						//�^�C�}�L��
	TIM17->CR2 = 0;
	TIM17->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0 |
			TIM_CCMR1_OC1PE;	//PWM���[�h2,CH1
	TIM17->CCER = TIM_CCER_CC1E;		//TIM17_CH1�o�͗L��
	TIM17->BDTR = TIM_BDTR_MOE;

	TIM17->CNT = 0;					//�^�C�}�J�E���^�l��0�Ƀ��Z�b�g
	TIM17->PSC = 64-1;					//�^�C�}�̃N���b�N���g�����V�X�e���N���b�N/64=1MHz�ɐݒ�
	TIM17->ARR = 0;	//�^�C�}�J�E���^�̏���l�B��芸����
	TIM17->CCR1 = 0;				//�^�C�}�J�E���^�̔�r��v�l
}
