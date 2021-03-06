# hebocon2018
ヘボコン2018関連プロジェクト

## ハードウェア情報

### Arduino Mini Pro

* [回路図](https://www.arduino.cc/en/uploads/Main/Arduino-Pro-Mini-schematic.pdf)

### TA7291P

* [データシート](http://akizukidenshi.com/download/ta7291p.pdf)

## Raspberry Pi

### イメージ作成

* イメージダウンロード
    * https://downloads.raspberrypi.org/raspbian_lite_latest
* SDカードに書き込む。
    * 使用ツール [Etcher](https://etcher.io/)
* ブート設定変更
    * SSH有効化
        * bootドライブ直下に `ssh` という名前の空ファイルを作成する。
    * USB OTG設定
        * bootドライブ直下の`cmdline.txt`に`modules-load=dwc2,g_ether`を追加する。
            * `rootwait`と`quiet`の間に追加する。
        * bootドライブ直下の`config.txt`の最後に`dtoverlay=dwc2`を追加する。
* SSH接続
    * `ssh pi@raspberrypi.local`で接続可能
        * 初期パスワードは`raspberry`

### 設定

* `pi`ユーザーパスワード変更
    * `sudo passwd pi`
* タイムゾーン変更
    * `sudo raspi-config`
* Wifi国指定
    * `sudo raspi-config`
* ホスト名変更
    * `sudo raspi-config`で`Advanced Options` > `Hostname`
* AP化
    * [公式ドキュメント](https://www.raspberrypi.org/documentation/configuration/wireless/access-point.md)
* pipインストール
    * `sudo apt-get install python3-pip`
    * `pip3 install tornado`
* I2C有効化
    * `sudo raspi-config`
    * `sudo apt-get install python3-smbus i2c-tools`
* ssh-keygen
    * Github用に生成、登録する。
    * `sudo apt-get install git`
    * `git config --global user.name "user name"`
    * `git config --global user.email "user.name@mail.com"`
    * `git config --global core.editor 'vim -c "set fenc=utf-8"'`

### vim設定

`sudo apt-get install vim` 実行

`~/.vimrc`に下記を記載

```
set encoding=utf-8
set fileencodings=utf-8
set fileformats=unix,dos,mac

syntax on
```

### イメージバックアップ

* Macで下記を実行する。
    * `tar -zcvf /yourflashdrive/raspbian.tar.gz dev/mmcblk0p1`

