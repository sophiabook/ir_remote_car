/*
 * interrupt.h
 *
 *  Created on: 2018/11/16
 *      Author: iLand
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

void tim6_init(void);
void ms_interrupt_start();

#ifdef EXTERN
volatile float dt = 0.001; // [s]�^�C�}���荞�ݎ���
#else
extern volatile float dt;
#endif

//https://www.grapecity.com/tools/support/powernews/column/clang/033/page02.htm

//----�t���O���p�E�\����----
#ifndef __AIRPLANE_FLAGS__//�Ή��t�@�C���ň�x���ǂݍ��܂�Ă��Ȃ��ꍇ�ȉ����`
	#define __AIRPLANE_FLAGS__//�ǂݍ��񂾂��Ƃ�\��
	typedef union {//���p�̂̐錾
		uint16_t FLAGS;
		struct ap_flags{//�\���̂̐錾
			uint16_t GEI:1;//����|�r�b�g(:1��1�r�b�g���̈Ӗ��A�r�b�g�t�B�[���h)
			uint16_t SCND:1;//�񎟃t���O
			uint16_t SLAL:1;//����t���O
			uint16_t CTRL:1;//����t���O
			uint16_t ACCL:1;//�����t���O
			uint16_t DECL:1;//�����t���O
			uint16_t DEF:1;//�葬�t���O
			uint16_t STOP:1;//��~�t���O
			uint16_t SOUND:1;//���t���O
		}FLAG;
	} airplane_flags;
#endif

#ifdef EXTERN							//�Ή��t�@�C����EXTERN����`����Ă���ꍇ
	volatile airplane_flags AF;			//�X�e�[�^�X���܂Ƃ߂����p�E�\����
#else									//�Ή��t�@�C����EXTERN����`����Ă��Ȃ��ꍇ
	extern volatile airplane_flags AF;
#endif

#endif /* INTERRUPT_H_ */
