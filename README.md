# インタラクティブCG 課題

## このリポジトリについて

このリポジトリは **OS X Mountain Lion** のみを対象にしています。
それ以外のディストリビューションでは正しく動作しない可能性が高いです。

## 動作環境

このリポジトリに含まれるファイルをコンパイルするために必要なものがいくつかあります。

### FLTK

[Homebrew](http://brew.sh/)を使っている場合はそこから最新安定版である1.3.2をインストールすると良いです。
ただ、僕のMacBook Pro 2011 Earlyでは最新安定版が動作しなかったのでスナップショットを入れました。

### GCC

Xcodeに付属しているコンパイラではコンパイル出来ません。Homebrewにgccのパッケージは入っていませんが、
`brew tap homebrew/versions`するなどしてパッケージを追加するとよいです。
僕は`gcc4.8`を入れました。

### X11

`Modeler`をコンパイルするためにはX11が必要なので、[XQuartz](http://xquartz.macosforge.org/landing/)を入れましょう。

### OMake

今回のプログラムには[OMake](http://omake.metaprl.org/index.html)を用いています。
OMakeはHomebrewに収録されていないので、HomebrewでOCamlのパッケージマネージャーである[OPAM](http://opam.ocamlpro.com/)をインストールして
OPAMからOMakeをインストールしてください。

## ビルドの仕方

基本的に`impressionist`など各課題フォルダの直下へ移動して、`omake`コマンドでビルド出来ると思います。
もしビルド出来ない場合は課題の直下にある`OMakefile`を編集する必要があるかもしれません。

### 例 - impressionistをコンパイルする

```
git clone https://github.com/coins11/interactive-computer-graphics.git
cd interactive-computer-graphics
cd impressionist
omake
```

## その他

思いついたことを列挙します。

- 文字コードと改行文字は`nkf`で _UTF-8:Unix_ へ変換
	+ `nkf -w -Lu --overwrite *`
- `#include`する際のOpenGLのパスを修正
	+ `perl -i -plE 's/<GL\/(.*\.h)>/<OpenGL\/\1>/g' *`
- 干渉するファイルをいくつか削除
- 謎のヘッダファイルを削除


