/*
ピン

PA2 WAVE
PA3 LED
PA7 SW
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "seq.h"

#define MTRKS 4
#define BTN_DOWN ~VPORTA.IN&(1<<7)
#define FOR(X) for(uint8_t i=0;i<X;i++)
void wait(){while(!(TCB0.INTFLAGS&TCB_CAPT_bm));TCB0.INTFLAGS=1;}// TCB0待ち(25us) 1書いて解除
void wait_btn(){while(BTN_DOWN)FOR(255)wait();}// 0.025*255=6.375ms

const uint16_t n0[]={2446,2309,2179,2057,1942,1833,1730,1633,1541,1455,1373,1296};// C0~B0

static void sleep(){uint8_t d=VPORTA.DIR;VPORTA.DIR=0;sei();SLPCTRL.CTRLA=SLPCTRL_SMODE_PDOWN_gc|SLPCTRL_SEN_bm;sleep_cpu();cli();wait_btn();VPORTA.DIR=d;}// avr/sleep.hが仕事しないので手動設定
ISR(PORTA_PORT_vect){PORTA.INTFLAGS=PORT_INT7_bm;}// リセット必須

static void blink(uint8_t x){FOR(8){if((x>>i)&1)PORTA.OUTSET=0b1000;else PORTA.OUTCLR=0b1000;for(uint16_t j=0;j<2500;j++)wait();}}// 下位bitから読み込み MSBの状態のまま離脱 1/16秒*8

static void play(const uint8_t *s){
	static const uint8_t
	*p[MTRKS],*_p[MTRKS];// チャネルポインタ ループ用に二重保存
	static uint8_t
	t[MTRKS<<1]={},_t[MTRKS],// 音価
	cfg[MTRKS]={},_v[MTRKS],// 設定項目 音量
	ntrks,// 有効トラック数
	out;
	uint16_t
	h=(*s++<<8)|(*s++),// ヘッダ
	n[MTRKS]={},_n[MTRKS],// 音高
	env,// 減衰カウンタ
	dt=24e5/(h>>5),_dt;// 最小音価 40000*60/TPM

	ntrks=0;
	while(ntrks<MTRKS){if(*s++==0){if(*s==0)break;p[ntrks++]=s;}}// チャネル数&ポインタ読取
	while(1){
		_dt=ntrks;env=1;FOR(ntrks){_p[i]=p[i];_t[i]=0;}// 初期化
		while(1){
			if(--_dt<ntrks){
				if(*_p[_dt]&&!_t[_dt]--){
					while(!(*_p[_dt]&0x80)){
						if(*_p[_dt]>>6==1)t[(_dt<<1)|((*_p[_dt]>>5)&1)]=*_p[_dt]&0x1f;// 音価メモリ変更
						else if(*_p[_dt]>>5==1)cfg[_dt]=*_p[_dt]&0x1f;// 設定項目変更
						else if(*_p[_dt]==1)goto dc;// 終了フラグ
						_p[_dt]++;
					}
					_t[_dt]=t[(_dt<<1)|((*_p[_dt]>>6)&1)];// 音価1bit(5bit)
					n[_dt]=(*_p[_dt]&0xf)>11?0:n0[*_p[_dt]&0xf]>>(((*_p[_dt]>>4)&3)+((cfg[_dt]>>3)&1?1:4));// オクターブ2+1bit 音高4bit
					_n[_dt]=0;// 波形カウンタリセット
					_v[_dt]=0xff>>((cfg[_dt]>>2)&1);// 音量 
					_p[_dt]++;
				}
				if(!_dt)_dt=dt;
			}
			out=0;
			FOR(ntrks){// 矩形波合成 1/4
				if(++_n[i]==n[i])_n[i]=0;
				if(_n[i]<(n[i]>>(((cfg[i]>>1)&1)+1)))out+=_v[i]>>2;
			}
			TCA0.SINGLE.CMP2BUF=out;
			if(--env<ntrks){if(!(cfg[env]&1))_v[env]-=(_v[env]>>4);if(!env)env=384;}// 減衰 9.6ms毎
			if(BTN_DOWN)goto fin;// ボタン離脱
			wait();
		}
		dc:if(!(h&1))break;// ループ
	}
	fin:TCA0.SINGLE.CMP2BUF=0;
	wait_btn();
}

void main(){
	// TCA0 疑似DAC 可能な限り高速な方が良い 20MHz/(8bit=2**8)=78.125kHz
	TCA0.SINGLE.CTRLA=TCA_SINGLE_ENABLE_bm;// 分周無し TCA有効
	TCA0.SINGLE.CTRLB=TCA_SINGLE_CMP2EN_bm|TCA_SINGLE_WGMODE_SINGLESLOPE_gc;// TCA0 wo2有効 単傾斜PWM
	TCA0.SINGLE.PER=0xff;// TOP 8bit

	// TCB0 波形生成 これが解像度 可聴域上端の2倍弱あれば何とかなる 20MHz/500=40kHz
	TCB0.CTRLA=TCB_ENABLE_bm;// 分周無し TCB有効
	// TCB0.CTRLB=TCB_CNTMODE_INT_gc;// 周期的割り込み動作
	TCB0.CCMP=F_CPU/4e4-1;// TOP

	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB,0);// 分周無効化 CPUも周辺機能も20MHz
	PORTA.DIRSET=0b1100;// 出力: PA3,2
	PORTA.PIN7CTRL=PORT_PULLUPEN_bm|PORT_ISC_LEVEL_gc;// PA7 プルアップ ピン割り込みはBOTHEDGESかLEVELじゃなきゃ起きない 

	while(1){
		blink(0b00110011);sleep();play(jb);
	}
}