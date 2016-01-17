// ReplaceFNameChar.cpp : コンソール アプリケーションのエントリ ポイントを定義します。

#ifdef _MSC_VER
#define _CTR_SECURE_NO_WARNINGS
#endif
#include <tchar.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define CTABLE_SIZE 4
_TCHAR* ctable[CTABLE_SIZE][2] = {
{ __T("　"), __T(" ")},
{ __T("&"), __T("＆")},
{ __T("^"), __T("＾")},
{ __T("!"), __T("！")}
};

int pathchg(_TCHAR *buf, const _TCHAR *strf, const _TCHAR *strr)
{
	_TCHAR *p;
	_TCHAR tmp[_MAX_FNAME];
	while ((p = _tcsstr(buf, strf)) != NULL) {
		*p = _T('\0');
		p += _tcslen(strf);
		_tcscpy(tmp, p);
		//check ov
		if(_tcslen(buf) + _tcslen(strr) >= _MAX_FNAME) return -1;
		_tcscat(buf, strr);
		//check ov
		if(_tcslen(buf) + _tcslen(tmp) >= _MAX_FNAME) return -1;
		_tcscat(buf, tmp);
	}
	return 0;
}
int pathrep(_TCHAR* strin)
{
	for (int i = 0; i < CTABLE_SIZE; ++i)
	{
		if(pathchg(strin, ctable[i][0], ctable[i][1])) return -1;
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	_TCHAR drive[_MAX_DRIVE];
	_TCHAR dir[_MAX_DIR];
	_TCHAR fname[_MAX_FNAME];
	_TCHAR ext[_MAX_EXT];
	_TCHAR fnamer[_MAX_PATH];
	FILE* fp;
	int retmain = 0;
	_tsetlocale(LC_ALL, _T("japanese_japan.932"));
	_tprintf(__T("n: %d\n"), argc - 1);
	if (argc < 2) {
			_tprintf(__T("説明:\nファイル名のうちコマンドプロンプトで使用できない文字を置換・リネーム\n"));
			_tprintf(__T("使い方:\n引数 ファイルパス1 [ファイルパス2 [...]]\n"));
			_tprintf(__T("またはエクスプローラー上で対象ファイルを本実行ファイルにドラッグアンドドロップ\n"));
			_tprintf(_T("置換文字:\n"));
			for (int i = 0; i < CTABLE_SIZE; ++i)
			{
				_tprintf(__T("'%s' -> '%s'\n"), ctable[i][0], ctable[i][1]);
			}
			getchar();
			return -1;
	}
	for (int i = 1; i < argc; ++i)
	{
		_tprintf(__T("\n%d: %s\n"), i, argv[i]);
		fp = _tfopen(argv[i], __T("r"));
		if (fp == NULL) {
			_tprintf(__T("入力ファイルを開けません.\n"));
			_tprintf(__T("ファイルパスとアクセス権限を確認してください.\n"));
			++retmain;
			continue;
		}
		fclose(fp);
		if(_tcslen(argv[i]) >= _MAX_PATH)
		{
			_tprintf(__T("ファイルパスが長すぎます.(>%d chs)\n"), _MAX_PATH);
			++retmain;
			continue;
		}
		_tsplitpath(argv[i], drive, dir, fname, ext);
		if(_tcslen(fname) >= _MAX_FNAME)
		{
			_tprintf(__T("ファイル名が長すぎます.(>%d chs)\n"), _MAX_FNAME);
			++retmain;
			continue;
		}
		if(pathrep(fname) != 0)
		{
			_tprintf(__T("置換後のファイル名の長さが上限を超えました.(>%d chs)\n"), _MAX_FNAME);
			++retmain;
			continue;
		}
		_tmakepath(fnamer, drive, dir, fname, ext);
		_tprintf(__T("-> %s\n"), fnamer);
		if (_tcscmp(fnamer, argv[i]) == 0)
		{
			_tprintf(__T("ファイル名を変更する必要はありません.\n"));
			continue;
		}
		fp = NULL;
		fp = _tfopen(fnamer, __T("r"));
		if (fp != NULL)
		{
			fclose(fp);
			_tprintf(__T("既に同名のファイルが存在します.\n"));
			++retmain;
			continue;
		}
		int retcode = _trename(argv[i], fnamer);
		if(retcode != 0)
		{
			retcode = _doserrno;//win sys err nuber
			_tprintf(__T("ファイル名を変更できませんでした.(errno=%d)\n"), retcode);
			++retmain;
		}
		else
		{
			_tprintf(__T("ファイル名を変更しました.\n"));
		}
	}
#if _DEBUG
	getchar();
#endif
	//ret 0:No error,>0:one or more errors have occured
	return retmain;
}
