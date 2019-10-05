/*
 * motor.h
 *
 *  Created on: 2018/11/16
 *      Author: iLand
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define INTERVAL 1280

//====機体が前進する際のモータの回転方向====
#define MOTOR_R_FOWARD 2//実際にモーターを回してみて1か2か決める
#define MOTOR_L_FOWARD 1//実際にモーターを回してみて1か2か決める

void motor_pwm_init();
void motor_R(float duty);
void motor_L(float duty);

#endif /* MOTOR_H_ */
