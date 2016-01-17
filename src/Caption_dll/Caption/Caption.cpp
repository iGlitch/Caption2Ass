//------------------------------------------------------------------------------
// Caption.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//------------------------------------------------------------------------------
#pragma warning(disable: 4100)

#include "stdafx.h"

#include "CaptionDef.h"
#include "ColorDef.h"
#include "ARIB8CharDecode.h"
#include "CaptionMain.h"
#include "Caption.h"

static CCaptionMain *g_sys = NULL;

static __inline DWORD initialize(BOOL bUNICODE)
{
    if (g_sys || (g_sys = new CCaptionMain(bUNICODE)) == NULL)
        return ERR_INIT;
    return NO_ERR;
}

static __inline void uninitialize(void)
{
    if (!g_sys)
        return;
    delete g_sys;
    g_sys = NULL;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_sys = NULL;
        break;
    case DLL_PROCESS_DETACH:
        uninitialize();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    default:
        break;
    }
    return TRUE;
}

//DLLの初期化
//戻り値：エラーコード
DWORD WINAPI InitializeCP(void)
{
    return initialize(FALSE);
}

//DLLの初期化 UNICODE対応
//戻り値：エラーコード
DWORD WINAPI InitializeUNICODE(void)
{
    return initialize(TRUE);
}

//DLLの開放
//戻り値：エラーコード
DWORD WINAPI UnInitializeCP(void)
{
    uninitialize();
    return NO_ERR;
}

DWORD WINAPI AddTSPacketCP(BYTE *pbPacket)
{
    if (!g_sys)
        return ERR_NOT_INIT;
    return g_sys->AddTSPacket(pbPacket);
}

DWORD WINAPI ClearCP(void)
{
    if (!g_sys)
        return ERR_NOT_INIT;
    return g_sys->Clear();
}

DWORD WINAPI GetTagInfoCP(LANG_TAG_INFO_DLL **ppList, DWORD *pdwListCount)
{
    if (!g_sys)
        return ERR_NOT_INIT;
    return g_sys->GetTagInfo(ppList, pdwListCount);
}

DWORD WINAPI GetCaptionDataCP(unsigned char ucLangTag, CAPTION_DATA_DLL **ppList, DWORD *pdwListCount)
{
    if (!g_sys)
        return ERR_NOT_INIT;
    return g_sys->GetCaptionData(ucLangTag, ppList, pdwListCount);
}
