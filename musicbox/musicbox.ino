#include <avr/sleep.h>
#include "sheet.h"
#define WAIT255 for(uint8_t i=-1;i>0;i--)WAIT
#define WAIT {while(!(TIFR&0b10));TIFR|=0b10;}// タイマー0待ち(32us) 強制解除
#define PB0_PUSHED !(PINB&0b1)
#define TRKS_FE for(uint8_t i=0;i<ntrks;i++)
#define MTRKS 4

static const uint16_t t0[]={1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012};//C0~B0

void sleep(){
	uint8_t ddrb=DDRB,portb=PORTB;// ピン設定保存
	DDRB=0;PORTB=1;// PB0:PU
	GIMSK=0b00100000;// [一般割り込み許可レジスタ] - INT0 PCIE - - - - - : PCIEを設定
	PCMSK=0b00000001;// [ピン変化割り込み許可レジスタ] - - PCINT5 PCINT4 PCINT3 PCINT2 PCINT1 PCINT0 : PB0を設定
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);sleep_enable();sleep_cpu();
	// zzZ...
	sleep_disable();
	GIMSK=0;// 割り込み解除
	DDRB=ddrb;PORTB=portb;// ピン復帰
	while(PB0_PUSHED);WAIT255;// PB0解放待機 チャタリング対策
}
ISR(PCINT0_vect){}

void blink(uint8_t x){// 下位bitから読み込み MSBの状態のまま離脱
	static const uint8_t mask=0b00000110;
	for(uint8_t i=0;i<8;i++){
		if((x>>i)&0x1){//1:H, 2:L
			DDRB=(~mask&DDRB)|(mask&0b00000110);PORTB=(~mask&PORTB)|(mask&0b00000010);
		}else{//1:Z, 2:Z
			DDRB=(~mask&DDRB)|(mask&0b00000000);PORTB=(~mask&PORTB)|(mask&0b00000000);
		}
		for(uint16_t j=31250>>4;j>0;j--)WAIT// 1/16秒
	}
}

void play(const uint16_t *s){
	DDRB|=0b00011000;// 3,4出力設定

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
		out,// 出力合成用
		decay,// 減衰カウンタ
		ntrks=0;// 有効トラック数
  bool
    w[MTRKS],// 波形
    d[MTRKS];// 減衰

	dt=75e5/(h>>2); // 最小音価 31250*240/BPM/minNote
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
		TRKS_FE{
			x[i]=1;// チャネルを1で初期化
			_p[i]=p[i];// チャネルポインタ初期化
			l[i]=0;// 音価を0で初期化
		}

		while(_x){
			if(--_dt<ntrks){// 最小音価カウンタが終了に近づいたら
				if(x[_dt]&&(!l[_dt]--)){// 前の音符が存在かつ終了したら
					x[_dt]=pgm_read_word_near(_p[_dt]++);// PROGMEM読込
					v[_dt]=0xff>>(x[_dt]>>15);// 音量
          w[_dt]=(x[_dt]>>14)&0b1;// 波形
          d[_dt]=(x[_dt]>>13)&0b1;// 減衰
					t[_dt]=(x[_dt]&0b1111000000)>0b1011000000?0:t0[(x[_dt]>>6)&0b1111]>>((x[_dt]>>10)&0b111);// オクターブ3bit 音高4bit(12以上は休符)
					l[_dt]=x[_dt]&0b111111;// 音価6bit

					_t[_dt]=0;// 波形生成用カウンタ初期化
				}
				if(!_dt){
					_dt=dt;// 最小音価カウンタリセット
					_x=0;TRKS_FE _x|=x[i];// チャネル合計 終了判定
				}
			}

			out=0;TRKS_FE out+=(_t[i]=(++_t[i]==t[i]?0:_t[i]))<(t[i]>>(w[i]?2:1))?v[i]>>2:0;// 各トラック1/4にして合成 矩形波
			OCR1B=out;// レジスタに入れる

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
	DDRB&=~0b00011000;// 3,4出力解除
}

void setup(){
	// DDRB PORTB:state, 00:IN_HI-Z, 01:IN_P-UP, 10:OUT_L, 11:OUT_H
	DDRB  =0;PORTB =1;// [ポートBレジスタ] PB0:PU
	ADCSRA=0;         // [ADC制御レジスタ A] 停止

	TCCR0A=0b00000011;// [タイマー0制御レジスタ A] COM0A1 COM0A0 COM0B1 COM0B0 - - WGM01 WGM00 : 高速PWM
	TCCR0B=0b00001010;// [タイマー0制御レジスタ B] FOC0A FOC0B - - WGM02 CS02 CS01 CS00 : 高速PWM 1/8分周
	OCR0A =F_CPU/25e4;// [タイマー0レジスタA] 基準クロック 25e4/8=31.25kHz 32us

	TCCR1 =0b00000001;// [タイマー1制御レジスタ A] CTC1 PWM1A COM1A1 COM1A0 CS13 CCS12 CS11 CS10 : 分周無し
	GTCCR =0b01010000;// [タイマー1制御レジスタ B] TSM PWM1B COM1B1 COM1B0 FOC1B FOC1A PSR1 PSR0 : PWM1B PB3有効
	PLLCSR=0b00000111;// [PLL制御状態レジスタ] LSM - - - - PCKE PLLE PLOCK : 通常動作, PCK PLL Plock許可 64MHz動作
	OCR1B=0;OCR1C=255;// [タイマー1レジスタBC] 64e6/255≒250kHz動作

	TIMSK =0b00000000;// [タイマー割り込み許可レジスタ] - OCIE1A OCIE1B OCIE0A OCIE0B TOIE1 TOIE0 : 無効
	TCNT0 =0;TCNT1 =0;// [タイマー] リセット
}
void loop(){
	blink(0b01100110);sleep();play(sheet0);// 再生
	blink(0b01100110);sleep();play(sheet1);// 再生
	blink(0b01100110);sleep();play(sheet2);// 再生
}
