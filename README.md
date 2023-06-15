# avr_musicbox
avrマイコンとスピーカだけで作れる和音再生可能な電子オルゴール

[GitHub](https://github.com/mcbeeringi/avr_musicbox/)
## 機能
- avrとスピーカーの直結可
- タクトスイッチとLED
- 4ch矩形波
- 音域: C1~B7
- 楽譜毎にループ機能
- チャンネル毎に設定可能
	- 減衰の有無
	- パルス幅(1:1, 3:1)
	- 音量(1bit)

## 対応AVR
- ATTiny85(t85)
	- t45も可
- ATTiny202(t202)
	- t402も可

## 譜面作成
Music Macro Languageライクの記法で譜面作成可能

[譜面作成 mml.html](mml.html)

### フォーマット
```
header 2byte
	BBBBBBBB
	BBBBBL__
		BPM*minNote 13bit
		loop 1bit
track
	0 1byte
	commands 1byte
		1LOONNNN
			note=NNNN+(O+(baseMode?1:4))*12;
			length=tick[L];
			play();

		01LTTTTT
			tick[L]=TTTTT;

		001_BVME
			bass=B;
			halfVol=V;
			pulseMod=M;
			envelope=!E;

		00011111~00000010 reserved

		00000001
			break;
0 0 2byte
```