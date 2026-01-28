({
	title:'ciello_estrellado',
	tpm:108*32/4,
	loop:false,
	notes:`
		x0010
		32r
		4b>b<b>b<b>b<b>b
		b>b<b>b<b>b<b>b<
		r<4b>a<b>
		rCb>20e,

		x0010 >
		32r2r4FFFFFFFF>
		FFFFFFFF
		r<dgd
		re>C18b,

		x1000 >
		4b>b<b>b<b>b<b>b<
		b>b<b>b<b>b<b>b<
		b>b<b>b<b>b<b>b<
		16g30a,

		x1000 >>
		2r4FFFFFFFF
		FFFFFFFF
		FFFFFFFF
		14g2r32a
	`
})
