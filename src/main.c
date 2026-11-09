#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "seq.h"
#include "depmel/sf.h"
#include "depmel/sh.h"
#include "depmel/sw.h"
#include "depmel/sakurai.h"


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

const uint16_t dds_base[]={// C9 ~ B9
	// [...Array(12)].map((_,i)=>Math.round(65536/(20000/(440*(2**((i-9)/12+5))))))
  27433, 29065, 30793,
  32624, 34564, 36619,
  38797, 41104, 43548,
  46137, 48881, 51787
};


#define POLY_MAX 4

#define BTN_DOWN ~VPORTB.IN&(1<<3)
void wait(){
	while(!(TCB0.INTFLAGS&TCB_CAPT_bm))
		;
	TCB0.INTFLAGS=1;
}
void wait_btn(){while(BTN_DOWN)FOR(255)wait();}// 0.05*255=12.75ms

static void sleep(){
			PORTA.OUTCLR=0b1000000;
	uint8_t d=VPORTA.DIR;VPORTA.DIR=0b1000000;sei();SLPCTRL.CTRLA=SLPCTRL_SMODE_PDOWN_gc|SLPCTRL_SEN_bm;sleep_cpu();cli();
			PORTA.OUTSET=0b1000000;
	wait_btn();VPORTA.DIR=d;}// avr/sleep.hが仕事しないので手動設定
ISR(PORTB_PORT_vect){PORTB.INTFLAGS=PORT_INT3_bm;}// リセット必須

static void blink(uint8_t x){FOR(8){if((x>>i)&1)PORTA.OUTSET=0b10000000;else PORTA.OUTCLR=0b10000000;for(uint16_t j=0;j<1250;j++)wait();}}

void play(const uint8_t *s){
	static const uint8_t
	*p[POLY_MAX],*_p[POLY_MAX];// チャネルポインタ ループ用に二重保存
	static uint8_t
	t[POLY_MAX<<1]={},_t[POLY_MAX],// 音価
	cfg[POLY_MAX]={},vol[POLY_MAX],
	poly,
	env;
	int8_t out_l,out_r;
	uint16_t
	h=(*s++<<8)|(*s++),// ヘッダ
	dds_step[POLY_MAX],theta[POLY_MAX],phi[POLY_MAX],
	lfsr[POLY_MAX],
	dt=12e5/(h>>5),_dt;// 最小音価 20000*60/TPM

	poly=0;
	while(poly<POLY_MAX){if(*s++==0){if(*s==0)break;p[poly++]=s;}}// チャネル数&ポインタ読取


	while(1){
		_dt=poly;env=1;FOR(poly){_p[i]=p[i];_t[i]=0;lfsr[i]=0xace1;}// 初期化
		while(1){
			if(--_dt<poly){
				if(*_p[_dt]&&!_t[_dt]--){
					while(!(*_p[_dt]&0x80)){
						if(*_p[_dt]>>6==1)t[(_dt<<1)|((*_p[_dt]>>5)&1)]=*_p[_dt]&0x1f;// 音価メモリ変更
						else if(*_p[_dt]>>5==1)cfg[_dt]=*_p[_dt]&0x1f;// 設定項目変更
						else if(*_p[_dt]==1)goto dc;// 終了フラグ
						_p[_dt]++;
					}
					_t[_dt]=t[(_dt<<1)|((*_p[_dt]>>6)&1)];// 音価1bit(5bit)
					dds_step[_dt]=(*_p[_dt]&0xf)>11?0:dds_base[*_p[_dt]&0xf]>>(((cfg[_dt]>>3)&1?8:5)-((*_p[_dt]>>4)&3));
					theta[_dt]=0;phi[_dt]=0;
					vol[_dt]=0xff>>((cfg[_dt]>>2)&1);
					_p[_dt]++;
				}
				if(!_dt)_dt=dt;
			}
			out_l=0;
			out_r=0;
			FOR(poly){// synthesis
				uint16_t prev=theta[i];
				theta[i]+=dds_step[i];
				phi[i]+=dds_step[i]*(((cfg[i]>>1)&1)?3:1);

				int8_t out;
				// if(i==3){
				// 	if(theta[i]<prev)
				// 		lfsr[i]=(lfsr[i]>>1)|(((lfsr[i]>>0)^(lfsr[i]>>2)^(lfsr[i]>>3)^(lfsr[i]>>5))<<15);
				// 	out=(lfsr[i]&0x8000?127:-127)*vol[i]/256/2;
				// }
				// else
				{
					out=((
						(cfg[i]>>3)&1?
						// (int16_t)(theta[i]>>8)-128:
						theta[i]<0x4000?127:-127:
						sin_table[(theta[i]+sin_table[phi[i]>>10]*(cfg[i]&1?41:(vol[i]>>1)+41))>>10]
					)*vol[i]/256)/2;
				}
				if(i<(poly>>1))out_r+=out;
				else out_l+=out;
			}
			if(poly==1)out_r=out_l;
			TCA0.SINGLE.CMP0BUF=out_r+128;
			TCA0.SINGLE.CMP1BUF=out_l+128;
			if(--env<poly){if(!(cfg[env]&1))vol[env]-=(vol[env]>>4);if(!env)env=255;}// envelope : every 0.05*255=12.75ms
			if(BTN_DOWN)goto fin;// ボタン離脱
			wait();
		}
		dc:if(!(h&1))break;// Da Capo
	}
	fin:TCA0.SINGLE.CMP0BUF=128;
	TCA0.SINGLE.CMP1BUF=128;
	wait_btn();
}


int main(){
	// TCA0 as Pseudo DAC 20MHz/(8bit=2**8)=78.125kHz
	TCA0.SINGLE.PER=0xff;
	TCA0.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1_gc|TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.CTRLB=TCA_SINGLE_CMP1EN_bm|TCA_SINGLE_CMP0EN_bm|TCA_SINGLE_WGMODE_SINGLESLOPE_gc;

	// TCB0 as Timer 20kHz
	#ifdef OSCCAL
		// error(OSCxERRxV) <<< error(int op)
		// Do not expect any dramatic improvement.
		// Cosumes worthless 310B!!
		TCB0.CCMP=F_CPU/1024*(1024+(int8_t)SIGROW.OSC20ERR5V)/20e3-1;
	#else
		TCB0.CCMP=F_CPU/20e3-1;
	#endif
	TCB0.CTRLA=TCB_CLKSEL_CLKDIV1_gc|TCB_ENABLE_bm;
	// TCB0.CTRLB=TCB_CNTMODE_INT_gc;

	PORTA.DIRSET=0b11000000;
	PORTA.OUTSET=0b01000000;
	PORTB.DIRSET=0b11;
	PORTB.PIN3CTRL=PORT_PULLUPEN_bm|PORT_ISC_LEVEL_gc;

	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB,0);

	while(1){
		blink(0b00110011);sleep();play(kokyo_no_sora);
		blink(0b00110011);sleep();play(toryanse);
		blink(0b00110011);sleep();play(famima);
		blink(0b00110011);sleep();play(kakko);
		blink(0b00110011);sleep();play(ofuro);
		blink(0b00110011);sleep();play(jingle);play(yobikomi);
		blink(0b00110011);sleep();play(jingle_bell);
		blink(0b00110011);sleep();play(petrouchka);
		blink(0b00110011);sleep();play(nyan);
		blink(0b00110011);sleep();play(small_world);
		blink(0b00110011);sleep();play(kewpie);
		blink(0b00110011);sleep();play(dw3battle);play(dw3level);
		blink(0b00110011);sleep();play(allback);
		blink(0b00110011);sleep();play(gakuseigai_no_kissatenn);
		blink(0b00110011);sleep();play(waltzing_in_the_rain);
		blink(0b00110011);sleep();play(surfboard);

		blink(0b00110011);sleep();play(sf_3);
		blink(0b00110011);sleep();play(haru_new);

		blink(0b00110011);sleep();play(sh1);
		blink(0b00110011);sleep();play(sh2);
		blink(0b00110011);sleep();play(sh3);
		blink(0b00110011);sleep();play(sh4);
		blink(0b00110011);sleep();play(sh5);
		blink(0b00110011);sleep();play(sh6);
		blink(0b00110011);sleep();play(sh7);
		blink(0b00110011);sleep();play(sh8);
		blink(0b00110011);sleep();play(sh9);

		blink(0b00110011);sleep();play(gota_del_vient);
		blink(0b00110011);sleep();play(verde_rayo);
		blink(0b00110011);sleep();play(water_crown);
		blink(0b00110011);sleep();play(ciello_estrellado);
		blink(0b00110011);sleep();play(moon_stone);
		blink(0b00110011);sleep();play(rakuraku_tetudou_ryokou);
		blink(0b00110011);sleep();play(mori_no_yousei);
		blink(0b00110011);sleep();play(asatuyu);

		blink(0b00110011);sleep();play(azamino);
		blink(0b00110011);sleep();play(holiday);
		blink(0b00110011);sleep();play(springbox);
		blink(0b00110011);sleep();play(sennro_no_kanata);
		blink(0b00110011);sleep();play(mellow_time);
		blink(0b00110011);sleep();play(cappuccino);
		blink(0b00110011);sleep();play(ogawa_no_seseragi);
	}

}
