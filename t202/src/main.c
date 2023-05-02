#define F_CPU 20000000
#define LED_BUILTIN 3
#define BTN_BUILTIN 7
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "seq.h"

#define BTN_DOWN ~VPORTA.IN&(1<<7)
#define WAIT_5 for(uint8_t i=0;i<200;i++)WAIT// 5ms
#define WAIT do{while(!(TCB0.INTFLAGS&TCB_CAPT_bm));TCB0.INTFLAGS=TCB_CAPT_bm;}while(0)// TCB0待ち(25us) 解除

void sleep(){
	sei();SLPCTRL.CTRLA=SLPCTRL_SMODE_PDOWN_gc|SLPCTRL_SEN_bm;// avr/sleep.hが仕事しないので
	sleep_cpu();// ピン割り込みはBOTHEDGESかLEVELじゃなきゃ起きない
	SLPCTRL.CTRLA=0;cli();
	while(BTN_DOWN);WAIT_5;
}ISR(PORTA_PORT_vect){PORTA.INTFLAGS=PORT_INT7_bm;}

void blink(uint8_t x){// 下位bitから読み込み MSBの状態のまま離脱
	for(uint8_t i=0;i<8;i++){
		if((x>>i)&1)PORTA.OUTSET=1<<LED_BUILTIN;else PORTA.OUTCLR=1<<LED_BUILTIN;
		for(uint16_t j=0;j<2500;j++)WAIT;// 1/16秒
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
	TCB0.CCMP=499;// TOP

	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB,0);// 分周無効化 CPUも周辺機能も20MHz
	PORTA.DIRSET=0b1100;// 出力: PA3,2
	PORTA.PIN7CTRL=PORT_PULLUPEN_bm|PORT_ISC_LEVEL_gc;// PA7 プルアップ LOWで割り込み 
	while(1){
		blink(0b01001001);sleep();
	}
}