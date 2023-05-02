# avr_musicbox
avr-gcc製の電子オルゴール
## 対応チップ
### t85_musicbox
- ATTiny85
- 4チャネルの矩形波
- 設定可能項目
	- 減衰の有無
	- 音量(1bit)
	- パルス幅(1:1, 3:1)
	- ループ
	- ボタン機能(停止, 一時停止)

### t202_musicbox
WIP
- ATTiny202
- 省容量フォーマット
	- 1音符1byte

## 譜面作成
index.htmlでMusic Macro Languageを使って譜面作成可能