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
volatile float dt = 0.001; // [s]タイマ割り込み周期
#else
extern volatile float dt;
#endif

//https://www.grapecity.com/tools/support/powernews/column/clang/033/page02.htm

//----フラグ共用・構造体----
#ifndef __AIRPLANE_FLAGS__//対応ファイルで一度も読み込まれていない場合以下を定義
	#define __AIRPLANE_FLAGS__//読み込んだことを表す
	typedef union {//共用体の宣言
		uint16_t FLAGS;
		struct ap_flags{//構造体の宣言
			uint16_t GEI:1;//宴会芸ビット(:1は1ビット分の意味、ビットフィールド)
			uint16_t SCND:1;//二次フラグ
			uint16_t SLAL:1;//旋回フラグ
			uint16_t CTRL:1;//制御フラグ
			uint16_t ACCL:1;//加速フラグ
			uint16_t DECL:1;//減速フラグ
			uint16_t DEF:1;//定速フラグ
			uint16_t STOP:1;//停止フラグ
			uint16_t SOUND:1;//音フラグ
		}FLAG;
	} airplane_flags;
#endif

#ifdef EXTERN							//対応ファイルでEXTERNが定義されている場合
	volatile airplane_flags AF;			//ステータスをまとめた共用・構造体
#else									//対応ファイルでEXTERNが定義されていない場合
	extern volatile airplane_flags AF;
#endif

#endif /* INTERRUPT_H_ */
