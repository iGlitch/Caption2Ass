//------------------------------------------------------------------------------
//IniFile.cpp
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <shlwapi.h>

#include "IniFile.h"
#include "CaptionDef.h"
#include "Caption2Ass_PCR.h"

#define FILE_PATH_MAX           (2048)
#define INI_STRING_MAX          (1024)

static const unsigned char utf16le_bom[4] = { 0xFF, 0xFE, 0x5B, 00 };

static int GetPrivateProfilePath(TCHAR *ini_file)
{
    int ret = -1;

    // Allocate string buffers
    TCHAR *process_path = new TCHAR[FILE_PATH_MAX];
    if (!process_path)
        goto EXIT;
    // Initliaze string buffers.
    memset(process_path, 0, sizeof(TCHAR) * FILE_PATH_MAX);

    // Get the full path name of the running process.
    DWORD dwRet = GetModuleFileName(NULL, process_path, sizeof(TCHAR) * FILE_PATH_MAX);
    if (dwRet == 0)
        goto EXIT;

    // Generate the ini file path.
    _tcscpy_s(ini_file, FILE_PATH_MAX, process_path);
    TCHAR *pExt = PathFindExtension(ini_file);
    _tcscpy_s(pExt, 5, _T(".ini"));

    ret = 0;
EXIT:
    SAFE_DELETE_ARRAY(process_path);

    return ret;
}

extern int IniFileRead(TCHAR *ass_type, ass_setting_t *as)
{
    int ret = -1;
	int alignCenter = 0;

    // Allocate string buffers.
    TCHAR *ini_file = new TCHAR[FILE_PATH_MAX];
    TCHAR *tmp_buff = new TCHAR[INI_STRING_MAX];
    WCHAR *utf8_str = new WCHAR[INI_STRING_MAX];
    if (!ini_file || !tmp_buff || !utf8_str)
        goto EXIT;
    // Initliaze string buffers.
    memset(ini_file, 0, sizeof(TCHAR) * FILE_PATH_MAX);
    memset(tmp_buff, 0, sizeof(TCHAR) * INI_STRING_MAX);
    memset(utf8_str, 0, sizeof(WCHAR) * INI_STRING_MAX);

    // Get the file path of ini file.
    if (GetPrivateProfilePath(ini_file))
        goto EXIT;
    // Open ini file.
    FILE *fp = NULL;
    if (_tfopen_s(&fp, ini_file, _T("r")) || !fp) {
        if (_tfopen_s(&fp, ini_file, _T("wb")) || !fp)
            goto EXIT;
#ifdef _UNICODE
		fwrite(utf16le_bom, 4, 1, fp);
#endif
        _ftprintf(fp, _T("%s"), _T(DEFAULT_INI));
    }
    fclose(fp);

    // Caption offset of SWF-Mode
    as->SWF0offset=GetPrivateProfileInt(_T("SWFModeOffset"), _T("SWF0offset"), 0, ini_file);
    as->SWF5offset=GetPrivateProfileInt(_T("SWFModeOffset"), _T("SWF5offset"), 0, ini_file);
    as->SWF7offset=GetPrivateProfileInt(_T("SWFModeOffset"), _T("SWF7offset"), 0, ini_file);
    as->SWF9offset=GetPrivateProfileInt(_T("SWFModeOffset"), _T("SWF9offset"), 0, ini_file);
    as->SWF11offset=GetPrivateProfileInt(_T("SWFModeOffset"), _T("SWF11offset"), 0, ini_file);

    // ass header infomation
#ifndef _UNICODE
#define GET_INI_STRING(sec, key, def, tmp, str, len, ini, get)      \
do {                                                                \
    GetPrivateProfileStringA(sec, key, def, tmp, len, ini);          \
    MultiByteToWideChar(932, 0, tmp, -1, str, len);                 \
    WideCharToMultiByte(CP_UTF8, 0, str, -1, get, len, NULL, NULL); \
} while (0)
#else //_UNICODE
#define GET_INI_STRING(sec, key, def, tmp, str, len, ini, get)      \
do {                                                                \
    GetPrivateProfileStringW(sec, key, def, str, len, ini);          \
    WideCharToMultiByte(CP_UTF8, 0, str, -1, get, len, NULL, NULL); \
} while (0)
#endif
#define GET_INI_VALUE(sec, key, def, ini, get)          \
do {                                                    \
    get = GetPrivateProfileInt(sec, key, def, ini);     \
} while (0)

    GET_INI_STRING(ass_type, _T("Comment1"), NULL, tmp_buff, utf8_str, INI_STRING_MAX, ini_file, as->Comment1);
    GET_INI_STRING(ass_type, _T("Comment2"), NULL, tmp_buff, utf8_str, INI_STRING_MAX, ini_file, as->Comment2);
    GET_INI_STRING(ass_type, _T("Comment3"), NULL, tmp_buff, utf8_str, INI_STRING_MAX, ini_file, as->Comment3);
    GET_INI_VALUE(ass_type, _T("PlayResX"), 1920, ini_file, as->PlayResX);
    GET_INI_VALUE(ass_type, _T("PlayResY"), 1080, ini_file, as->PlayResY);

    GET_INI_STRING(ass_type, _T("DefaultFontname"), _T("MS UI Gothic"), tmp_buff, utf8_str, INI_STRING_MAX, ini_file, as->DefaultFontname);
    GET_INI_VALUE(ass_type, _T("DefaultFontsize"), 90, ini_file, as->DefaultFontsize);
    GET_INI_STRING(ass_type, _T("DefaultStyle"), _T("&H00FFFFFF,&H000000FF,&H00000000,&H00000000,0,0,0,0,100,100,15,0,1,2,2,1,10,10,10,0")
                 , tmp_buff, utf8_str, INI_STRING_MAX, ini_file, as->DefaultStyle);

    GET_INI_STRING(ass_type, _T("BoxFontname"), _T("MS UI Gothic"), tmp_buff, utf8_str, INI_STRING_MAX, ini_file, as->BoxFontname);
    GET_INI_VALUE(ass_type, _T("BoxFontsize"), 90, ini_file, as->BoxFontsize);
    GET_INI_STRING(ass_type, _T("BoxStyle"), _T("&HFFFFFFFF,&H000000FF,&H00FFFFFF,&H00FFFFFF,0,0,0,0,100,100,0,0,1,2,2,2,10,10,10,0")
                 , tmp_buff, utf8_str, INI_STRING_MAX, ini_file, as->BoxStyle);

    GET_INI_STRING(ass_type, _T("RubiFontname"), _T("MS UI Gothic"), tmp_buff, utf8_str, INI_STRING_MAX, ini_file, as->RubiFontname);
    GET_INI_VALUE(ass_type, _T("RubiFontsize"), 50, ini_file, as->RubiFontsize);
    GET_INI_STRING(ass_type, _T("RubiStyle"), _T("&H00FFFFFF,&H000000FF,&H00000000,&H00000000,0,0,0,0,100,100,0,0,1,2,2,1,10,10,10,0")
                 , tmp_buff, utf8_str, INI_STRING_MAX, ini_file, as->RubiStyle);
	GET_INI_VALUE(ass_type, _T("AlignCenter"), 0, ini_file, alignCenter);
	if(alignCenter) as->aligncenter = true;

#undef GET_INI_STRING
#undef GET_INI_VALUE

    ret = 0;
EXIT:
    SAFE_DELETE_ARRAY(ini_file);
    SAFE_DELETE_ARRAY(tmp_buff);
    SAFE_DELETE_ARRAY(utf8_str);

    return ret;
}

#ifdef _DEBUG
extern int load_debug(int *argc_p, TCHAR ***argv_p)
{
    int ret = 0;
    int argc = 0;
    TCHAR **argv = NULL;

    // Allocate string buffer.
    TCHAR *ini_file = new TCHAR[FILE_PATH_MAX];
    TCHAR *tmp_buff = new TCHAR[INI_STRING_MAX];
    if (!ini_file || !tmp_buff)
        return 0;
    memset(ini_file, 0, sizeof(TCHAR) * FILE_PATH_MAX);
    memset(tmp_buff, 0, sizeof(TCHAR) * INI_STRING_MAX);

    // Get the file path of ini file.
    if (GetPrivateProfilePath(ini_file))
        goto EXIT;
    // Open ini file.
    FILE *fp = NULL;
    if (_tfopen_s(&fp, ini_file, _T("r")) || !fp)
        goto EXIT;

    // Parse ini file.
    int debug = 0;
    while (1) {
        if (_ftscanf_s(fp, _T("%s"), tmp_buff, INI_STRING_MAX) == EOF)
            goto EXIT;
        if (debug == 0) {
            // Search debug section.
            if (_tcsicmp(tmp_buff, _T("[Debug]")) == 0)
                debug = 1;
            continue;
        }
        if (argc == 0) {
            // Check nums of debug settings.
            if (_stscanf_s(tmp_buff, _T("argc=%d"), &argc) == 1)
                break;
        }
    }

    // Allocate buffers of debug strings.
    argv = new TCHAR *[argc];
    if (!argv)
        goto EXIT;
    memset(argv, 0, sizeof(TCHAR *) * argc);
    for (int i = 1; i < argc; i++) {
        argv[i] = new TCHAR[INI_STRING_MAX];
        if (!(argv[i]))
            goto EXIT;
        memset(argv[i], 0, sizeof(TCHAR) * INI_STRING_MAX);
    }
    // Load debug settings.
    int tmp_index = 0;
    for (int i = 1; i < argc; i++) {
        if (_ftscanf_s(fp, _T("%s"), tmp_buff, INI_STRING_MAX) == EOF)
            goto EXIT;
        if (_stscanf_s(tmp_buff, _T("argv%d=%s"), &tmp_index, argv[i], INI_STRING_MAX) != 2)
            goto EXIT;
    }

    argv[0] = (*argv_p)[0];     // Copy pointer of process path.
    *argv_p = argv;
    *argc_p = argc;
    ret = 1;

EXIT:
    if (ret == 0) {
        for (int i = 1; i < argc; i++)
            SAFE_DELETE_ARRAY(argv[i]);
        SAFE_DELETE_ARRAY(argv);
    }

    fclose(fp);
    SAFE_DELETE_ARRAY(ini_file);
    SAFE_DELETE_ARRAY(tmp_buff);

    return ret;
}

extern void unload_debug(int argc, TCHAR **argv)
{
    for (int i = 1; i < argc; i++)
        SAFE_DELETE_ARRAY(argv[i]);
    SAFE_DELETE_ARRAY(argv);
}
#endif
