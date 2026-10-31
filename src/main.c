#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>


uint8_t onkai=0;
uint8_t onkai_=0;

const uint8_t sin_table[]={
	// 64程度のテーブルでは最適化したとしても1/4波形よりも全部展開したほうが小さいし早い
	// [...Array(64)].map((_,i,{length:l})=>Math.round((Math.sin(i/l*Math.PI*2)*.5+.5)*255))
	128, 140, 152, 165, 176, 188, 198, 208, 218, 226, 234,
  240, 245, 250, 253, 254, 255, 254, 253, 250, 245, 240,
  234, 226, 218, 208, 198, 188, 176, 165, 152, 140, 128,
  115, 103,  90,  79,  67,  57,  47,  37,  29,  21,  15,
   10,   5,   2,   1,   0,   1,   2,   5,  10,  15,  21,
   29,  37,  47,  57,  67,  79,  90, 103, 115
};

const uint16_t d_theta[]={// C7 ~ B7
	// [...Array(12)].map((_,i)=>Math.round(65536/(20000/(440*(2**((i-9)/12+4))))))
	13717, 14532, 15396,
  16312, 17282, 18310,
  19398, 20552, 21774,
  23069, 24440, 25894
};

#define NUM_POLY 7
uint16_t theta[NUM_POLY]={0};


ISR(TCB0_INT_vect){
	theta[0]+=d_theta[onkai]>>onkai_;

	uint8_t out=sin_table[theta[0]>>10];
	TCA0.SINGLE.CMP0BUF=out;
	TCA0.SINGLE.CMP1BUF=out;

	TCB0.INTFLAGS=TCB_CAPT_bm;
}
ISR(PORTB_PORT_vect){
	PORTA.OUTTGL=0x80;
	PORTB.INTFLAGS=PORT_INT3_bm;
}


void main(){
	// TCA0 as Pseudo DAC 20MHz/(8bit=2**8)=78.125kHz
	TCA0.SINGLE.PER=0xff;
	TCA0.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1_gc|TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.CTRLB=TCA_SINGLE_CMP1EN_bm|TCA_SINGLE_CMP0EN_bm|TCA_SINGLE_WGMODE_SINGLESLOPE_gc;

	// TCB0 as Timer 20kHz
	TCB0.CCMP=F_CPU/20e3-1;
	TCB0.CTRLA=TCB_CLKSEL_CLKDIV1_gc|TCB_ENABLE_bm;
	// TCB0.CTRLB=TCB_CNTMODE_INT_gc;
	TCB0.INTCTRL=TCB_CAPT_bm;

	PORTA.DIRSET=0b11000000;
	PORTA.OUTSET=0b11000000;
	PORTB.DIRSET=0b11;
	PORTB.PIN3CTRL=PORT_PULLUPEN_bm|PORT_ISC_LEVEL_gc;

	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB,0);
	sei();
	while(1){
		_delay_ms(50);
		onkai=rand()&0xf;
		while(11<onkai)onkai--;
		onkai_=rand()&3;
	}
}
