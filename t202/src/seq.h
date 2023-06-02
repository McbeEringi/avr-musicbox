#ifndef SEQ_H
#define SEQ_H
/*
header 2byte
	BBBBBBBB
	BBBBBL__
		BPM*minNote 13bit
		loop 1bit
track
	0 1byte
	commands 1byte
		1LOONNNN
			note=NNNN+O*12;
			length=tick[L];
			play();

		01LTTTTT
			tick[L]=TTTTT;

		001__VME
			halfVolume=V;
			octPulseMode=M;
			envelope=E;

		00011111~00000010 reserved

		00000001
			break;
0 0 2byte
*/

const uint8_t famima[]={
	20,4,
	0,34,64,166,162,153,162,164,98,233,164,166,164,153,67,162,
	0,65,156,150,98,225,96,212,153,153,67,150,1,
	0,0
};
#endif


