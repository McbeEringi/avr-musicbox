# avr-musicbox

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

