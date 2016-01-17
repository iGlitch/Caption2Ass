# Caption2AssC5 rev.2 2015/05/13

## 使用許諾条件

このソフトを使用して得られるいかなるデータを第三者に渡したり
公衆に送信可能な状態にすることを禁じます。

私はCaption.dll、Caption2Ass_PCRなど改変元のプログラムを製作された原著作者とは一切関係ありません。
技術サポートには応じられません。

## 変更点

### Caption2Ass_C5 rev.2 2015/05/13

* Anamorphic Encodingが有効な場合にサイズ・位置が合わなくなるので適切なスタイルを追加 [Cap2AssC]

### Caption2Ass_C5 2015/05/10

* ASS出力について位置変更、ルビを適用するように変更。つまりCaption2Ass_PCR本来の仕様に戻した。iniファイルのスタイルセクションにAlignCenter=1またはコマンドで-centerスイッチを指定すると従来の形式で出力する。PlayRes=0かつPlayResY=0の場合も従来形式での出力になるが、この時フォントサイズが絶対値であることに注意 [Cap2AssC]
* 内部表現の完全Unicode化。利点はiniファイルやコマンド入力でUnicodeをサポートするため、スタイル・フォント名の自由度が増えたことくらい。字幕出力は従来通りUTF-8 [Cap2AssC]
* ASSヘッダーテキストの出力を変更 [Cap2AssC]

### Caption2Ass_C4 rev.3 2015/05/06

* x64(64ビット)実行バイナリを追加。64ビット版Windowsの場合はこちらを使ったほうが多少速い
* 抽出開始時の2秒間のウェイトを削除 [Cap2AssC]
* ASS出力で無意味な{}を出力しないように変更 [Cap2AssC]

### Caption2Ass_C4 rev.2 2015/01/26

* 本Readme.txtの「使用方法」にiniファイルとランタイムについての説明を追加。
* プログラムには手を加えていません。

### Caption2Ass_C4 rev.2 2014/01/15

* ビットマップ外字が字幕データで"[外:***]"と表示されていたのを表示しないように修正した [Caption]

### Caption2Ass_C4

新たにCaption2Ass_PCRをベースとして以下のように仕様を変更した

* ASS出力について位置変更、ルビ(ふりがな)を無視 [Cap2AssC]
* 改行を含む字幕が上から順に表示されない問題を修正 [Cap2AssC]

## 使用方法

Caption2AssC.exe、Caption.dll、iniフォルダーの3つを同一のフォルダーに配置して下さい。
コマンドプロンプトやバッチファイルから"Caption2AssC.exe -format ass "tsfile.ts"のように実行して下さい。
使用可能な引数を知るにはコマンドプロンプトからCaption2AssC.exeを実行して下さい。

標準設定ではフォントはMicrosoft Wordに付属する「HG丸ゴシックM-PRO」、
字幕表示解像度は1280x720ドット、サイズは50ptとして設定されています。
設定を変更するにはCaption2AssC.iniファイルを書き換えてください。

-asstype <string>スイッチを使うことでコマンドからプリセット設定を切り替えることができます。
例えば、Caption2AssC.iniに[default43]セクションで設定を記述して、
"Caption2AssC.exe -asstype default43 -format ass "tsfile.ts"
というように実行します。
-asstypeスイッチが指定されなかった場合はdefaultセクションの設定が使用されます。

### 必要なDLLファイル(MSVCR**.DLLなど)が見つからない。というエラーが出る場合。

プログラムをVisual Studio 2012でビルドしているため、
Visual C++ 2012用のランタイムをインストールすると問題が解決するかもしれません。
ランタイムはマイクロソフトのサイトから無料でダウンロードできます。

Visual Studio 2012 更新プログラム 4 の Visual C++ 再頒布可能パッケージ 
: <http://www.microsoft.com/ja-jp/download/details.aspx?id=30679>

x86(32ビット)版を使用する場合は、
32/64ビット版Windowsのどちらの場合でもvcredist_x86.exeを実行してください。

x64(64ビット)版を使用する場合はvcredist_x64.exeを実行してください。

## 改変・再配布について

プログラムのソース・バイナリはオリジナルのライセンスに準拠します。
改変して再配布する場合はオリジナルとは別の著作者・配布物であることを明示して下さい。許可は不要です。

~~~~~~~~~~~~~~~
●EpgDataCap_Bon、TSEpgView_Sample、NetworkRemocon、Caption、TSEpgViewServerの
ソースの取り扱いについて
　特にGPLとかにはしないので自由に改変してもらって構わないです。
　改変して公開する場合は改変部分のソースぐらいは一緒に公開してください。
　（強制ではないので別に公開しなくてもいいです）
　EpgDataCap.dllの使い方の参考にしてもらうといいかも。

●EpgDataCap.dll、Caption.dllの取り扱いについて
　フリーソフトに組み込む場合は特に制限は設けません。ただし、dllはオリジナルのまま
　組み込んでください。
　このdllを使用したことによって発生した問題について保証は一切行いません。
　商用、シェアウェアなどに組み込むのは不可です。
~~~~~~~~~~~~~~~

## 以下の変更点は現行バージョンには引き継がれていません

Caption2Ass_C3

文中のスタイル変更に対応(ASS)

INIファイルよりPlayResX,PlayResY,Styleを変更できるようにした

[Default]
PlayResX=1280
PlayResY=720
;Format: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColour, BackColour, Bold, Italic, Underline, StrikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding
DefaultStyle='Color,HGMaruGothicMPRO,30,0x00FFFFFF,0x000000FF,0x00000000,0x80000000,0,0,0,0,100,100,0,0,1,2,2,2,30,30,30,1'
Colorについては16進数で、&H00000000ではなく0や0x00000000などと指定する必要がある
ただしPrimaryColour, OutlineColour, BackColourについては字幕データで上書きされるため意味を成さない
フォント名は日本語名に対応していない

unicodeに対応しているようでしていない...

これ以上このソースに手を付けようとは思わない
Caption2Ass_PCRという優れた版があるので、それをベースにいじった方がよかったかも

Caption2Ass_C2

引数よりフォント指定対応
パラグラフ単位で字幕色に対応
//subtitle color style
//alpha value of charcolor == 255 --> ABGR(0,b,g,r)
//alpha value of backcolor == 255 --> ABGR(128,0,0,0)

Caption2Ass_C1

私が手を加えたのは、入力ファイルが存在しない等によるファイルハンドラ取得失敗時の終了バグ修正とpress any keyのコード(getchar)を削除しただけです。
Windows XP以前では動作しません。

オリジナルはCaption2Ass 補完計画（Cleanup code）[up1060.zip]