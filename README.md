# hebocon2018
ヘボコン2018関連プロジェクト

## ハードウェア情報

### Arduino Micro

* [Pinout](https://www.arduino.cc/en/uploads/Main/ArduinoMicro_Pinout3.png)

### TA7291P

* [データシート](http://akizukidenshi.com/download/ta7291p.pdf)

## Raspberry Pi

### イメージ作成

* イメージダウンロード
    * https://downloads.raspberrypi.org/raspbian_lite_latest
* ブート設定変更
    * SSH有効化
        * bootドライブ直下に `ssh` という名前の空ファイルを作成する。
    * USB OTG設定
        * bootドライブ直下の`cmdline.txt`に`modules-load=dwc2,g_ether`を追加する。
            * `rootwait`と`quiet`の間に追加する。
        * bootドライブ直下の`config.txt`の最後に`dtoverlay=dwc2`を追加する。
* SDカードに書き込む。
    * 使用ツール [Etcher](https://etcher.io/)
* SSH接続
    * `ssh pi@raspberrypi.local`で接続可能
        * 初期パスワードは`raspberry`

