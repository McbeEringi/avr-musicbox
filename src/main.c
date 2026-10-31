#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FOR(X) for(uint8_t i=0;i<X;i++)


const int8_t sin_table[]={
	// 64程度のテーブルでは最適化したとしても1/4波形よりも全部展開したほうが小さいし早い
	// [...Array(64)].map((_,i,{length:l})=>Math.round(Math.sin(i/l*Math.PI*2)*127))
	// 128, 140, 152, 165, 176, 188, 198, 208, 218, 226, 234,
 //  240, 245, 250, 253, 254, 255, 254, 253, 250, 245, 240,
 //  234, 226, 218, 208, 198, 188, 176, 165, 152, 140, 128,
 //  115, 103,  90,  79,  67,  57,  47,  37,  29,  21,  15,
 //   10,   5,   2,   1,   0,   1,   2,   5,  10,  15,  21,
 //   29,  37,  47,  57,  67,  79,  90, 103, 115
 0,   12,   25,   37,   49,   60,   71,   81,   90,
    98,  106,  112,  117,  122,  125,  126,  127,  126,
   125,  122,  117,  112,  106,   98,   90,   81,   71,
    60,   49,   37,   25,   12,    0,  -12,  -25,  -37,
   -49,  -60,  -71,  -81,  -90,  -98, -106, -112, -117,
  -122, -125, -126, -127, -126, -125, -122, -117, -112,
  -106,  -98,  -90,  -81,  -71,  -60,  -49,  -37,  -25,
   -12
};

const uint16_t d_theta[]={// C7 ~ B7
	// [...Array(12)].map((_,i)=>Math.round(65536/(20000/(440*(2**((i-9)/12+4))))))
  6858,  7266,  7698,
   8156,  8641,  9155,
   9699, 10276, 10887,
  11534, 12220, 12947
};

#define NUM_POLY 8
uint8_t poly=1;
uint16_t theta[NUM_POLY]={0};
uint16_t phi[NUM_POLY]={0};

uint8_t test[]={0,4,7,11};


ISR(TCB0_INT_vect){
	int8_t out=0,out_=0;

	FOR(poly){
		uint8_t
			note=test[i%4],
			oct=3-i/4;
		theta[i]+=d_theta[note]>>oct;
		phi[i]+=(d_theta[note]>>oct)*5;
		// out+=theta[i]>>15?63:0; // sq wave
		if(i&1)
			out+=sin_table[(
				theta[i]+(sin_table[phi[i]>>10]<<4)
			)>>10]/8;
		else
			out_+=sin_table[(
				theta[i]+(sin_table[phi[i]>>10]<<4)
			)>>10]/8;
	}
	TCA0.SINGLE.CMP0BUF=out+128;
	TCA0.SINGLE.CMP1BUF=out_+128;

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
		_delay_ms(250);
		if(NUM_POLY-1<++poly){
			_delay_ms(1000);
			poly=1;
		}
	}
}
