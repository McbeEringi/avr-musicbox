#define F_CPU 20000000
#define LED_BUILTIN 3
#define BTN_BUILTIN 7
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "seq.h"

void sleep(){
	sei();
	SLPCTRL.CTRLA=SLPCTRL_SMODE_PDOWN_gc|SLPCTRL_SEN_bm;// avr/sleep.hが仕事しないので
	sleep_cpu();
	SLPCTRL.CTRLA=0;
	cli();
}ISR(PORTA_PORT_vect){}

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

	CLKCTRL.MCLKCTRLB=0;// 分周無効化 CPUも周辺機能も20MHz
	PORTA.DIRSET=0b1100;// 出力: PA3,2
	PORTA.PIN7CTRL=PORT_PULLUPEN_bm|PORT_ISC_RISING_gc;// PA7 プルアップ 離したら割り込み
	while(1){

	}
}