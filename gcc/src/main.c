#define F_CPU 8000000// 8MHz
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include "sheet.h"
#define WAIT255 for(uint8_t i=-1;i>0;i--)WAIT
#define WAIT {while(!(TIFR&0b10));TIFR|=0b10;}// タイマー0待ち(32us) 強制解除
#define PB0_PUSHED !(PINB&0b1)
#define FOR(X) for(uint8_t i=0;i<X;i++)
#define MTRKS 4
#define _OUT OUT(3)OUT(2)OUT(1)OUT(0)
#define OUT(I) +((_t[I]=(++_t[I]==t[I]?0:_t[I]))<(t[I]>>(w[I]?2:1))?v[I]>>2:0)// 各トラック1/4にして合成 矩形波

static const uint16_t t0[]={1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012};//C0~B0

void sleep(){
	const uint8_t ocr1b=OCR1B;
	OCR1B=0;// PWM停止
	GIMSK=0b00100000;// [一般割り込み許可レジスタ] - INT0 PCIE - - - - - : PCIE
	PCMSK=0b00000001;// [ピン変化割り込み許可レジスタ] - - PCINT5 PCINT4 PCINT3 PCINT2 PCINT1 PCINT0 : PB0
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);sleep_mode();// zzZ...
	GIMSK=0;PCMSK=0;// 割り込み解除
	while(PB0_PUSHED);WAIT255;// PB0解放待機 チャタリング対策
	OCR1B=ocr1b;// PWM復帰
}ISR(PCINT0_vect){}

void blink(uint8_t x){// 下位bitから読み込み MSBの状態のまま離脱
	for(uint8_t i=0;i<8;i++){
		if((x>>i)&0b1)PORTB|=0b10;//1:H
		else PORTB&=~0b10;//1:L
		for(uint16_t j=31250>>4;j>0;j--)WAIT// 1/16秒
	}
}

void play(const uint16_t *s){
	const uint16_t
		*p[MTRKS],*_p[MTRKS];// チャネルポインタ ループ用に二重保存
	uint16_t
		x[MTRKS],_x,// PROGMEMから読んだ音符とその合計
		t[MTRKS],_t[MTRKS],// 音高とその波形生成用カウンタ
		dt,_dt,// 最小音価とそのカウンタ
		h=pgm_read_word_near(s++);// ヘッダー
	uint8_t
		v[MTRKS],// 音量
		l[MTRKS],// 音価
		decay,// 減衰カウンタ
		ntrks=0;// 有効トラック数
	bool
		w[MTRKS],// 波形
		d[MTRKS];// 減衰

	dt=75e5/(h>>2); // 最小音価 31250*240/BPM/minNote
	FOR(MTRKS)t[i]=0;// 音高を0で初期化 ノイズ防止
	while(ntrks<MTRKS){
		if(pgm_read_word_near(s++)==0){// 0 チャネル先頭
			if(pgm_read_word_near(s  )==0)break;// 0,0 楽譜終端 離脱
			p[ntrks++]=s;// チャネルポインタ読取
		}
	}

	while(1){
		_x=1;/// チャネル合計を1で初期化
		_dt=ntrks;// 最小音価カウンタをトラック数で初期化
		decay=1;// 減衰カウンタを1で初期化
		FOR(ntrks){
			x[i]=1;// チャネルを1で初期化
			_p[i]=p[i];// チャネルポインタ初期化
			l[i]=0;// 音価を0で初期化
		}

		while(_x){
			if(--_dt<ntrks){// 最小音価カウンタが終了に近づいたら
				if(x[_dt]&&!l[_dt]--){// 前の音符が存在かつ終了したら
					x[_dt]=pgm_read_word_near(_p[_dt]++);// PROGMEM読込
					v[_dt]=0xff>>(x[_dt]>>15);// 音量
					w[_dt]=(x[_dt]>>14)&0b1;// 波形
					d[_dt]=(x[_dt]>>13)&0b1;// 減衰
					t[_dt]=(!x[_dt]||((x[_dt]>>6)&0b1111)>0b1011)?0:t0[(x[_dt]>>6)&0b1111]>>((x[_dt]>>10)&0b111);// オクターブ3bit 音高4bit(12以上は休符)
					l[_dt]=x[_dt]&0b111111;// 音価6bit

					_t[_dt]=0;// 波形生成用カウンタ初期化
				}
				if(!_dt){
					_dt=dt;// 最小音価カウンタリセット
					_x=0;FOR(ntrks)_x|=x[i];// チャネル合計 終了判定
				}
			}

			OCR1B=_OUT;// 波形生成 詳しくはマクロ参照

			if(--decay<ntrks){// 減衰
				if(!d[decay])v[decay]-=(v[decay]>>5);// 上位3bitがある間は1-1/2^5倍
				if(!decay)decay=192;// 32us*192毎
			}

			WAIT;
			if(PB0_PUSHED){// PB0押下
				while(PB0_PUSHED);WAIT255;// PB0解放待機 チャタリング対策
				if(!(h&0b1))break;// 一時停止でなければ離脱
				blink(0b01010101);sleep();
			}
		}
		if(!((h>>1)&0b1)||_x)break;// ループでないまたは再生途中なら
	}
	OCR1B=0;// PWMリセット
}

void main(){
	TCCR0A=0b00000011;// [タイマー0制御レジスタ A] COM0A1 COM0A0 COM0B1 COM0B0 - - WGM01 WGM00 : 高速PWM
	TCCR0B=0b00001010;// [タイマー0制御レジスタ B] FOC0A FOC0B - - WGM02 CS02 CS01 CS00 : 高速PWM 1/8分周
	OCR0A =F_CPU/25e4;// [タイマー0レジスタA] 基準クロック 25e4/8=31.25kHz 32us

	TCCR1 =0b00000001;// [タイマー1制御レジスタ A] CTC1 PWM1A COM1A1 COM1A0 CS13 CCS12 CS11 CS10 : 分周無し
	GTCCR =0b01100000;// [タイマー1制御レジスタ B] TSM PWM1B COM1B1 COM1B0 FOC1B FOC1A PSR1 PSR0 : PWM1B PB4のみ有効
	PLLCSR=0b00000111;// [PLL制御状態レジスタ] LSM - - - - PCKE PLLE PLOCK : 通常動作, PCK PLL Plock許可 64MHz動作
	OCR1B=0;OCR1C=255;// [タイマー1レジスタBC] 64e6/256=250kHz動作

	// DDRB PORTB:state, 00:IN_HI-Z, 01:IN_P-UP, 10:OUT_L, 11:OUT_H
	DDRB  =0b00011110;// [ポートB方向レジスタ] OUT : PB1,2,3,4
	PORTB =0b00000001;// [ポートB出力レジスタ] PU|H: PB0
	ADCSRA=0;         // [ADC制御レジスタ A] 停止
	TIMSK =0;         // [タイマー割り込み許可レジスタ] 無効
	TCNT0 =0;TCNT1 =0;// [タイマー] リセット
	while(1){
		blink(0b01100110);sleep();play(sanpo);// 再生
		blink(0b01100110);sleep();play(nyan);
		blink(0b01100110);sleep();play(yobikomi);
		blink(0b01100110);sleep();play(kewpie);
		blink(0b01100110);sleep();play(small_world);
	}
}