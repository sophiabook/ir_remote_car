/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#define EXTERN

#include "global.h"


void init();

int main(void)
{
	init();

	uart_printf("%s\r", "mono_pro");

	while(1) {
		if(ir_available() == true) {
			switch (ir_get_data()) {
			//case POWER:
				//break;
			case A: // music start
				AF.FLAG.SOUND = 1;
				uart_printf("%s\r", "A");
				break;
			case B: // music stop
				AF.FLAG.SOUND = 0;
				uart_printf("%s\r", "B");
				break;
			//case C:
				//break;
			case UP: // go forward
				motor_R(0.1);
				motor_L(0.1);
				uart_printf("%s\r", "UP");
				break;
			case DOWN: // go back
				motor_R(-0.1);
				motor_L(-0.1);
				uart_printf("%s\r", "DOWN");
				break;
			case LEFT: // turn left
				motor_R(0.1);
				motor_L(-0.1);
				uart_printf("%s\r", "LEFT");
				break;
			case RIGHT: // turn right
				motor_R(-0.1);
				motor_L(0.1);
				uart_printf("%s\r", "RIGHT");
				break;
			case SELECT: // stop
				motor_R(0);
				motor_L(0);
				uart_printf("%s\r", "SELECT");
				break;
			//case UP_LEFT:
				//break;
			//case DOWN_LEFT:
				//break;
			//case UP_RIGHT:
				//break;
			//case DOWN_RIGHT:
				//break;
			//default:
				//break;
			}
			ir_data_available = false;
		}
	}
    return 0;
}

void init(){
	sysclk_init(16);
	usart_init(19200);
	receiver_init();

	hardware_exti_init();
	attach_external_interrupt();

	tim7_init();
	start_100us_interrupt();

	tim6_init();
	ms_interrupt_start();

	speaker_pwm_init();

	motor_pwm_init();
}
