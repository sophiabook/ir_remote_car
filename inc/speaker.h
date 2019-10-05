/*
 * speaker.h
 *
 *  Created on: 2019/01/03
 *      Author: iLand
 */

#ifndef SPEAKER_H_
#define SPEAKER_H_

//���̎��g��[Hz]��PWM�����ɕϊ�
//�^�C�}�̃N���b�N���g���̓V�X�e���N���b�N/64=1MHz�ɐݒ肵�Ă���
//(�N���b�N���g��[MHz])/(���̎��g��[Hz])
#define FREQ2PWMPERIOD(X) (int)(1000000 / (X))

//----���K----
//�}�N���̓h�C�c���K
//�h�C�c�� �h���~�t�@�\���V
//�Վ��L���Ȃ�
//C    D   E   F  G   A   H
//�c�F�[ �f�[ �G�[ �G�t �Q�[ �A�[ �n�[
//#���t������
//Cis  Dis  Eis  Fis  Gis Ais His
//�c�B�X �f�B�X �G�C�X �t�B�X �M�X �A�C�X �q�X
//b���t������
//Ces  Des Es Fes  Ges As B
//�c�F�X �f�X �G�X �t�F�X �Q�X �A�X �x�[

#define		C3		130.813
	#define	Cis3	138.591
#define		D3		146.832
	#define	Dis3	155.563
#define		E3		164.814
#define		F3		174.614
	#define	Fis3	184.997
#define		G3		195.998
	#define	Gis3	207.652
#define		A3		220.000
	#define	Ais3	233.082
#define		H3		246.942

#define		C4 		261.626//�h
	#define	Cis4 	277.183//�h#/��b
#define		D4 		293.665//��
	#define	Dis4 	311.127//��#/�~b
#define		E4 		329.628//�~
#define		F4		349.228//�t�@
	#define	Fis4 	369.994//�t�@#/�\b
#define		G_SO4		391.995//�\
	#define	Gis4 	415.305//�\#/��b
#define		A4		440.000//��
	#define	Ais4 	466.164//��#/�Vb
#define		H4 		493.883//�V

#define		C5 		523.251//�h
	#define	Cis5 	554.365//�h#/��b
#define		D5 		587.330//��
	#define	Dis5 	622.254//��#/�~b
#define		E5 		659.255//�~
#define		F5		698.456//�t�@
	#define	Fis5 	739.989//�t�@#/�\b
#define		G5		783.991
	#define	Gis5 	830.609//�\#/��b
#define		A5		880.000//��
	#define	Ais5 	932.328//��#/�Vb
#define		H5 		987.767//�V

//----�L�΂�����[ms]----
#define len1	1536				//�S�����ƑS�x���̒����B2^8*3^2
#define len2	len1 / 2			//�񕪉����Ɠ񕪋x���̒���
#define len2d	len1 / 4 * 3		//���_�񕪉����ƕ��_�񕪋x���̒���
#define len4	len1 / 4			//�l�������Ǝl���x���̒���
#define len4d	len1 / 8 * 3		//���_�l�������ƕ��_�l���x���̒���
#define len3_4	len1 /2 / 3			//�O�A�l�������ƎO�A�l���x���̒���
#define len8	len1 / 8			//���������Ɣ����x���̒���
#define len3_8	len1 / 4 / 3		//�O�A���������ƎO�A�����x���̒���
#define len8d	len1 / 16 * 3		//���_���������ƕ��_�����x���̒���
#define len16	len1 / 16			//�\�Z�������Ə\�Z���x���̒���

//----�x��----
#define rest 0

#ifdef EXTERN
volatile uint16_t score_index = 0;
volatile uint16_t sound_counter = 0;
const float combat_march[2][141] = {
#include "combat_march.h"
};
#else
/*�O���[�o���ϐ��̐錾*/
extern volatile uint16_t score_index;
extern volatile uint16_t sound_counter;
extern const float combat_march[2][141];
#endif

void speaker_pwm_init(void);

#endif /* SPEAKER_H_ */
