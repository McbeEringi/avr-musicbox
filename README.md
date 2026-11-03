# avr-musicbox


## seq format
```txt
header cmd cmd...
```

### header
```c
struct Header{
	uint8_t ntrks;
	uint16_t[ntrks] offset;
}
```

### cmd
```txt
NNNNOOLL: play
	NNNN: note number 0~11
	OO: octave
	LL: length index

110000LL: rest
	LL: length index

110001XX
11001XXX
1101XXXX
111XXXXX
	
```

- tps 11~bit
- octave 2bit
- length 5~bit x2bit
- volume
- decay
- timbre
	- FM series 2op
		- mod index 0(sin)~7
	- pulse
		- 1/2 1/4 1/8
	- saw
	- xor noise

