/*
 * motor.c
 *
 *  Created on: 2018/11/16
 *      Author: iLand
 */

#include "global.h"

void motor_pwm_init(void) {

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // IO portA clock enable

	/*//�t�@���p
	// PA12 �� Alternative Function �ɐݒ肷��
	GPIOA->MODER &= ~(1 << 24);
	GPIOA->MODER |= 1 << 25;
	// PA12 �� AF1�ɐݒ肷��
	GPIOA->AFR[1] |= (GPIO_AF1_TIM16 << GPIO_AFRH_AFRH4_Pos);

	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN; // Clock supply enable

	TIM16->CR1 = TIM_CR1_CEN;						//�^�C�}�L��
	TIM16->CR2 = 0;
	TIM16->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0 |
			TIM_CCMR1_OC1PE;	//PWM���[�h2,CH1
	TIM16->CCER = TIM_CCER_CC1E;		//TIM16_CH1�o�͗L��
	TIM16->BDTR = TIM_BDTR_MOE;

	TIM16->CNT = 0;					//�^�C�}�J�E���^�l��0�Ƀ��Z�b�g
	TIM16->PSC = 1-1;					//�^�C�}�̃N���b�N���g�����V�X�e���N���b�N/1=64MHz�ɐݒ�
	TIM16->ARR = INTERVAL;	//�^�C�}�J�E���^�̏���l�BPWM����64MHz/1280=50kHz
	TIM16->CCR1 = 0;				//�^�C�}�J�E���^�̔�r��v�l*/

	//���[�^�[�p
	// PA8 �� Alternate Function �ɐݒ肷��
	GPIOA->MODER &= ~(1 << 16);
	GPIOA->MODER |= 1 << 17;
	// PA8 �� AF6�ɐݒ肷��
	GPIOA->AFR[1] |= (GPIO_AF6_TIM1 << GPIO_AFRH_AFRH0_Pos);

	// PA11 �� Alternate Function �ɐݒ肷��
	GPIOA->MODER &= ~(1 << 22);
	GPIOA->MODER |= 1 << 23;
	// PA11 �� AF11�ɐݒ肷��
	GPIOA->AFR[1] |= (GPIO_AF11_TIM1 << GPIO_AFRH_AFRH3_Pos);


	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // Clock supply enable

	TIM1->CR1 |= TIM_CR1_CEN;						//�^�C�}�L��
	TIM1->CR2 = 0;
	TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0 |
			TIM_CCMR1_OC1PE;	//PWM���[�h2,CH1
	TIM1->CCMR2 = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0 |
			TIM_CCMR2_OC4PE;	//PWM���[�h2,CH4
	TIM1->CCER = TIM_CCER_CC1E | TIM_CCER_CC4E;		//TIM1_CH1,CH4�o�͗L��
	TIM1->BDTR = TIM_BDTR_MOE;

	TIM1->CNT = 0;					//�^�C�}�J�E���^�l��0�Ƀ��Z�b�g
	TIM1->PSC = 1-1;					//�^�C�}�̃N���b�N���g�����V�X�e���N���b�N/1=64MHz�ɐݒ�
	TIM1->ARR = INTERVAL;	//�^�C�}�J�E���^�̏���l�BPWM����64MHz/1280=50kHz
	TIM1->CCR1 = 0;				//�^�C�}�J�E���^�̔�r��v�l
	TIM1->CCR4 = 0;				//�^�C�}�J�E���^�̔�r��v�l


	//���[�^�[�p
	// PA6 �� Alternative Function �ɐݒ肷��
	GPIOA->MODER &= ~(1 << 12);
	GPIOA->MODER |= 1 << 13;
	// PA6 �� AF2�ɐݒ肷��
	GPIOA->AFR[0] |= (GPIO_AF2_TIM3 << GPIO_AFRL_AFRL6_Pos);

	// PA4 �� Alternative Function �ɐݒ肷��
	GPIOA->MODER &= ~(1 << 8);
	GPIOA->MODER |= 1 << 9;
	// PA4 �� AF2 �ɐݒ肷��
	GPIOA->AFR[0] |= (GPIO_AF2_TIM3 << GPIO_AFRL_AFRL4_Pos);

	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Clock supply enable

	TIM3->CR1 = TIM_CR1_CEN;						//�^�C�}�L��
	TIM3->CR2 = 0;
	TIM3->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 |  TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1PE |
			TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2PE;	//PWM���[�h2,CH1,CH2
	TIM3->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;		//TIM3_CH1,CH2�o�͗L��
	TIM3->BDTR = TIM_BDTR_MOE;

	TIM3->CNT = 0;					//�^�C�}�J�E���^�l��0�Ƀ��Z�b�g
	TIM3->PSC = 1-1;					//�^�C�}�̃N���b�N���g�����V�X�e���N���b�N/1=64MHz�ɐݒ�
	TIM3->ARR = INTERVAL;	//�^�C�}�J�E���^�̏���l�BPWM����64MHz/1280=50kHz
	TIM3->CCR1 = 0;				//�^�C�}�J�E���^�̔�r��v�l
	TIM3->CCR2 = 0;				//�^�C�}�J�E���^�̔�r��v�l
}

//====�E���[�^��]====
void motor_R(float duty){//-1.0<=duty<0.0�Ȃ�t��]�Aduty==0.0�Ȃ��~�A0.0<duty<=1.0�Ȃ琳��]
	if(duty >= 0.0F){//����]�܂��͒�~
		if(MOTOR_R_FOWARD == 1){//MOTOR_R_FOWARD��1��2���͂ǂ��z�����邩�Ō��܂�
			TIM1->CCR1 = INTERVAL * duty;
			TIM1->CCR4 = 0;
		}else{
			TIM1->CCR1 = 0;
			TIM1->CCR4 = INTERVAL * duty;
		}
	}else{//�t��]
		if(MOTOR_R_FOWARD == 2){//MOTOR_R_FOWARD��1��2���͂ǂ��z�����邩�Ō��܂�
			TIM1->CCR1 = INTERVAL * (-duty);
			TIM1->CCR4 = 0;
		}else{
			TIM1->CCR1 = 0;
			TIM1->CCR4 = INTERVAL * (-duty);
		}
	}
}

//====�����[�^��]====
void motor_L(float duty){//duty>0�Ȃ琳��]�Aduty==0�Ȃ��~�Aduty<0�Ȃ�t��]
	if(duty >= 0.0F){//����]�܂��͒�~
		if(MOTOR_L_FOWARD == 1){//MOTOR_R_FOWARD��1��2���͂ǂ��z�����邩�Ō��܂�
			TIM3->CCR1 = INTERVAL * duty;
			TIM3->CCR2 = 0;
		}else{
			TIM3->CCR1 = 0;
			TIM3->CCR2 = INTERVAL * duty;
		}
	}else{//�t��]
		if(MOTOR_L_FOWARD == 2){//MOTOR_R_FOWARD��1��2���͂ǂ��z�����邩�Ō��܂�
			TIM3->CCR1 = INTERVAL * (-duty);
			TIM3->CCR2 = 0;
		}else{
			TIM3->CCR1 = 0;
			TIM3->CCR2 = INTERVAL * (-duty);
		}
	}
}
