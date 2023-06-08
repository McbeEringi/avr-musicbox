# avr_musicbox
avrマイコンとスピーカだけで作れる和音再生可能な電子オルゴール

[GitHub](https://github.com/mcbeeringi/avr_musicbox/)
## 機能
- avrとスピーカーの直結可
- 4ch矩形波
- タクトスイッチとLED
- 楽譜毎にループ機能
- チャンネル毎に設定可能
	- 減衰の有無
	- パルス幅(1:1, 3:1)
	- 音量(1bit)

## 対応AVR
- ATTiny85(t85)
	- 楽譜サイズが小さければt45も可
- ATTiny202(t202)
	- t402も可

## 譜面作成
Music Macro Languageライクの記法で譜面作成可能

- [t202 & t85new](mml.html)
- [t85](t85/)(バイナリ互換性無し)

