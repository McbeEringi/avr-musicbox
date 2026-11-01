#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FOR(X) for(uint8_t i=0;i<X;i++)


const int8_t sin_table[]={
	// [...Array(64)].map((_,i,{length:l})=>Math.round(Math.sin(i/l*Math.PI*2)*127))
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
// const uint8_t yobikomi[]={// 324bytes
// 	65,129,
// 	0,35,64,153,156,99,217,155,156,153,156,150,156,97,217,220,153,156,99,217,155,156,153,156,150,156,97,217,220,146,156,146,156,146,156,148,156,100,214,156,146,156,214,156,153,156,103,217,146,156,146,156,146,156,148,156,214,146,156,146,156,146,156,148,156,214,148,156,148,156,148,156,146,156,97,212,220,214,220,217,220,215,220,214,220,212,220,
// 	0,42,65,172,64,169,98,236,169,236,169,169,97,236,169,98,236,169,236,169,236,169,169,97,236,169,98,236,171,236,171,236,171,171,97,236,171,98,236,171,236,171,236,171,171,97,236,171,98,236,171,236,171,236,171,171,97,236,171,98,236,171,236,171,236,171,171,97,236,171,98,236,169,236,169,236,169,169,97,236,169,98,236,169,236,169,236,169,169,65,172,169,
// 	0,42,65,172,64,166,98,236,166,236,166,166,97,236,166,98,236,166,236,166,236,166,166,97,236,166,98,236,166,236,166,236,166,166,97,236,166,98,236,166,236,166,236,166,166,97,236,166,98,236,167,236,167,236,167,167,97,236,167,98,236,167,236,167,236,167,167,97,236,167,98,236,164,236,164,236,164,164,97,236,164,98,236,164,236,164,236,164,164,65,172,164,
// 	0,43,67,162,153,162,153,162,153,98,226,96,217,97,226,225,155,150,155,150,155,150,98,219,96,214,97,219,217,151,146,151,162,151,146,215,210,215,219,153,148,153,148,153,148,225,219,153,1,
// 	0,0
// };


#define NUM_POLY 7
uint8_t poly=1,mn=0;
uint16_t theta[NUM_POLY]={0};
uint16_t phi[NUM_POLY]={0};

uint8_t test[]={0,4,7,11};



// #define MTRKS NUM_POLY
// volatile static const uint8_t
// 	*p[MTRKS],*_p[MTRKS];// チャネルポインタ ループ用に二重保存
// static uint8_t
// 	t[MTRKS<<1]={},_t[MTRKS],// 音価
// 	cfg[MTRKS]={},_v[MTRKS],// 設定項目 音量
// 	ntrks,// 有効トラック数
// 	out;
// uint16_t
// 	h=(*s++<<8)|(*s++),// ヘッダ
// 	n[MTRKS]={},_n[MTRKS],// 音高
// 	env,// 減衰カウンタ
// 	dt=24e5/(h>>5),_dt;// 最小音価 40000*60/TPM

// void play(const uint8_t *s){
// 	ntrks=0;

// 	while(ntrks<NUM_POLY){if(*s++==0){if(*s==0)break;p[ntrks++]=s;}}// チャネル数&ポインタ読取
// }

// void _play_init(){
// 	_dt=ntrks;env=1;FOR(ntrks){_p[i]=p[i];_t[i]=0;}// 初期化
// }

ISR(TCB0_INT_vect){
	// if(--_dt<ntrks){
	// 	if(*_p[_dt]&&!_t[_dt]--){
	// 		while(!(*_p[_dt]&0x80)){
	// 			if(*_p[_dt]>>6==1)t[(_dt<<1)|((*_p[_dt]>>5)&1)]=*_p[_dt]&0x1f;// 音価メモリ変更
	// 			else if(*_p[_dt]>>5==1)cfg[_dt]=*_p[_dt]&0x1f;// 設定項目変更
	// 			else if(*_p[_dt]==1)goto dc;// 終了フラグ
	// 			_p[_dt]++;
	// 		}
	// 		_t[_dt]=t[(_dt<<1)|((*_p[_dt]>>6)&1)];// 音価1bit(5bit)
	// 		n[_dt]=(*_p[_dt]&0xf)>11?0:sin_table[*_p[_dt]&0xf]<<(7-(((*_p[_dt]>>4)&3)+((cfg[_dt]>>3)&1?1:4)));// オクターブ2+1bit 音高4bit
	// 		_n[_dt]=0;// 波形カウンタリセット
	// 		_v[_dt]=0xff>>((cfg[_dt]>>2)&1);// 音量 
	// 		_p[_dt]++;
	// 	}
	// 	if(!_dt)_dt=dt;
	// }

	int8_t out_l=0,out_r=0;

	FOR(poly){
		uint8_t
			note=test[i%4],
			oct=3-i/4;
		theta[i]+=d_theta[note]>>oct;
		phi[i]+=(d_theta[note]>>oct)*mn;
		// out+=theta[i]>>15?63:0; // sq wave
		if(i&1)
			out_l+=sin_table[(
				theta[i]+(sin_table[phi[i]>>10]*16)
			)>>10]/8;
		else
			out_r+=sin_table[(
				theta[i]+(sin_table[phi[i]>>10]*16)
			)>>10]/8;
	}
	TCA0.SINGLE.CMP0BUF=out_r+128;
	TCA0.SINGLE.CMP1BUF=out_l+128;

	// if(--env<ntrks){if(!(cfg[env]&1))_v[env]-=(_v[env]>>4);if(!env)env=384;}// 減衰 9.6ms毎

	TCB0.INTFLAGS=TCB_CAPT_bm;
}
ISR(PORTB_PORT_vect){
	mn=0;
	PORTA.OUTCLR=0x80;
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
		++poly;
		_delay_ms(50);
		if(NUM_POLY-1<poly){
			PORTA.OUTTGL=0x80;
			poly=1;
			mn++;
		}
	}
}
