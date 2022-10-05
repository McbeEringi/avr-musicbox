#include "sheet.h"
#define _BV_PINB0 1
#define _BV_TOV0 2

void setup(){
	// DDRB PORTB:state, 00:IN_HI-Z, 01:IN_P-UP, 10:OUT_L, 11:OUT_H

	// 0: INPUT_PULLUP
	// 1: HIGH
	// 2: LOW
	// --ZZZLHP
	DDRB  =0b00000110;// [ポートB方向レジスタ] OUT 1 2
	PORTB =0b00000011;// [ポートB出力レジスタ] PU||H 0 1

	TIMSK =0b00000000;// [タイマ―割り込み許可レジスタ] - OCIE1A OCIE1B OCIE0A OCIE0B TOIE1 TOIE0 : 無効

	TCCR0A=0b00000011;
	TCCR0B=0b00001010;// [タイマー0制御レジスタ] COM0A1 COM0A0 COM0B1 COM0B0 - - WGM01 WGM00 : FOC0A FOC0B - - WGM02 CS02 CS01 CS00 : 高速PWM 1/8分周
	OCR0A =F_CPU/25e4;// [タイマ0レジスタA] 基準クロック 31.25kHz 32us

	TCCR1 =0b00000001;// [タイマー1制御レジスタ 1] CTC1 PWM1A COM1A1 COM1A0 CS13 CCS12 CS11 CS10 : 分周無し
	GTCCR =0b01010000;// [タイマー1制御レジスタ 2] TSM PWM1B COM1B1 COM1B0 FOC1B FOC1A PSR1 PSR0 : PWM1B PB3有効
	PLLCSR=0b00000111;// [PLL制御状態レジスタ] LSM - - - - PCKE PLLE PLOCK : 通常動作, PCK PLL Plock許可 64MHz動作
	OCR1B=0;OCR1C=255;// [タイマ1レジスタBC] 250kHz動作

	TCNT1=0;// [タイマー1] リセット
}
void loop(){
	while( (PINB&_BV_PINB0));// PB0解放
	while(!(PINB&_BV_PINB0));// PB0押下
	core(sheet);// 再生
}

void core(){
	DDRB|=0b00011000;// 3,4出力設定
	do{

		while(!(TIFR&_BV_TOV0));TIFR|=_BV_TOV0;// タイマー0待ち(32us) 強制解除
		if(!(PINB&_BV_PINB0))break;// PB0押下で離脱
	}while(0);
	DDRB&=~0b00011000;// 3,4出力解除
}

