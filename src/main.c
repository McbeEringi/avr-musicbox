#include <avr/io.h>


#define SIN_TABLE_LEN 15
const uint8_t sin_table[]={// [15]
	25,50,74,98,120,142,162,180,197,212,225,236,244,250,254
};

const uint16_t d_theta[]={// C7 ~ B7
	
}

#define NUM_POLY 7
uint16_t theta[NUM_POLY]={0};




void main(){
	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB,0);
}
