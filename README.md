# avr-musicbox

avrマイコンとスピーカだけで作れる和音再生可能な電子オルゴール

[GitHub](https://github.com/mcbeeringi/avr-musicbox/)

参考元
<https://hello-world.blog.ss-blog.jp/search/?keyword=%E9%9F%B3%E6%A5%BD%E3%82%92%E6%BC%94%E5%A5%8F%E3%81%97%E3%81%9F%E3%81%84>

## 機能

- avrとスピーカーの直結可
- タクトスイッチとLED
- 4ch矩形波
- 音域: C1~B7
- 楽譜毎にループ機能
- チャンネル毎に設定可能
  - 減衰の有無
  - パルス幅(1/2, 1/4)
  - 音量(1bit)

## 対応AVR

- ATTiny85(t85)
  - t45も可
- ATTiny202(t202)
  - t402も可

ピンの機能は各main.cの先頭にメモあり

## 譜面作成

Music Macro Languageライクの記法で譜面作成可能

[譜面作成 mml.html](mml.html)

### フォーマット

```text
header 2byte
  TTTTTTTT
  TTT____L
    TickPerMinute=(beat/minute=BPM)*(tick/beat=beat(♩(1/4) in most)/minNoteValue) 11bit
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

## 使い方

platformio core を使用
必要に応じてインストール

各ディレクトリにて`pio run`で書き込み

## PCB

KiCADのデータがあるかも
[pcb-stuff](https://github.com/mcbeeringi/pcb-stuff)
