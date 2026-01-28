({
	title:'sh3',
	tpm:190*32/4,
	loop:false,
	notes:`
		x0010 >
		4bAFDC<8bb>4DFAbAFD
		>C<aF8edd>4CdCdC<aF
		>3r28e,

		x0100
		4r8FF4r8F 4r8FF4r8F
		4r8aa4r8a 4r8aa4r8a
		x0010>2r31c,
		x0100
		8r>Drr rD4C<brb
		8r>drr rF4edrd
		x0010 1g31a,

		x1000>>32bb>dd 32f
	`//.replace(/\/\/(.*)$/gm,(_,x)=>x.replace(/[a-gA-G]/g,'r'))
})

