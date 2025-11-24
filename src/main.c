#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// #define WO_ALT
#define WO_CH 0
#include "tca0.h"

#define FOR(X) for(uint8_t i=0;i<X;i++)
void wait(){while(!(TCB0.INTFLAGS&TCB_CAPT_bm));TCB0.INTFLAGS=1;}
void wait_btn(){while(BTN_DOWN)FOR(255)wait();}

const uint16_t n0[]={2446,2309,2179,2057,1942,1833,1730,1633,1541,1455,1373,1296};

static void sleep(){uint8_t d=VPORTA.DIR;VPORTA.DIR=0;sei();SLPCTRL.CTRLA=SLPCTRL_SMODE_PDOWN_gc|SLPCTRL_SEN_bm;sleep_cpu();cli();wait_btn();VPORTA.DIR=d;}
ISR(PORTA_PORT_vect){PORTA.INTFLAGS=PORT_INT7_bm;}


void main(){
	// TCA0 疑似DAC 可能な限り高速な方が良い 20MHz/(8bit=2**8)=78.125kHz
	TCA0.SINGLE.CTRLA=TCA_SINGLE_ENABLE_bm;// 分周無し TCA有効
	TCA0.SINGLE.CTRLB=WO_CMPnEN|TCA_SINGLE_WGMODE_SINGLESLOPE_gc;// TCA0 wo2有効 単傾斜PWM
	TCA0.SINGLE.PER=0xff;// TOP 8bit

	// TCB0 波形生成 これが解像度 可聴域上端の2倍弱あれば何とかなる 20MHz/500=40kHz
	TCB0.CTRLA=TCB_ENABLE_bm;// 分周無し TCB有効
	TCB0.CCMP=F_CPU/4e4-1;// TOP

	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB,0);

	WO_PORT.DIRSET=(1<<WO_PIN);

}
