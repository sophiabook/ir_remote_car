/*
 * motor.c
 *
 *  Created on: 2018/11/16
 *      Author: iLand
 */

#include "global.h"

void motor_pwm_init(void) {

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // IO portA clock enable

	/*//ファン用
	// PA12 を Alternative Function に設定する
	GPIOA->MODER &= ~(1 << 24);
	GPIOA->MODER |= 1 << 25;
	// PA12 を AF1に設定する
	GPIOA->AFR[1] |= (GPIO_AF1_TIM16 << GPIO_AFRH_AFRH4_Pos);

	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN; // Clock supply enable

	TIM16->CR1 = TIM_CR1_CEN;						//タイマ有効
	TIM16->CR2 = 0;
	TIM16->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0 |
			TIM_CCMR1_OC1PE;	//PWMモード2,CH1
	TIM16->CCER = TIM_CCER_CC1E;		//TIM16_CH1出力有効
	TIM16->BDTR = TIM_BDTR_MOE;

	TIM16->CNT = 0;					//タイマカウンタ値を0にリセット
	TIM16->PSC = 1-1;					//タイマのクロック周波数をシステムクロック/1=64MHzに設定
	TIM16->ARR = INTERVAL;	//タイマカウンタの上限値。PWM周期64MHz/1280=50kHz
	TIM16->CCR1 = 0;				//タイマカウンタの比較一致値*/

	//モーター用
	// PA8 を Alternate Function に設定する
	GPIOA->MODER &= ~(1 << 16);
	GPIOA->MODER |= 1 << 17;
	// PA8 を AF6に設定する
	GPIOA->AFR[1] |= (GPIO_AF6_TIM1 << GPIO_AFRH_AFRH0_Pos);

	// PA11 を Alternate Function に設定する
	GPIOA->MODER &= ~(1 << 22);
	GPIOA->MODER |= 1 << 23;
	// PA11 を AF11に設定する
	GPIOA->AFR[1] |= (GPIO_AF11_TIM1 << GPIO_AFRH_AFRH3_Pos);


	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // Clock supply enable

	TIM1->CR1 |= TIM_CR1_CEN;						//タイマ有効
	TIM1->CR2 = 0;
	TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0 |
			TIM_CCMR1_OC1PE;	//PWMモード2,CH1
	TIM1->CCMR2 = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0 |
			TIM_CCMR2_OC4PE;	//PWMモード2,CH4
	TIM1->CCER = TIM_CCER_CC1E | TIM_CCER_CC4E;		//TIM1_CH1,CH4出力有効
	TIM1->BDTR = TIM_BDTR_MOE;

	TIM1->CNT = 0;					//タイマカウンタ値を0にリセット
	TIM1->PSC = 1-1;					//タイマのクロック周波数をシステムクロック/1=64MHzに設定
	TIM1->ARR = INTERVAL;	//タイマカウンタの上限値。PWM周期64MHz/1280=50kHz
	TIM1->CCR1 = 0;				//タイマカウンタの比較一致値
	TIM1->CCR4 = 0;				//タイマカウンタの比較一致値


	//モーター用
	// PA6 を Alternative Function に設定する
	GPIOA->MODER &= ~(1 << 12);
	GPIOA->MODER |= 1 << 13;
	// PA6 を AF2に設定する
	GPIOA->AFR[0] |= (GPIO_AF2_TIM3 << GPIO_AFRL_AFRL6_Pos);

	// PA4 を Alternative Function に設定する
	GPIOA->MODER &= ~(1 << 8);
	GPIOA->MODER |= 1 << 9;
	// PA4 を AF2 に設定する
	GPIOA->AFR[0] |= (GPIO_AF2_TIM3 << GPIO_AFRL_AFRL4_Pos);

	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Clock supply enable

	TIM3->CR1 = TIM_CR1_CEN;						//タイマ有効
	TIM3->CR2 = 0;
	TIM3->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 |  TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1PE |
			TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2PE;	//PWMモード2,CH1,CH2
	TIM3->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;		//TIM3_CH1,CH2出力有効
	TIM3->BDTR = TIM_BDTR_MOE;

	TIM3->CNT = 0;					//タイマカウンタ値を0にリセット
	TIM3->PSC = 1-1;					//タイマのクロック周波数をシステムクロック/1=64MHzに設定
	TIM3->ARR = INTERVAL;	//タイマカウンタの上限値。PWM周期64MHz/1280=50kHz
	TIM3->CCR1 = 0;				//タイマカウンタの比較一致値
	TIM3->CCR2 = 0;				//タイマカウンタの比較一致値
}

//====右モータ回転====
void motor_R(float duty){//-1.0<=duty<0.0なら逆回転、duty==0.0なら停止、0.0<duty<=1.0なら正回転
	if(duty >= 0.0F){//正回転または停止
		if(MOTOR_R_FOWARD == 1){//MOTOR_R_FOWARDが1か2かはどう配線するかで決まる
			TIM1->CCR1 = INTERVAL * duty;
			TIM1->CCR4 = 0;
		}else{
			TIM1->CCR1 = 0;
			TIM1->CCR4 = INTERVAL * duty;
		}
	}else{//逆回転
		if(MOTOR_R_FOWARD == 2){//MOTOR_R_FOWARDが1か2かはどう配線するかで決まる
			TIM1->CCR1 = INTERVAL * (-duty);
			TIM1->CCR4 = 0;
		}else{
			TIM1->CCR1 = 0;
			TIM1->CCR4 = INTERVAL * (-duty);
		}
	}
}

//====左モータ回転====
void motor_L(float duty){//duty>0なら正回転、duty==0なら停止、duty<0なら逆回転
	if(duty >= 0.0F){//正回転または停止
		if(MOTOR_L_FOWARD == 1){//MOTOR_R_FOWARDが1か2かはどう配線するかで決まる
			TIM3->CCR1 = INTERVAL * duty;
			TIM3->CCR2 = 0;
		}else{
			TIM3->CCR1 = 0;
			TIM3->CCR2 = INTERVAL * duty;
		}
	}else{//逆回転
		if(MOTOR_L_FOWARD == 2){//MOTOR_R_FOWARDが1か2かはどう配線するかで決まる
			TIM3->CCR1 = INTERVAL * (-duty);
			TIM3->CCR2 = 0;
		}else{
			TIM3->CCR1 = 0;
			TIM3->CCR2 = INTERVAL * (-duty);
		}
	}
}
