#ifndef TCA0_H
#define TCA0_H

#include "modern_avr.h"

// #define WO_ALT
// #define WO_CH 0 // 0,1,2


#if (WO_CH==0)
	#define WO_CMPnEN TCA_SINGLE_CMP0EN_bm
	#define WO_CMPnBUF TCA0.SINGLE.CMP0BUF
#elif (WO_CH==1)
	#define WO_CMPnEN TCA_SINGLE_CMP1EN_bm
	#define WO_CMPnBUF TCA0.SINGLE.CMP1BUF
#elif (WO_CH==2)
	#define WO_CMPnEN TCA_SINGLE_CMP2EN_bm
	#define WO_CMPnBUF TCA0.SINGLE.CMP2BUF
#endif

#if (
	defined(TINYAVR_8PIN)
)
	#define WO_PORT PORTA
	#if (WO_CH==0)
		#ifdef WO_ALT
			#define WO_PIN 7
		#else
			#define WO_PIN 0
		#endif
	#elif ((WO_CH==1)||(WO_CH==2))
		#ifdef WO_ALT
			#error "No ALT pin"
		#else
			#define WO_PIN WO_CH
		#endif
	#else
		#error "WO_CH shoud in 1 ~ 2"
	#endif
#endif

#if (
	defined(TINYAVR_14PIN)||
	defined(TINYAVR_20PIN)||
	defined(TINYAVR_24PIN)
)
	#define WO_PORT PORTB
	#if ((WO_CH==0)||(WO_CH==1)||(WO_CH==2))
		#ifdef WO_ALT
			#define WO_PIN (WO_ALT+3)
		#else
			#define WO_PIN WO_ALT
		#endif
	#else
		#error "WO_CH shoud in 1 ~ 2"
	#endif
#endif

#if (
	defined(MEGAAVR_32PIN)||
	defined(MEGAAVR_48PIN)
)
	#if (!defined(WO_ALT)||WO_ALT==0)
		#define WO_PORT PORTA
	#elif (WO_ALT==1)
		#define WO_PORT PORTB
	#elif (WO_ALT==2)
		#define WO_PORT PORTC
	#elif (WO_ALT==3)
		#define WO_PORT PORTD
	#elif (WO_ALT==4)
		#define WO_PORT PORTE
	#elif (WO_ALT==5)
		#define WO_PORT PORTF
	#else
		#error "WO_ALT should in 0 ~ 5"
	#endif
	#if ((WO_CH==0)||(WO_CH==1)||(WO_CH==2))
		#define WO_PIN WO_ALT
	#else
		#error "WO_CH shoud in 1 ~ 2"
	#endif
#endif


#endif

// DATAMEM_SIZE
