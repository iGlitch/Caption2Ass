chcp 932
echo off
setlocal
SET STR_Version=v2.48_150628r0
echo H.264自動エンコード・字幕埋め込み実行バッチ %STR_Version%
rem v2.47to2.48:プリセット設定を変更. 旧版の720p変換→720pa, BS/CS等FHD解像度用の通常720p変換→720p.
rem v2.45to2.47:Caption2Assの実行方法を変えて実行時間を少し短縮.仕様変更に対応するためパラメータを変更.
rem    動作確認:Win8.1, HandBrake 0.10.2, mkvtoolnix 8.8.0 (全て64ビット版)
echo 引数指定方法: "入力ファイルパス" [プリセット名 [mkv/mp4]]
echo 引数指定例: "番組タイトル.ts" 480p mp4
echo 既定の設定: 720p mkv
rem 指定が無ければmkvで出力します. MKV変換を行う場合はMKVToolNixが必要です.
SET PATH_HandBrakeCLI=C:\Program Files\Handbrake\HandBrakeCLI.exe
SET PATH_Caption2Ass=C:\TvRock\Cap2Ass_C5\Caption2AssC_x64.exe
SET PATH_mkvmerge=C:\Program Files\MKVToolNix\mkvmerge.exe
SET PATH_OutputDir=D:\DTV
SET PATH_LogFile=HB_Batch.log
set retnum=127
set infiledir=%~dp1
set infiledrive=%~d1
if not exist "%infiledir%" goto nofiledir
%infiledrive%
cd "%infiledir%"
if not exist "%PATH_LogFile%" (
call :echo H.264自動エンコード・字幕埋め込み実行バッチ ログ
call :echo ログファイルHB_Batch.logは自動では削除されません. 定期的に削除して下さい.
)
>>"%PATH_LogFile%" date /t
>>"%PATH_LogFile%" time /t
>>"%PATH_LogFile%" echo %STR_Version%
call :echo dir:%infiledir%
call :echo args:%0 %*
if not exist "%PATH_HandBrakeCLI%" goto error_noexefile
if not exist "%PATH_Caption2Ass%" goto error_noexefile
call :echo 引数解析...
set infile=%~1
set infilename=%~n1

:fpath_repeat
if exist "%infile%" goto file_found
if "%~2"=="" goto nofile
shift
set infilename=%infile%　%~n1
set infile=%infile%　%~1
goto fpath_repeat

:file_found
shift
set enc_type=%~1
rem 既定のenc_type
if "%~1"=="" set enc_type=720p
shift
set file_type=%~1
rem 既定のfile_type
if "%~1"=="" set file_type=mkv
call :echo infile:%infile%
call :echo enc_type:%enc_type%
call :echo file_type:%file_type%
rem file_typeチェック
if "%file_type%"=="mp4" (
rem
) else if "%file_type%"=="mkv" (
rem
) else if "%file_type%"=="mp4_nosub" (
rem
) else if "%file_type%"=="mkv_nosub" (
rem
) else (
goto error_sel_ftype
)

rem HandBrakeCLIの引数を設定 好みに応じて変えて下さい
set PARAM_VideoOptions=-e x264 -q 24 -r 23.976 --cfr --h264-level=4.0 --h264-profile=high
set PARAM_AudioOptions=-a 1 -E faac -6 stereo -D 0 --gain 0
if "%enc_type%"=="720pa" (
set PARAM_FileDesc=720p x264 AAC
set PARAM_PictureOptions=-Y 720 --crop 0:0:0:0 --modulus 8 --loose-anamorphic
set PARAM_FilterOptions=--deinterlace=slower
set PARAM_Cap2AssOptions=-asstype 960x720
) else if "%enc_type%"=="720p" (
set PARAM_FileDesc=720p x264 AAC
set PARAM_PictureOptions=-Y 720 --crop 0:0:0:0
set PARAM_FilterOptions=--deinterlace=slower
set PARAM_Cap2AssOptions=
) else if "%enc_type%"=="720i" (
set PARAM_FileDesc=720i x264 AAC
set PARAM_PictureOptions=-Y 720 --crop 0:0:0:0
set PARAM_FilterOptions=
set PARAM_Cap2AssOptions=
) else (
goto end_err
)
rem MKVの場合は字幕データはass,srtを埋め込む
rem MP4の場合は字幕データはsrtを埋め込む
if "%file_type%"=="mkv" goto exportass
if "%file_type%"=="mp4" goto exportass
goto end_exportsrt

:exportass
call :echo 実行:%PATH_Caption2Ass% %PARAM_Cap2AssOptions% -format dual "%infile%"
start "Caption2Ass dual" /WAIT /I /BELOWNORMAL /MIN %PATH_Caption2Ass% %PARAM_Cap2AssOptions% -format dual "%infile%"
set exitcode=%errorlevel%
call :echo 終了コード %exitcode% .
if %exitcode% GEQ 1 goto failed_getcaption

:end_exportsrt
if not exist "%infilename%.srt" (
set fileSize=-1
) else (
call :getFilesize "%infilename%.srt"
)

call :echo 字幕データサイズ:%fileSize% bytes
if %fileSize% LEQ 3 (
call :echo 字幕データは見つかりませんでした.
if "%file_type%"=="mp4" set file_type=mp4_nosub
if "%file_type%"=="mkv" set file_type=mkv_nosub
) else (
rem 字幕データがある場合
)
goto end_getcaption

:failed_getcaption
call :echo 字幕データの抽出に失敗しました.
if "%file_type%"=="mp4" set file_type=mp4_nosub
if "%file_type%"=="mkv" set file_type=mkv_nosub
:end_getcaption
rem 出力ファイルの拡張子名を設定
if "%file_type%"=="mp4" ( 
set outftypename=mp4
set PARAM_SubtitleOptions=-N jpn --srt-file "%infilename%.srt" --srt-codeset UTF-8 --srt-lang jpn
) else if "%file_type%"=="mkv" (
set outftypename=mkv
set PARAM_SubtitleOptions=
) else if "%file_type%"=="mp4_nosub" (
set outftypename=mp4
set PARAM_SubtitleOptions=
) else if "%file_type%"=="mkv_nosub" (
set outftypename=mkv
set PARAM_SubtitleOptions=
) else (
goto error_sel_ftype
)
rem 既に同名の出力ファイルが存在すれば終了
if exist "%infilename% (%PARAM_FileDesc%).%file_type%" goto error_samefileexist
if exist "%PATH_OutputDir%\%infilename% (%PARAM_FileDesc%).%file_type%" goto error_samefileexist
call :echo HandBrakeCLI %file_type% %PARAM_FileDesc%
call :echo 実行:"%PATH_HandBrakeCLI%" -i "%infile%" -o "%infilename% (%PARAM_FileDesc%).%outftypename%" -f %outftypename% %PARAM_FilterOptions% %PARAM_VideoOptions% %PARAM_AudioOptions% %PARAM_PictureOptions% --verbose=1 %PARAM_SubtitleOptions%"
start "HandBrakeCLI %file_type% %PARAM_FileDesc% %infilename%" /WAIT /I /BELOWNORMAL /MIN "%SystemRoot%\System32\cmd.exe" /c "1>"%infilename% (%PARAM_FileDesc%).%outftypename%.log" 2>&1 3>&1 "%PATH_HandBrakeCLI%" -i "%infile%" -o "%infilename% (%PARAM_FileDesc%).%outftypename%" -f %outftypename% %PARAM_FilterOptions% %PARAM_VideoOptions% %PARAM_AudioOptions% %PARAM_PictureOptions% --verbose=1 %PARAM_SubtitleOptions%"
set exitcode=%errorlevel%
call :echo 終了コード %exitcode% .
if %exitcode% NEQ 0 goto hb_err

if "%file_type%"=="mkv" goto mergesub
goto hb_success
:mergesub
ren "%infilename% (%PARAM_FileDesc%).%outftypename%" "%infilename% (%PARAM_FileDesc%).temp.%outftypename%"
call :echo mkvmerge処理...
call :echo 実行:"%PATH_mkvmerge%" --default-language jpn -o "%infilename% (%PARAM_FileDesc%).%outftypename%" "%infilename% (%PARAM_FileDesc%).temp.%outftypename%" "%infilename%.ass" "%infilename%.srt"
start "mkvmerge %file_type% %PARAM_FileDesc% %infilename%" /WAIT /I /BELOWNORMAL /MIN "%SystemRoot%\System32\cmd.exe" /c "1>>"%infilename% (%PARAM_FileDesc%).%outftypename%.log" 2>>&1 3>>&1 "%PATH_mkvmerge%" --default-language jpn -o "%infilename% (%PARAM_FileDesc%).%outftypename%" "%infilename% (%PARAM_FileDesc%).temp.%outftypename%" "%infilename%.ass" "%infilename%.srt""
set exitcode=%errorlevel%
call :echo 終了コード %exitcode% .
if %exitcode% NEQ 0 goto hb_err

:hb_success
call :echo --- 正常終了 ---
set retnum=0
call :echo 出力ファイル:%infilename% (%PARAM_FileDesc%).%outftypename%
rem ファイル移動処理
IF DEFINED PATH_OutputDir (
IF NOT EXIST "%PATH_OutputDir%" goto error_outdirnotexist
MOVE /Y "%infilename% (%PARAM_FileDesc%).%outftypename%" "%PATH_OutputDir%"
call :echo 出力ファイル移動:%PATH_OutputDir%
) else (
call :echo 環境変数PATH_OutputDirが未定義のため、出力ファイルを移動しません.
)
if not exist "%infiledir%converted" mkdir "%infiledir%converted"
MOVE /Y "%infilename% (%PARAM_FileDesc%).%outftypename%.log" "%infiledir%converted"
call :echo 入力ファイル移動:%infiledir%converted
MOVE /Y "%infile%" "%infiledir%converted"
rem 万が一変換作業に失敗したときのために入力ファイルは削除していません. バッチ処理で入力ファイルを削除したい場合は上の2行の行頭にREMを付けて次の2行の行頭のREMを削除して下さい.
rem call :echo 入力ファイル削除
rem del "%infile%"
goto end_cleanup
rem ---関数等---
:getFilesize
set filesize=%~z1
exit /b
:echo
set msg_output=%*
echo. %msg_output%
>>"%PATH_LogFile%" echo. %msg_output%
exit /b
rem ---エラー処理---
:hb_err
set errmsg=外部コマンドは異常終了しました.
goto end_err
:nofiledir
set errmsg=入力ファイルディレクトリ %~1 が見つかりません.
goto end_err
:nofile
set errmsg=入力ファイル %~1 が見つかりません.
goto end_err
:error_sel_ftype
set errmsg=環境変数file_typeが正しくないため変換処理を中止します.
goto end_err
:error_noexefile
set errmsg=処理に必要なファイルまたはディレクトリが見つかりません. 必要なファイル・ディレクトリまたはバッチファイルに記述されているパスを確認して下さい.
goto end_err
:error_samefileexist
set errmsg=同名の出力ファイルが存在するため変換処理を中止します.
goto end_err
:error_outdirnotexist
set errmsg=出力先ディレクトリ %PATH_OutputDir% が見つからないため出力ファイルを移動できませんでした.
goto end_err
:end_err
if not defined errmsg goto end
call :echo *** 異常終了 ***
call :echo errmsg:%errmsg%
set retnum=1
:end_cleanup
rem 作業ファイル削除処理
if exist "%infilename%.ass" del "%infilename%.ass"
if exist "%infilename%.srt" del "%infilename%.srt"
if exist "%infilename% (%PARAM_FileDesc%).temp.%outftypename%" del "%infilename% (%PARAM_FileDesc%).temp.%outftypename%"
:end
call :echo ----------------------------------------
exit %retnum%