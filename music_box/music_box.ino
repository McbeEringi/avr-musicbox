#include <avr/sleep.h>
#include "sheet.h"
#define WAIT255 for(uint8_t i=-1;i>0;i--)WAIT
#define WAIT_(x) for(uint16_t i=31250>>(x);i>0;i--)WAIT
#define WAIT {while(!(TIFR&_BV_TOV0));TIFR|=_BV_TOV0;}// タイマー0待ち(32us) 強制解除
#define PB0_PUSHED !(PINB&_BV_PINB0)
#define _BV_PINB0 1
#define _BV_TOV0 2
#define MTRKS 4

const uint16_t t0[]={1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012};//C0~B0

void sleep(){
	uint8_t ddrb=DDRB,portb=PORTB;// ピン設定保存
	DDRB=0;PORTB=1;// PB0以外無効化
	GIMSK=0b00100000;// [一般割り込み許可レジスタ] - INT0 PCIE - - - - - : PCIEを設定
	PCMSK=0b00000001;// [ピン変化割り込み許可レジスタ] - - PCINT5 PCINT4 PCINT3 PCINT2 PCINT1 PCINT0 : PB0を設定
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_cpu();
	// zzZ...
	sleep_disable();
	GIMSK=0;// 割り込み解除
	DDRB=ddrb;PORTB=portb;// ピン復帰
	while(PB0_PUSHED);// PB0押下
	WAIT255;// チャタリング対策
}
ISR(PCINT0_vect){}

void play(const uint16_t *d){
	DDRB|=0b00011110;// 1,2,3,4出力設定

	const uint16_t *p[MTRKS];// 各トラックの先頭のポインタ
	uint8_t
		l[MTRKS],// 音価
		v[MTRKS],// 音量
		decay=1,// 減衰用タイマ
		ntrks=0;// 有効トラック数
	uint16_t
		w,// PROGMEMから読んだ音符
		dt,_dt=MTRKS,// 最小音価とそのカウンタ(トラック数で初期化(すぐ楽譜読込処理))
		t[MTRKS],_t[MTRKS];// 音高とその波形生成用カウンタ

	dt=75e5/pgm_read_word_near(d++)/MIN_NOTE; // 最小音価 31250*240/BPM/minNote
	for(uint8_t i=0;i<MTRKS;){
		l[i]=1;// 音価を1で初期化(すぐ楽譜読込処理)
		t[i++]=0;//音高の初期化(チャネル未使用の場合に備えて)
	}
	for(;ntrks<MTRKS;){//トラック数と各トラックの先頭の取得
		if(pgm_read_word_near(d++)!=0)continue;// 0が来るまで飛ばす
		if(pgm_read_word_near(d  )==0)break;// 0,0 譜面終了 離脱
		p[ntrks++]=d;// トラックの先頭を取得
	}

	do{
		if(--_dt<ntrks){// 最小音価のカウンタが終了に近づいたら
			if(!--l[_dt]){// 前の音符が終了したら
				w=pgm_read_word_near(p[_dt]++);// 楽譜読込
				l[_dt]=w;// 下位8bitが音価 (MIN_NOTE分音符*N) (uint8_t=uint16_tなので自動的に下位8bitが読まれる)
				t[_dt]=(w>>8)?t0[(w>>8)&0xf]>>(w>>12):0;// 上位4bitがオクターブ 中位4bitが音高 (1-12)(0は休符)
				_t[_dt]=0;// 波形生成用カウンタを0で初期化
				v[_dt]=0xff;// 最大音量で初期化
			}
			if(!_dt)_dt=dt;// 最小音価カウンタリセット
		}

		OCR1B=// 各トラック1/4にして合成
			(((_t[3]=(++_t[3]==t[3])?0:_t[3])<(t[3]>>2))?v[3]>>2:0)+// 出力波形生成 25%矩形波
			(((_t[2]=(++_t[2]==t[2])?0:_t[2])<(t[2]>>2))?v[2]>>2:0)+
			(((_t[1]=(++_t[1]==t[1])?0:_t[1])<(t[1]>>2))?v[1]>>2:0)+
			(((_t[0]=(++_t[0]==t[0])?0:_t[0])<(t[0]>>2))?v[0]>>2:0);
		switch(--decay){// 減衰
			case 4:v[3]-=(v[3]>>6);break;// 上位2bitがある間は1-1/2^6倍
			case 3:v[2]-=(v[2]>>6);break;
			case 2:v[1]-=(v[1]>>6);break;
			case 1:v[0]-=(v[0]>>6);break;
			case 0:decay=96;// 32us*96毎
		}

		if(PB0_PUSHED){// PB0押下
			while(PB0_PUSHED);
			WAIT255;// チャタリング対策
			break;//sleep();
		}
		WAIT;
	}while(w);
	OCR1B=0;// PWMリセット
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
	OCR0A =F_CPU/25e4;// [タイマ0レジスタA] 基準クロック 25e4/8=31.25kHz 32us

	TCCR1 =0b00000001;// [タイマー1制御レジスタ A] CTC1 PWM1A COM1A1 COM1A0 CS13 CCS12 CS11 CS10 : 分周無し
	GTCCR =0b01010000;// [タイマー1制御レジスタ B] TSM PWM1B COM1B1 COM1B0 FOC1B FOC1A PSR1 PSR0 : PWM1B PB3有効
	PLLCSR=0b00000111;// [PLL制御状態レジスタ] LSM - - - - PCKE PLLE PLOCK : 通常動作, PCK PLL Plock許可 64MHz動作
	OCR1B=0;OCR1C=255;// [タイマ1レジスタBC] 64e6/255≒250kHz動作

	TIMSK =0b00000000;// [タイマ―割り込み許可レジスタ] - OCIE1A OCIE1B OCIE0A OCIE0B TOIE1 TOIE0 : 無効
	TCNT0 =0;TCNT1 =0;// [タイマー] リセット

	DDRB=0;
	WAIT_(2);DDRB=0b00000110;
	WAIT_(3);DDRB=0;
	WAIT_(3);DDRB=0b00000110;
	WAIT_(3);DDRB=0;
}
void loop(){
	sleep();play(sheet);// 再生
	sleep();play(sheet0);// 再生
	sleep();play(sheet12);// 再生
	sleep();play(sheet3);// 再生
}
