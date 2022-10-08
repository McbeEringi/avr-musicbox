#include "sheet.h"
#define TRKS 4
#define WAIT {while(!(TIFR&_BV_TOV0));TIFR|=_BV_TOV0;}// タイマー0待ち(32us) 強制解除
#define _BV_PINB0 1
#define _BV_TOV0 2

const uint16_t t0[]={1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012};//C0~B0
const uint8_t pulse[]={0b01000000,0b01100000,0b01111000,0b10011111};
const uint8_t tri[]={255,238,221,204,187,170,153,136,119,102,85,68,51,34,17,0,0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255};

void core(const uint16_t *d){
	DDRB|=0b00011110;// 1,2,3,4出力設定

	const uint16_t *p[TRKS];// 各トラックの先頭のポインタ
	uint8_t
		l[TRKS],// 音価
		env=1;// 減衰用タイマ
	uint16_t
		note,// PROGMEMから読んだ音符
		dt,_dt=TRKS,// 最小音価とそのカウンタ (トラック数で初期化(すぐ楽譜読込処理))
		t[TRKS],_t[TRKS],// 音高とその波形生成用カウンタ
		v[TRKS],// 音量
		out[TRKS];// 出力

	dt=75e5/pgm_read_word_near(d++)/MIN_NOTE; // 最小音価 31250*240/BPM/minNote
	for(uint8_t i=0;1;){//トラック数と各トラックの先頭の取得
		if(pgm_read_word_near(d++)!=0)continue;// 0が来るまで飛ばす
		if(pgm_read_word_near(d  )==0)break;// 0,0 譜面終了 離脱
		l[i]=1;// 音価を1で初期化(すぐ楽譜読込処理)
		p[i++]=d;// トラックの先頭を取得
	}

	do{
		if(--_dt<TRKS){// 最小音価のカウンタが終了に近づいたら
			if(!--l[_dt]){// 前の音符が終了したら
				note=pgm_read_word_near(p[_dt]++);// 楽譜読込
				l[_dt]=(uint8_t)note;// 下位8bitが音価 (96分音符*N)
				t[_dt]=(note>>8)?t0[(note>>8)&0xf]>>(note>>12):0;// 上位4bitがオクターブ 中位4bitが音高 (1-12)(0は休符)
				_t[_dt]=0;// 波形生成用カウンタを0で初期化
				v[_dt]=0xffff;// 最大音量で初期化
			}
			if(!_dt)_dt=dt;// 最小音価カウンタリセット
		}

		out[3]=((_t[3]=(++_t[3]==t[3])?0:_t[3])<(t[3]>>2))?v[3]:0;// 出力波形生成 25%矩形波
		out[2]=((_t[2]=(++_t[2]==t[2])?0:_t[2])<(t[2]>>2))?v[2]:0;
		out[1]=((_t[1]=(++_t[1]==t[1])?0:_t[1])<(t[1]>>2))?v[1]:0;
		out[0]=((_t[0]=(++_t[0]==t[0])?0:_t[0])<(t[0]>>2))?v[0]:0;
		OCR1B=((out[0]>>2)+(out[1]>>2)+(out[2]>>2)+(out[3]>>2))>>8;// 各トラック1/4にして合成 上位8bitを出力
		switch(--env){// 減衰
			case 4:v[3]-=(v[3]>>8);break;// 1-1/2^8倍
			case 3:v[2]-=(v[2]>>8);break;
			case 2:v[1]-=(v[1]>>8);break;
			case 1:v[0]-=(v[0]>>8);break;
			case 0:env=32;// 32us*32毎
		}

		if(!(PINB&_BV_PINB0))break;// PB0押下で離脱
		WAIT;
	}while(note);
	OCR1B=0;
	DDRB&=~0b00011110;// 1,2,3,4出力解除
}

void setup(){
	// DDRB PORTB:state, 00:IN_HI-Z, 01:IN_P-UP, 10:OUT_L, 11:OUT_H

	// 0: INPUT_PULLUP
	// 1: HIGH
	// 2: LOW
	// --ZZZLHP
	DDRB  =0b00000110;// [ポートB方向レジスタ] OUT 1 2
	PORTB =0b00000011;// [ポートB出力レジスタ] PU||H 0 1

	ADCSRA=0;         // [ADC制御レジスタ A] 停止

	TCCR0A=0b00000011;// [タイマー0制御レジスタ A] COM0A1 COM0A0 COM0B1 COM0B0 - - WGM01 WGM00 : 高速PWM
	TCCR0B=0b00001010;// [タイマー0制御レジスタ B] FOC0A FOC0B - - WGM02 CS02 CS01 CS00 : 高速PWM 1/8分周
	OCR0A =F_CPU/25e4;// [タイマ0レジスタA] 基準クロック 31.25kHz 32us

	TCCR1 =0b00000001;// [タイマー1制御レジスタ A] CTC1 PWM1A COM1A1 COM1A0 CS13 CCS12 CS11 CS10 : 分周無し
	GTCCR =0b01010000;// [タイマー1制御レジスタ B] TSM PWM1B COM1B1 COM1B0 FOC1B FOC1A PSR1 PSR0 : PWM1B PB3有効
	PLLCSR=0b00000111;// [PLL制御状態レジスタ] LSM - - - - PCKE PLLE PLOCK : 通常動作, PCK PLL Plock許可 64MHz動作
	OCR1B=0;OCR1C=255;// [タイマ1レジスタBC] 250kHz動作

	TIMSK =0b00000000;// [タイマ―割り込み許可レジスタ] - OCIE1A OCIE1B OCIE0A OCIE0B TOIE1 TOIE0 : 無効
	TCNT0 =0;TCNT1 =0;// [タイマー] リセット

	DDRB=0;
	for(uint16_t i=31250>>2;i>0;i--)WAIT;DDRB=0b00000110;
	for(uint16_t i=31250>>3;i>0;i--)WAIT;DDRB=0;
	for(uint16_t i=31250>>3;i>0;i--)WAIT;DDRB=0b00000110;
	for(uint16_t i=31250>>3;i>0;i--)WAIT;DDRB=0;
}
void loop(){
	while( (PINB&_BV_PINB0));// PB0解放
	while(!(PINB&_BV_PINB0));// PB0押下
	core(sheet);// 再生
}
