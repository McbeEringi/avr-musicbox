#include <avr/sleep.h>
#include "sheet.h"
#define WAIT255 for(uint8_t i=-1;i>0;i--)WAIT
#define WAIT {while(!(TIFR&_BV_TOV0));TIFR|=_BV_TOV0;}// タイマー0待ち(32us) 強制解除
#define PB0_PUSHED !(PINB&_BV_PINB0)
#define _BV_PINB0 1
#define _BV_TOV0 2
#define MTRKS 4

const uint16_t t0[]={1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012};//C0~B0
const uint8_t v0[]={0x40,0x80,0xc0,0xff};

void sleep(){
	uint8_t ddrb=DDRB,portb=PORTB;// ピン設定保存
	DDRB=0;PORTB=1;// PB0 PU
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

void blink(uint8_t x){// 下位bitから読み込み MSBの状態のまま離脱
	for(uint8_t i=0;i<8;i++){
		for(uint16_t j=31250>>4;j>0;j--)WAIT// 1/16秒
		uint8_t mask=~0b00000110,ddrb=DDRB&mask,portb=PORTB&mask;
		if((x>>i)&0x1){//1:H, 2:L
			DDRB =ddrb +0b00000110;
			PORTB=portb+0b00000010;
		}else{//1:Z, 2:Z
			DDRB =ddrb +0b00000000;
			PORTB=portb+0b00000000;
		}
	}
}

void play(const uint16_t *s){
	DDRB|=0b00011000;// 3,4出力設定

	const uint16_t
		*p[MTRKS];// 各トラックの先頭のポインタ
	bool
		d[MTRKS];// 減衰
	uint8_t
		l[MTRKS],// 音価
		v[MTRKS],// 音量
		w[MTRKS],// 波形
		decay=1,// 減衰用タイマ
		ntrks=0;// 有効トラック数
	uint16_t
		t[MTRKS],_t[MTRKS],// 音高とその波形生成用カウンタ
		dt,_dt=MTRKS,// 最小音価とそのカウンタ(トラック数で初期化(すぐ楽譜読込処理))
		x=1;// PROGMEMから読んだ音符

	dt=75e5/(pgm_read_word_near(s)>>8)/(pgm_read_word_near(s++)&0xff); // 最小音価 31250*240/BPM/minNote
	for(uint8_t i=0;i<MTRKS;){
		l[i]=1;// 音価を1で初期化(すぐ楽譜読込処理)
		w[i]=0;// 波形を初期化(誤作動防止)
		t[i++]=0;//音高の初期化(チャネル未使用の場合に備えて)
	}
	while(ntrks<MTRKS){//トラック数と各トラックの先頭の取得
		if(pgm_read_word_near(s++)!=0)continue;// 0が来るまで飛ばす
		if(pgm_read_word_near(s  )==0)break;// 0,0 譜面終了 離脱
		p[ntrks++]=s;// トラックの先頭を取得
	}

	while(x){// いずれかのパートが終わるまで
		if(--_dt<ntrks){// 最小音価のカウンタが終了に近づいたら
			if(!--l[_dt]){// 前の音符が終了したら
				x=pgm_read_word_near(p[_dt]++);// 楽譜読込
				w[_dt]=((x>>14)&0x3)+1;// 波形2bit
				v[_dt]=v0[(x>>12)&0x3];// 音量2bit
				d[_dt]=(x>>11)&0x1;// 減衰1bit
				t[_dt]=(x&0x00f0)>0x00b0?0:t0[(x>>4)&0xf]>>((x>>8)&0x7);// オクターブ3bit+音高4bit(0-11)(12は休符)
				_t[_dt]=0;// 波形生成用カウンタ初期化
				l[_dt]=(x&0xf)+1;// 音価4bit(MIN_NOTE分音符*N)
			}
			if(!_dt)_dt=dt;// 最小音価カウンタリセット
		}

		OCR1B=// 各トラック1/4にして合成
			(((_t[3]=(++_t[3]==t[3])?0:_t[3])<(t[3]>>w[3]))?v[3]>>2:0)+// 出力波形生成 矩形波
			(((_t[2]=(++_t[2]==t[2])?0:_t[2])<(t[2]>>w[2]))?v[2]>>2:0)+
			(((_t[1]=(++_t[1]==t[1])?0:_t[1])<(t[1]>>w[1]))?v[1]>>2:0)+
			(((_t[0]=(++_t[0]==t[0])?0:_t[0])<(t[0]>>w[0]))?v[0]>>2:0);
		switch(--decay){// 減衰
			case 4:if(d[3])v[3]-=(v[3]>>5);break;// 上位3bitがある間は1-1/2^5倍
			case 3:if(d[2])v[2]-=(v[2]>>5);break;
			case 2:if(d[1])v[1]-=(v[1]>>5);break;
			case 1:if(d[0])v[0]-=(v[0]>>5);break;
			case 0:decay=192;// 32us*192毎
		}

		if(PB0_PUSHED){// PB0押下
			while(PB0_PUSHED);
			WAIT255;// チャタリング対策
			break;
			//sleep();
		}
		WAIT;
	};
	OCR1B=0;// PWMリセット
	DDRB&=~0b00011000;// 3,4出力解除
}

void setup(){
	// DDRB PORTB:state, 00:IN_HI-Z, 01:IN_P-UP, 10:OUT_L, 11:OUT_H
	DDRB  =0;PORTB =1;// [ポートB方向レジスタ] [ポートB出力レジスタ] PB0 PU

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
}
void loop(){
	blink(0b01100110);sleep();play(sheet0);// 再生
	blink(0b01100110);sleep();play(sheet1);// 再生
	blink(0b01100110);sleep();play(sheet2);// 再生
}
