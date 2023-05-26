#define F_CPU 20000000 // 念のため
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "seq.h"
#define MTRKS 4

#define WAIT_BTN while(BTN_DOWN)WAIT_5
#define BTN_DOWN ~VPORTA.IN&(1<<7)
#define WAIT_5 FOR(200)WAIT// 5ms
#define WAIT do{while(!(TCB0.INTFLAGS&TCB_CAPT_bm));TCB0.INTFLAGS=TCB_CAPT_bm;}while(0)// TCB0待ち(25us) 解除
#define FOR(X) for(uint8_t i=0;i<X;i++)

const uint16_t t0[]={2446,2309,2179,2057,1942,1833,1730,1633,1541,1455,1373,1296};// C0~B0

void sleep(){uint8_t d=VPORTA.DIR;VPORTA.DIR=0;sei();SLPCTRL.CTRLA=SLPCTRL_SMODE_PDOWN_gc|SLPCTRL_SEN_bm;sleep_cpu();cli();WAIT_BTN;VPORTA.DIR=d;}// avr/sleep.hが仕事しないので手動設定
ISR(PORTA_PORT_vect){PORTA.INTFLAGS=PORT_INT7_bm;}// ピン割り込みはBOTHEDGESかLEVELじゃなきゃ起きない リセット必須

void blink(uint8_t x){// 下位bitから読み込み MSBの状態のまま離脱
	FOR(8){
		if((x>>i)&1)PORTA.OUTSET=0b1000;else PORTA.OUTCLR=0b1000;
		for(uint16_t j=0;j<2500;j++)WAIT;// 1/16秒
	}
}

void play(){
	uint16_t t[3]={76,61,51},_t[3]={0,0,0};//C5,E5,G5
	for(uint16_t i=0;i<-1;i++){
		TCA0.SINGLE.CMP2=
		((_t[0]=(++_t[0]==t[0]?0:_t[0]))<(t[0]>>1)?255>>2:0)+
		((_t[1]=(++_t[1]==t[1]?0:_t[1]))<(t[1]>>1)?255>>2:0)+
		((_t[2]=(++_t[2]==t[2]?0:_t[2]))<(t[2]>>1)?255>>2:0)
		;
		WAIT;
	}
}


void main(){
	// TCA0 疑似DAC 可能な限り高速な方が良い 20MHz/(8bit=2**8)=78.125kHz
	TCA0.SINGLE.CTRLA=TCA_SINGLE_ENABLE_bm;// TCA有効
	TCA0.SINGLE.CTRLB=TCA_SINGLE_CMP2EN_bm|TCA_SINGLE_WGMODE_SINGLESLOPE_gc;// TCA0 wo2有効 単傾斜PWM
	TCA0.SINGLE.PER=0xff;//45454;// TOP 8bit
	//TCA0.SINGLE.CMP2=22727;// clear

	// TCB0 波形生成 これが解像度 可聴域上端の2倍弱あれば何とかなる 20MHz/500=40kHz
	TCB0.CTRLA=TCB_CLKSEL_CLKTCA_gc|TCB_ENABLE_bm;// TCAとクロック共有 TCB有効
	TCB0.CTRLB=TCB_CNTMODE_INT_gc;// 周期的割り込み動作
	TCB0.CCMP=499;// TOP

	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB,0);// 分周無効化 CPUも周辺機能も20MHz
	PORTA.DIRSET=0b1100;// 出力: PA3,2
	PORTA.PIN7CTRL=PORT_PULLUPEN_bm|PORT_ISC_LEVEL_gc;// PA7 プルアップ LOWで割り込み 
	
	while(1){
		blink(0b00110011);sleep();blink(0b01010101);play();//play(yobikomi);
	}
}