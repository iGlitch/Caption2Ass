
Caption2Ass 補完計画（Cleanup code）

オリジナルのソースコードは読みにくいので、クリーンナップする必要を感じた。
見苦しいコマンドラインパースや、字幕処理に関係のないパケットパースは極力排除した。
知る必要はないが、パケットパースも極力、規格書に沿ったパックドstructで書き直した。

結果、メインソース・Caption2Ass.cpp はmain, DumpAssLine, DumpSrtLine のみを含む。
main も字幕処理に関係のないコードを排除したので、処理の流れが見易くなっている。

オリジナル版の処理：

オリジナル版はsrt出力を主目的としているらしく、メインループでわざわざUTF8文字列の
リストを生成して DumpAssLine, DumpSrtLine に渡している（この段階で位置・色情報など
が失われている）。

// parse caption;　とコメントされているところから、字幕処理が始まる。

capUtil.AddTSPacket(pbPacket);　でcaption.dllにパケットデータをフィードするが、一度
では必要なデータが揃わない。

capUtil.AddTSPacketがNO_ERR_CAPTIONを返したとき、capUtil.GetCaptionDataでCAPTION_DATA
を得ることが出来る。GetCaptionDataはCAPTION_DATAのベクター型を返す。

次にCAPTION_DATA要素のCAPTION_CHAR_DATAからstrDecode.c_str()で、caption.dllによってARIB
からsjisに変換された文字列を取り出し、UTF8に変換してstd::list<PSRT_LINE> SRT_LISTを作成
している。

CAPTION_DATAのbClearがtrueのとき字幕持続時間dwWaitTimeが確定し、DumpAssLine, 
DumpSrtLine を呼び出している。しかし、このときのCAPTION_CHAR_DATAの内容は無視している。

字幕情報を保持する計画：

位置・色などの字幕情報はCAPTION_DATAとCAPTION_CHAR_DATAに保持されているので、これらの
コピーをリスト（または配列）にして、DumpAssLine, DumpSrtLine の側で文字列を取り出すよう
に変更する。字幕情報はass/srtでサポートされるタグの形式で出力する。

