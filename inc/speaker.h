/*
 * speaker.h
 *
 *  Created on: 2019/01/03
 *      Author: iLand
 */

#ifndef SPEAKER_H_
#define SPEAKER_H_

//音の周波数[Hz]をPWM周期に変換
//タイマのクロック周波数はシステムクロック/64=1MHzに設定してある
//(クロック周波数[MHz])/(音の周波数[Hz])
#define FREQ2PWMPERIOD(X) (int)(1000000 / (X))

//----音階----
//マクロはドイツ音階
//ドイツ語 ドレミファソラシ
//臨時記号なし
//C    D   E   F  G   A   H
//ツェー デー エー エフ ゲー アー ハー
//#が付いた時
//Cis  Dis  Eis  Fis  Gis Ais His
//ツィス ディス エイス フィス ギス アイス ヒス
//bが付いた時
//Ces  Des Es Fes  Ges As B
//ツェス デス エス フェス ゲス アス ベー

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

#define		C4 		261.626//ド
	#define	Cis4 	277.183//ド#/レb
#define		D4 		293.665//レ
	#define	Dis4 	311.127//レ#/ミb
#define		E4 		329.628//ミ
#define		F4		349.228//ファ
	#define	Fis4 	369.994//ファ#/ソb
#define		G_SO4		391.995//ソ
	#define	Gis4 	415.305//ソ#/ラb
#define		A4		440.000//ラ
	#define	Ais4 	466.164//ラ#/シb
#define		H4 		493.883//シ

#define		C5 		523.251//ド
	#define	Cis5 	554.365//ド#/レb
#define		D5 		587.330//レ
	#define	Dis5 	622.254//レ#/ミb
#define		E5 		659.255//ミ
#define		F5		698.456//ファ
	#define	Fis5 	739.989//ファ#/ソb
#define		G5		783.991
	#define	Gis5 	830.609//ソ#/ラb
#define		A5		880.000//ラ
	#define	Ais5 	932.328//ラ#/シb
#define		H5 		987.767//シ

//----伸ばす長さ[ms]----
#define len1	1536				//全音符と全休符の長さ。2^8*3^2
#define len2	len1 / 2			//二分音符と二分休符の長さ
#define len2d	len1 / 4 * 3		//符点二分音符と符点二分休符の長さ
#define len4	len1 / 4			//四分音符と四分休符の長さ
#define len4d	len1 / 8 * 3		//符点四分音符と符点四分休符の長さ
#define len3_4	len1 /2 / 3			//三連四分音符と三連四分休符の長さ
#define len8	len1 / 8			//八分音符と八分休符の長さ
#define len3_8	len1 / 4 / 3		//三連八分音符と三連八分休符の長さ
#define len8d	len1 / 16 * 3		//符点八分音符と符点八分休符の長さ
#define len16	len1 / 16			//十六分音符と十六分休符の長さ

//----休み----
#define rest 0

#ifdef EXTERN
volatile uint16_t score_index = 0;
volatile uint16_t sound_counter = 0;
const float combat_march[2][141] = {
#include "combat_march.h"
};
#else
/*グローバル変数の宣言*/
extern volatile uint16_t score_index;
extern volatile uint16_t sound_counter;
extern const float combat_march[2][141];
#endif

void speaker_pwm_init(void);

#endif /* SPEAKER_H_ */
