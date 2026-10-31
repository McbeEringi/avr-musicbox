#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>


uint8_t onkai=0;
uint8_t onkai_=0;
const uint8_t sin_table[]={// [16]
	// [...Array(16)].map((_,i,{length:l})=>Math.round(Math.sin(i/l*Math.PI*.5)*255))
	0,25,50,74,98,120,142,162,180,197,212,225,236,244,250,254,255
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
	uint8_t out;
	switch(theta[0]>>14){
		case 0b00:{out=0x80+(sin_table[((theta[0]>>10)&0xf)]>>1);break;}
		case 0b01:{out=0x80+(sin_table[0x10-((theta[0]>>10)&0xf)]>>1);break;}
		case 0b10:{out=0x80-(sin_table[((theta[0]>>10)&0xf)]>>1);break;}
		case 0b11:{out=0x80-(sin_table[0x10-((theta[0]>>10)&0xf)]>>1);break;}
	}
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
