今回の試作品は保存されたTSファイルから、字幕を抽出し、.ASS あるいは .SRT 字幕ファイルを作るものです。

[使い方]

1. Caption2Ass.exe と Caption.dllを同じフォルダーに置く。
2. cmd.exeを実行する。

3. Caption2Ass.exe "C:\MyRecordedTsFile.ts" このように Caption2Ass.exeを実行してください。
   C:\MyRecordedTsFile.tsは保存されたTSファイルの名前です。

   (Double quotation marksを忘れないで。)

   自分で PMT Pid指定もできる。
　 Ex: Caption2Ass.exe -PMT_PID 1f0 "C:\MyRecordedTsFile.ts"
   PIDは Hex。

   出力字幕タイプ指定可能。(-format {srt|ass})
   Ex: Caption2Ass.exe -format srt "C:\MyRecordedTsFile.ts"

   出力字幕 FileName指定可能。
   Caption2Ass.exe -format srt "C:\MyRecordedTsFile.ts" "D:\MyRecordedTsFile.srt"
   (指定しない場合、デフォルトは xxxxxxx.srt(.ass)のようにします。)

[変更履歴]
2008-12-21
 出力字幕タイプ指定可能。
 出力字幕 FileName指定可能。

2008-12-20
 初版