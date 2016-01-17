chcp 932
echo off
setlocal
SET STR_Version=v1.10_131218
SET PATH_Batch=C:\TvRock\hb_h264qsv.bat
echo ディレクトリ内TSファイル一括変換処理実行バッチ %STR_Version%
title ディレクトリ内TSファイル一括変換 %STR_Version%
echo カレントディレクトリにある全てのTSファイルについてhb_h264qsv.batを呼び出し
echo て一括で変換するバッチです。
set curdir=%~dp0
echo カレントディレクトリ:%curdir%
if not exist %PATH_Batch% goto nobatch
>hb_FileList.txt dir *.ts /b
if not exist hb_FileList.txt goto nofile
echo 処理対象ファイル
type hb_FileList.txt
echo.
echo 処理を中止するには実行中のプログラム・ウィンドウを開きCTRL+Cキーを押して下さい.
echo 外部コマンド実行中は2回押して下さい.
echo 処理を中止すると作業ファイルが残る場合があります.
echo.
FOR /F "delims=" %%a in (hb_FileList.txt) do (
echo 実行中:%PATH_Batch% "%%~fa"
echo.
start "%%~a" /WAIT /I /MIN %PATH_Batch% "%%~fa"
)
goto end
:nobatch
echo hb_h264qsv.batが見つかりません.PATH_Batchに設定したパスを確認して下さい.
:nofile
echo .TSファイルが見つかりません.
:end
echo 全てのコマンドが完了しました.
echo 各ファイル処理の結果は呼び出し先プログラム・バッチのログファイル等を参照して下さい.
pause
if exist hb_FileList.txt del hb_FileList.txt
endlocal