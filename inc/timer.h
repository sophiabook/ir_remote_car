/*
 * timer.h
 *
 *  Created on: 2019/01/06
 *      Author: iLand
 */

#ifndef TIMER_H_
#define TIMER_H_

#ifdef EXTERN
volatile uint32_t time_cnt = 0;
#else
extern volatile uint32_t time_cnt;
#endif

void tim7_init(void);
void start_100us_interrupt();
void sysclk_init(uint8_t multiple);
void ms_wait(uint32_t ms);
uint32_t time_interval(uint32_t now, uint32_t past);



#endif /* TIMER_H_ */
