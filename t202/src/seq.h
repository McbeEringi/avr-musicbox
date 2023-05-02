#ifndef SEQ_H
#define SEQ_H
/*
sequence
	header

	track...
		0: track start
		LLLNNNNN...: note data
			L=
			N=1(F#3)~16(A4)~31(C6), 0(Rest)
	0,0: end of seq
*/
static const uint8_t yobikomi[]={
	255,
	0,
	0,
	0,
	0,
	0,0
};

#endif