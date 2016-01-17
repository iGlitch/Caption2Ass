//------------------------------------------------------------------------------
// cmdline.cpp
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <strsafe.h>

#include "cmdline.h"
#include "CaptionDef.h"

static void usage(int argc)
{
    static const TCHAR *help[] = {
        _T("Usage:  Caption2AssC.exe [Options] source.ts [target filename]"),
        _T(""),
        _T("Options:"),
        _T("    -format <string>            Specify output format. {srt|ass|taw|dual}"),
        _T("                                    Default: ass"),
        _T("    -delay <integer>            Sepcify delay time. [mili-sec]"),
        _T("    -PMT_PID <hex>              Specify PID value."),
        _T("    -detect_length <integer>    Specify upper limit value of packet counting"),
        _T("                                 for detecting caption data. [10k]"),
        _T("                                    Default: 300"),
        _T("    -log                        Make log-file."),
        _T("    -keepinterval               Keep the interval of the output timestamp"),
        _T("                                 upon detection of packet loss."),
        _T("  [srt]"),
        _T("    -srtornament                Set ornament to srt-file."),
        _T("  [ass]"),
        _T("    -asstype <string>           Sepcify type name of ass setting."),
        _T("    -hlc <string>               Sepcify HLC control type. {kigou|box|draw}"),
        _T("                                    Default: kigou"),
        _T("    -norubi                     Does not output the Rubi to ass-file."),
//      _T("                                (Note: This build does NOT support Rubi.)"),
        _T("    -center                     Fix align of text at bottom-center, no rubi."),
        _T(""),
        _T("Example:"),
        _T("    Caption2AssC.exe -format dual \"source.ts\""),
        _T("    Caption2AssC.exe -format ass -asstype Default43 -hlc kigou \"source.ts\""),
        _T("    Caption2AssC.exe -delay 500 -PMT_PID 1f2 -detect_length 400 \"source.ts\""),
        NULL
    };

    if (argc < 2) {
        for (int i = 0; help[i]; i++)
            _ftprintf_s(stdout, _T("%s\n"), help[i]);
    }
    else {
        for (int i = 0; help[i]; i++)
            _tMyPrintf(_T("%s\r\n"), help[i]);
    }
}

extern int ParseCmd(int argc, TCHAR **argv, CCaption2AssParameter *param)
{
    if (argc < 2) {
ERROR_PARAM:
        usage(argc);
        return -1;
    }

    // Refer parameters.
    pid_information_t *pi = param->get_pid_information();
    cli_parameter_t   *cp = param->get_cli_parameter();
    size_t string_length  = param->string_length;

    // Set up the default value.
    cp->detectLength = 300 * 10000;
    _tcscpy_s(cp->ass_type, string_length, _T("Default"));

    // Parse args.
    for (int i = 1; i< argc; i++) {
        if (_tcsicmp(argv[i], _T("-PMT_PID")) == 0) {
            i++;
            if (i > argc)
                goto ERROR_PARAM;
            if (_stscanf_s(argv[i], _T("%x"), &(pi->PMTPid)) <= 0)
                goto ERROR_PARAM;
        } else if (_tcsicmp(argv[i], _T("-format")) == 0) {
            i++;
            if (i > argc)
                goto ERROR_PARAM;
            if (_tcsicmp(argv[i], _T("srt")) == 0)
                cp->format = FORMAT_SRT;
            else if (_tcsicmp(argv[i], _T("ass")) == 0)
                cp->format = FORMAT_ASS;
            else if (_tcsicmp(argv[i], _T("taw")) == 0)
                cp->format = FORMAT_TAW;
            else if (_tcsicmp(argv[i], _T("dual")) == 0)
                cp->format = FORMAT_DUAL;
            else
                goto ERROR_PARAM;
        } else if (_tcsicmp(argv[i], _T("-i")) == 0) {
            i++;
            if (i > argc)
                goto ERROR_PARAM;
            _tcscpy_s(cp->FileName, string_length, argv[i]);
            
        } else if (_tcsicmp(argv[i], _T("-o")) == 0) {
            i++;
            if (i > argc)
                goto ERROR_PARAM;
            _tcscpy_s(cp->TargetFileName, string_length, argv[i]);
        } else if (_tcsicmp(argv[i], _T("-delay")) == 0) {
            i++;
            if (i > argc)
                goto ERROR_PARAM;
            if (_stscanf_s(argv[i], _T("%d"), &(cp->DelayTime)) <= 0)
                goto ERROR_PARAM;
        } else if (_tcsicmp(argv[i], _T("-asstype")) == 0) {
            i++;
            if (i > argc)
                goto ERROR_PARAM;
            _tcscpy_s(cp->ass_type, string_length, argv[i]);
        } else if (_tcsicmp(argv[i], _T("-log")) == 0)
            cp->LogMode = TRUE;
        else if (_tcsicmp(argv[i], _T("-keepinterval")) == 0)
            cp->keepInterval = TRUE;
        else if (_tcsicmp(argv[i], _T("-srtornament")) == 0)
            cp->srtornament = TRUE;
        else if (_tcsicmp(argv[i], _T("-hlc")) == 0) {
            i++;
            if (i > argc)
                goto ERROR_PARAM;
            if (_tcsicmp(argv[i], _T("kigou")) == 0)
                cp->HLCmode = HLC_kigou;
            else if (_tcsicmp(argv[i], _T("box")) == 0)
                cp->HLCmode = HLC_box;
            else if (_tcsicmp(argv[i], _T("draw")) == 0)
                cp->HLCmode = HLC_draw;
            else
                goto ERROR_PARAM;
        } else if (_tcsicmp(argv[i], _T("-norubi")) == 0)
            cp->norubi = TRUE;
		else if (_tcsicmp(argv[i], _T("-center")) == 0)
            cp->alignCenter = TRUE;
        else if (_tcsicmp(argv[i], _T("-detect_length")) == 0) {
            i++;
            if (i > argc)
                goto ERROR_PARAM;
            if (_stscanf_s(argv[i], _T("%d"), &cp->detectLength) < 0)
                goto ERROR_PARAM;
            cp->detectLength *= 10000;
        } else if (_tcsicmp(cp->FileName, _T("")) == 0)
            _tcscpy_s(cp->FileName, string_length, argv[i]);
        else if (_tcsicmp(cp->TargetFileName, _T("")) == 0)
            _tcscpy_s(cp->TargetFileName, string_length, argv[i]);
        else
            goto ERROR_PARAM;
    }
    return 0;
}

extern void _tMyPrintf(IN  LPCTSTR tracemsg, ...)
{
    TCHAR buf[MAX_PATH + 2048] = { 0 };
    HRESULT ret;

    __try {
        va_list ptr;
        va_start(ptr, tracemsg);

        ret = StringCchVPrintf(
            buf,
            MAX_PATH + 2048,
            tracemsg,
            ptr
            );

        if (ret == S_OK) {
            DWORD ws;
            WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, (DWORD)_tcslen(buf), &ws, NULL);
        }
    }
    __finally {
        ;
    }

    return;
}
