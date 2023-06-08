#define DIGISPARK
#ifdef DIGISPARK
	#define F_CPU 16500000// 16.5MHz
#else
	#define F_CPU 8000000// 8MHz
#endif
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "seq.h"

#define MTRKS 4
#define BTN_DOWN ~PINB&0b1
#define FOR(X) for(uint8_t i=0;i<X;i++)
void wait(){while(!(TIFR&0b10));TIFR|=0b10;}// TCB0待ち(32us) 解除
void wait_btn(){while(BTN_DOWN)FOR(255)wait();}// 0.032*255=8.160ms

const uint16_t n0[]={1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012};// C0~B0

static void sleep(){
	const uint8_t ocr1b=OCR1B;
	OCR1B=0;// PWM停止
	GIMSK=0b00100000;// [一般割り込み許可レジスタ] - INT0 PCIE - - - - - : PCIE
	PCMSK=0b00000001;// [ピン変化割り込み許可レジスタ] - - PCINT5 PCINT4 PCINT3 PCINT2 PCINT1 PCINT0 : PB0
	sei();set_sleep_mode(SLEEP_MODE_PWR_DOWN);sleep_mode();cli();// zzZ...
	GIMSK=0;PCMSK=0;// 割り込み解除
	wait_btn();// PB0解放待機 チャタリング対策
	OCR1B=ocr1b;// PWM復帰
}ISR(PCINT0_vect){}

static void blink(uint8_t x){// 下位bitから読み込み MSBの状態のまま離脱
	for(uint8_t i=0;i<8;i++){
		if((x>>i)&0b1)PORTB|=0b10;//1:H
		else PORTB&=~0b10;//1:L
		for(uint16_t j=31250>>4;j>0;j--)wait();// 1/16秒
	}
}

static void play(const uint8_t *s){
	static const uint8_t
	*p[MTRKS],*_p[MTRKS];// チャネルポインタ ループ用に二重保存
	static uint8_t
	x[MTRKS],// 読んだやつ
	t[MTRKS<<1]={},_t[MTRKS],// 音価
	cfg[MTRKS]={},_v[MTRKS],// 設定項目 音量
	ntrks,// 有効トラック数
	out;
	uint16_t
	h=(pgm_read_byte_near(s++)<<8)|pgm_read_byte_near(s++),// ヘッダ
	n[MTRKS]={},_n[MTRKS],// 音高
	env,// 減衰カウンタ
	dt=75e5/(h>>3),_dt;// 最小音価 40000*240/BPM/minNote

	ntrks=0;
	while(ntrks<MTRKS){if(pgm_read_byte_near(s++)==0){if(pgm_read_byte_near(s)==0)break;p[ntrks++]=s;}}// チャネル数&ポインタ読取
	while(1){
		_dt=ntrks;env=1;FOR(ntrks){_p[i]=p[i];_t[i]=0;x[i]=pgm_read_byte_near(_p[i]);}// 初期化
		while(1){
			if(--_dt<ntrks){
				if(x[_dt]&&!_t[_dt]--){
					while(!(x[_dt]&0x80)){
						if(x[_dt]>>6==1)t[(_dt<<1)|((x[_dt]>>5)&1)]=x[_dt]&0x1f;// 音価メモリ変更
						else if(x[_dt]>>5==1)cfg[_dt]=x[_dt]&0x1f;// 設定項目変更
						else if(x[_dt]==1)goto dc;// 終了フラグ
						x[_dt]=pgm_read_byte_near(++_p[_dt]);
					}
					_t[_dt]=t[(_dt<<1)|((x[_dt]>>6)&1)];// 音価1bit(5bit)
					n[_dt]=(x[_dt]&0xf)>11?0:n0[x[_dt]&0xf]>>(((x[_dt]>>4)&3)+((cfg[_dt]>>3)&1?1:4));// オクターブ2+1bit 音高4bit
					_n[_dt]=0;// 波形カウンタリセット
					_v[_dt]=0xff>>((cfg[_dt]>>2)&1);// 音量 
					x[_dt]=pgm_read_byte_near(++_p[_dt]);
				}
				if(!_dt)_dt=dt;
			}
			out=0;
			FOR(ntrks){// 矩形波合成 1/4
				if(++_n[i]==n[i])_n[i]=0;
				if(_n[i]<(n[i]>>(((cfg[i]>>1)&1)+1)))out+=_v[i]>>2;
			}
			OCR1B=out;
			if(--env<ntrks){if(!(cfg[env]&1))_v[env]-=(_v[env]>>4);if(!env)env=384;}// 減衰 9.6ms毎
			if(BTN_DOWN)goto fin;// ボタン離脱
			wait();
		}
		dc:if(!(h>>2&1))break;// ループ
	}
	fin:OCR1B=0;
	wait_btn();
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
		blink(0b00110011);sleep();play(famima);
		blink(0b00110011);sleep();play(ofuro);
		blink(0b00110011);sleep();play(yobikomi);
		blink(0b00110011);sleep();play(dw3battle);play(dw3level);
	}
}