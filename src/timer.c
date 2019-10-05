/*
 * timer.c
 *
 *  Created on: 2019/01/06
 *      Author: iLand
 */

#include "global.h"

void tim7_init(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN; // Clock supply enable
	TIM7->CR1 = TIM_CR1_CEN;		//�^�C�}�L��
	TIM7->CR2 = 0;
	TIM7->DIER = TIM_DIER_UIE;		//�^�C�}�X�V���荞�݂�L����
	TIM7->CNT = 0;					//�^�C�}�J�E���^�l��0�Ƀ��Z�b�g
	TIM7->PSC = 64-1;				//�^�C�}�̃N���b�N���g�����V�X�e���N���b�N/64=1MHz�ɐݒ�
	TIM7->ARR = 100-1;				//�^�C�}�J�E���^�̏���l�B100�ɐݒ�B�䂦��0.1ms���ƂɊ��荞�ݔ���

	TIM7->EGR = TIM_EGR_UG;			//�^�C�}�ݒ�𔽉f�����邽�߂Ƀ^�C�}�X�V�C�x���g���N����
}



void TIM7_DAC2_IRQHandler(void){

	if( !(TIM7->SR & TIM_SR_UIF) ){
		return;
	}

	time_cnt++;
	TIM7->SR &= ~TIM_SR_UIF;
}

void start_100us_interrupt(){
	NVIC_EnableIRQ(TIM7_DAC2_IRQn);			//�^�C�}�X�V���荞�݃n���h����L����
	NVIC_SetPriority(TIM7_DAC2_IRQn, 1);	//�^�C�}�X�V���荞�݂̊��荞�ݗD��x��ݒ�
}

void sysclk_init(uint8_t multiple) { // max clock = 64MHz
	if( multiple <= 0 || multiple > 16 ) {
		return;
	}
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2; // PLL <== HSI/2 = 4MHz
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1 = PLL / 2 = 32MHz
	RCC->CFGR |= ( (multiple - 1) << RCC_CFGR_PLLMUL_Pos);
	FLASH->ACR |= FLASH_ACR_LATENCY_1; // flash access latency for 48 < HCLK <= 72. This statement must be placed immediately after PLL multiplication.
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY)); // wait until PLL is ready
	RCC->CFGR |= RCC_CFGR_SW_PLL; // PLL as system clock
	while( (RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL ); // wait until PLL clock supply starts
	SystemCoreClockUpdate();
}

void ms_wait(uint32_t ms) {
	SysTick->LOAD	=	8000 - 1; // reset value for count-down timer
	SysTick->VAL	=	0; // initial value
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // count start
	for(uint32_t i=0; i<ms; i++){
		while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) );
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // count stop
}

uint32_t time_interval(uint32_t now, uint32_t past){ // [10^-4 * s]
	uint32_t interval;
	if(now < past){
		interval = (0xFFFFFFFF - past) + now;
	}else{
		interval = now - past;
	}
	return interval;
}
