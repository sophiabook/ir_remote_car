/*
 * motor.h
 *
 *  Created on: 2018/11/16
 *      Author: iLand
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define INTERVAL 1280

//====�@�̂��O�i����ۂ̃��[�^�̉�]����====
#define MOTOR_R_FOWARD 2//���ۂɃ��[�^�[���񂵂Ă݂�1��2�����߂�
#define MOTOR_L_FOWARD 1//���ۂɃ��[�^�[���񂵂Ă݂�1��2�����߂�

void motor_pwm_init();
void motor_R(float duty);
void motor_L(float duty);

#endif /* MOTOR_H_ */
