({
	bpm:140,// テンポ
	minNote:1/16,// 音符の最小単位
	// ループ_ポーズ (どちらも1にすると複数曲再生ができなくなる)
	lp:0b1_0,
	vwd:[// 音量半分_音色_減衰無効化
		0b0_1_0,
		0b0_1_0,
		0b0_1_0,
		0b0_1_0
	],
	notes:`
		2>
		FG1d2D<1b>dC<2bb>C d1dC<b>CDFGDFCd<b>C<b> 2DF1GDFCD<b>dDdC<b>C 2d<1b>CdFCdC<b>2C<b>C
		FG1d2D<1b>dC<2bb>C d1dC<b>CDFGDFCd<b>C<b> 2DF1GDFCD<b>dDdC<b>C 2d<1b>CdFCdC<b>2C<bb
		b1FG2b1FGb>CD<b>eDeF <2bb1FGbF>eDC<bFDeF 2b1FG2b1FGbb>CD<bFGF 2b1bAbFGb>eDeF<2bA
		b1FG2b1FGb>CD<b>eDeF <2bb1FGbF>eDC<bFDeF 2b1FG2b1FGbb>CD<bFGF 2b1bAbFGb>eDeF<2b>C,
		<
		2eeFFDDGGCCFF<bb1b>dC<b> 2eeFFDDGGCCFF<bb1b>CdD
		2eeFFDDGGCCFF<bb1b>dC<b> 2eeFFDDGGCCFF<bb1b>CdD
		2eeFFDDGGCCFF<bb1b>dC<b> 2eeFFDDGGCCFF<bb1b>CdD
		2eeFFDDGGCCFF<bb1b>dC<b> 2eeFFDDGGCCFF<bb1b>CdD
		
	`
})
