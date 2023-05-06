#define F_CPU 20000000
#define F_WAV 40000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "seq.h"
#define LED_BUILTIN 3
#define BTN_BUILTIN 7
#define MTRKS 4

#define FOR(X) for(uint8_t i=0;i<X;i++)
#define WAIT_BTN while(BTN_DOWN)WAIT_5
#define BTN_DOWN ~VPORTA.IN&(1<<7)
#define WAIT_5 for(uint8_t i=0;i<200;i++)WAIT// 5ms
#define WAIT do{while(!(TCB0.INTFLAGS&TCB_CAPT_bm));TCB0.INTFLAGS=TCB_CAPT_bm;}while(0)// TCB0待ち(25us) 解除
#define _OUT OUT(3)OUT(2)OUT(1)OUT(0)
#define OUT(I) +((_t[I]=(++_t[I]==t[I]?0:_t[I]))<(t[I]>>1)?v[I]>>2:0)// 各トラック1/4にして合成 矩形波

const uint16_t t0[]={2446,2309,2179,2057,1942,1833,1730,1633,1541,1455,1373,1296};// C0~B0

void sleep(){sei();SLPCTRL.CTRLA=SLPCTRL_SMODE_PDOWN_gc|SLPCTRL_SEN_bm;sleep_cpu();cli();WAIT_BTN;}// avr/sleep.hが仕事しないので手動設定
ISR(PORTA_PORT_vect){PORTA.INTFLAGS=PORT_INT7_bm;}// ピン割り込みはBOTHEDGESかLEVELじゃなきゃ起きない リセット必須

void blink(uint8_t x){// 下位bitから読み込み MSBの状態のまま離脱
	for(uint8_t i=0;i<8;i++){
		if((x>>i)&1)PORTA.OUTSET=1<<LED_BUILTIN;else PORTA.OUTCLR=1<<LED_BUILTIN;
		for(uint16_t j=0;j<2500;j++)WAIT;// 1/16秒
	}
}

uint16_t n2t(uint8_t x){uint8_t a=2;while(x>=12){x-=12;a++;}return t0[x]>>a;}

void play(const uint8_t *s){
	uint8_t
	*p[MTRKS],*_p[MTRKS],// チャネルポインタ ループ用に二重保存
	x[MTRKS],_x,// 読んだ音符 再生中フラグ
	ntrks=0,// 有効トラック数
	l[MTRKS],// 音価
	v[MTRKS],// 音量
	env;// 減衰カウンタ
	uint16_t
	t[MTRKS]={0},_t[MTRKS],// 音高とその波形生成用カウンタ
	dt,_dt;// 最小音価とそのカウンタ

	dt=240*F_WAV/(*s>>3); // 最小音価 F_WAV/tps
	for(uint8_t *x=s+1;ntrks<MTRKS;){// テンポが遅いと最初が0になるので回避
		if(*x++){// 0 チャネル先頭
			if(*x)break;// 0,0 楽譜終端 離脱
			p[ntrks++]=x;// チャネルポインタ読取
		}
	}

	while(1){
		_x=1;/// 再生中フラグを立てる
		_dt=ntrks;// 最小音価カウンタをトラック数で初期化
		env=1;// 減衰カウンタを1で初期化
		FOR(ntrks){
			x[i]=1;// チャネルのフラグを立てる
			_p[i]=p[i]+3;// チャネルポインタ初期化
			l[i]=0;// 音価を0で初期化
		}

		while(_x){
			if(--_dt<ntrks){// 最小音価カウンタが終了に近づいたら
				if(x[_dt]&&!l[_dt]--){// 前の音符が存在かつ終了したら
					x[_dt]=*_p[_dt]++;// 読込
					v[_dt]=0xff;// 音量
					t[_dt]=(!(x[_dt]&0b11111))?0:n2t(x[_dt]&0b11111)>>(*(p[_dt]+2)>>6);// オクターブ3bit 音高4bit(12以上は休符)
					l[_dt]=s[1+(x[_dt]>>5)];// 音価3bit テーブル参照

					_t[_dt]=0;// 波形生成用カウンタ初期化
				}
				if(!_dt){
					_dt=dt;// 最小音価カウンタリセット
					_x=0;FOR(ntrks)_x|=x[i];// チャネル合計 終了判定
				}
			}

			TCA0.SINGLE.CMP2=_OUT;// 波形生成 詳しくはマクロ参照

			if(--env<ntrks){// 減衰
				if(1)v[env]-=(v[env]>>5);// 上位3bitがある間は1-1/2^5倍
				if(!env)env=245;// 25us*245毎
			}

			WAIT;
			if(BTN_DOWN){WAIT_BTN;break;}// PB0押下で離脱
		}
		if(!(s[1]&0b100)||_x)break;// ループでない又は再生途中なら離脱
	}
}


void main(){
	// TCA0 疑似DAC 可能な限り高速な方が良い 20MHz/(8bit=2**8)=78.125kHz
	TCA0.SINGLE.CTRLA=TCA_SINGLE_ENABLE_bm;// TCA有効
	TCA0.SINGLE.CTRLB=TCA_SINGLE_CMP2EN_bm|TCA_SINGLE_WGMODE_SINGLESLOPE_gc;// TCA0 wo2有効 単傾斜PWM
	TCA0.SINGLE.PER=0x0f;// TOP 8bit
	//TCA0.SINGLE.CMP2=0;// clear

	// TCB0 波形生成 これが解像度 可聴域上端の2倍弱あれば何とかなる 20MHz/500=40kHz
	TCB0.CTRLA=TCB_CLKSEL_CLKTCA_gc|TCB_ENABLE_bm;// TCAとクロック共有 TCB有効
	TCB0.CTRLB=TCB_CNTMODE_INT_gc;// 周期的割り込み動作
	TCB0.CCMP=F_CPU/F_WAV-1;// TOP

	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB,0);// 分周無効化 CPUも周辺機能も20MHz
	PORTA.DIRSET=0b1100;// 出力: PA3,2
	PORTA.PIN7CTRL=PORT_PULLUPEN_bm|PORT_ISC_LEVEL_gc;// PA7 プルアップ LOWで割り込み 
	
	while(1){
		blink(0b00110011);sleep();play(yobikomi);
	}
}