({
	bpm:120,// テンポ
	minNote:1/48,// 音符の最小単位
	// ループ_ポーズ (どちらも1にすると複数曲再生ができなくなる)
	lp:0b0_1,
	vwd:[// 音量半分_音色_減衰無効化
		0b0_1_0,
		0b0_0_0,
		0b0_1_0,
		0b1_0_0
	],
	notes:`
		>
		8g4g>c<g>cd<g>d8e4e8f4e8d4c<8b4a12g
		8g4g>c<g>cd<g>d8e4e8f4e8d<4b>4c<ab>crr<
		6defFgab>c12d4<ggg24g
		12a4gfe12dag4fed12cgf4fed6c<bab>12c4ceg>12cr<
		
		12eg>24c<12ga24g8r4c8e4g12>c<8b4a24gr
		8a4a8a12a>4c<8b4a24gr 8a4g8a4g12de24cr
		8G4G8G28G12g8g28g 12fff8d28e24r
		12c>c<b8g28a8r4a8b>4c 12dc<ba24gr
		>8c<4b>8c<4g8e>12c<28b12r8g4g
		12arbr>24cr<
		>8c<4b>8c<4g12e>8c<28b12r8g4g
		12arbr>6cc<AGFeDCcc<AGFeDC12c>4ceg>12cr,
		
		<
		12crcrcccr
		crcrcccr
		6defFgab>c12d<ggr
		12ffgfee<aa>ddggcccr
		
		ccccdd<gg>c<baa>dd<gg
		>ffffee<aa>dd<gg>cccr
		ffffeeeeddggccc<b
		aa>eefffeddFFgfed
		cccceeer
		frgrc<g>c4<gab>12
		ccc8c4d12e<b>er
		frgr24cccc12c<g>cr,
		
		48rr
		rr
		rr
		8r4c8r4c<8r4b8r4b 8r4b8r4b8r4a8r4a 8r4a8r4a8r4b8r4b 8r4g8r4g12cr
		
		8r4g8r4g8r4g8r4g 8r4a8r4a8r4b8r4g 8r4g8r4g8r4a8r4a 8r4a8r4a8r4b8r4b
		8r>4c8r4c8r4c8r4c< 8r4b8r4g8r4a8r4e 8r4f8r4f8r4g8r4g 8r4g8r4g12cr
		8r>4c8r4c8r4c8r4c 8r4c8r4c8r4c<8r4A 8r4a8r4a8r4b8r4g 8r4g8r4g8r4g8r4G
		8r4a8r4a8r4b8r4b >8r4c8r4c8r4c8r4c 8r4d8r4d8r4d8r4d< 8r4b8r4b8r4a8r4G
		8r4g8r4g8r4g8r4g 8r4b8r4b12br >crdr<
		8r4g8r4g8r4g12r
		8r4g8r4g8r4g12r 8r4b8r4b12br >crdr
		erergrAr>12c<gcr,
		
		>>>24AA12AAAr
		24AA12AAAr<<
		48rr
		rrrr
		
		48r 36r4gab 24>c<r r4grggFe
		24fr 12refg 24ar 8r4c8e4g>8c<2A>1c<A8a4g
		20G>16c<4G>c<G 20g>12c<4gefg
		24f12g4gab>8c<2b>1c<b8a4g8f2e1fe8d4c
		48rrr8g2g1ag8f2f1gf8e2e1fe8d2d1ed
		48c
	`
})
