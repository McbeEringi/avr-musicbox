#ifndef SEQ_H
#define SEQ_H
/*
sequence
	header
		TTTTTL__
			tickPerSec = T;// BPM:120,minNote:16=tps:8
			loop? = L
	track...
		WWWWWWWW
			wave form = W ( 2bit*4 )
		DDOOE_SS
		SSSSSSSS
			envelope? = E
			note data size(byte) = S
		LLLNNNNN... : note data
			length = [1,2,3,4,6,8,12,16][L]<<D
			note = [ 1(F#3)~16(A4)~31(C6) ][N]+O*12
	0 : end of seq
*/
static const uint8_t yobikomi[]={
};

#endif


