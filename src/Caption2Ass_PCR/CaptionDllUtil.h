//------------------------------------------------------------------------------
// CaptionDllUtil.h
//------------------------------------------------------------------------------
#ifndef __CAPTION_DLL_UTIL_H__
#define __CAPTION_DLL_UTIL_H__

#include "Caption.h"

#include <string>
#include <vector>

using namespace std;

typedef struct _CLUT_DAT {
    unsigned char ucR;
    unsigned char ucG;
    unsigned char ucB;
    unsigned char ucAlpha;
} CLUT_DAT;

typedef struct _LANG_TAG_INFO {
    unsigned char ucLangTag;
    unsigned char ucDMF;
    unsigned char ucDC;
    char szISOLangCode[4];
    unsigned char ucFormat;
    unsigned char ucTCS;
    unsigned char ucRollupMode;
    _LANG_TAG_INFO & operator= (const _LANG_TAG_INFO & o) {
        ucLangTag=o.ucLangTag;
        ucDMF = o.ucDMF;
        ucDC = o.ucDC;
        memcpy(szISOLangCode, o.szISOLangCode, 4 );
        ucFormat = o.ucFormat;
        ucTCS = o.ucTCS;
        ucRollupMode = o.ucRollupMode;
        return *this;
    };
} LANG_TAG_INFO;

typedef enum {
    STR_SMALL = 0,  //SSZ
    STR_MEDIUM   ,  //MSZ
    STR_NORMAL   ,  //NSZ
    STR_MICRO    ,  //SZX 0x60
    STR_HIGH_W   ,  //SZX 0x41
    STR_WIDTH_W  ,  //SZX 0x44
    STR_W        ,  //SZX 0x45
    STR_SPECIAL_1,  //SZX 0x6B
    STR_SPECIAL_2,  //SZX 0x64
} STRING_SIZE;

typedef struct _CAPTION_CHAR_DATA {
    string strDecode;
    STRING_SIZE emCharSizeMode;

    CLUT_DAT stCharColor;
    CLUT_DAT stBackColor;
    CLUT_DAT stRasterColor;

    BOOL bUnderLine;
    BOOL bShadow;
    BOOL bBold;
    BOOL bItalic;
    BYTE bFlushMode;
    BYTE bHLC;  //must ignore low 4bits

    WORD wCharW;
    WORD wCharH;
    WORD wCharHInterval;
    WORD wCharVInterval;
    _CAPTION_CHAR_DATA & operator= (const _CAPTION_CHAR_DATA & o) {
        strDecode=o.strDecode;
        emCharSizeMode = o.emCharSizeMode;
        stCharColor = o.stCharColor;
        stBackColor = o.stBackColor;
        stRasterColor = o.stRasterColor;
        bUnderLine = o.bUnderLine;
        bShadow = o.bShadow;
        bBold = o.bBold;
        bItalic = o.bItalic;
        bFlushMode = o.bFlushMode;
        bHLC = o.bHLC;
        wCharW = o.wCharH;
        wCharHInterval = o.wCharHInterval;
        wCharVInterval = o.wCharVInterval;
        return *this;
    };
} CAPTION_CHAR_DATA;

typedef struct _CAPTION_DATA {
    BOOL bClear;
    WORD wSWFMode;
    WORD wClientX;
    WORD wClientY;
    WORD wClientW;
    WORD wClientH;
    WORD wPosX;
    WORD wPosY;
    vector<CAPTION_CHAR_DATA> CharList;
    DWORD dwWaitTime;

    _CAPTION_DATA & operator= (const _CAPTION_DATA & o) {
        bClear=o.bClear;
        wSWFMode = o.wSWFMode;
        wClientX = o.wClientX;
        wClientY = o.wClientY;
        wClientW = o.wClientW;
        wClientH = o.wClientH;
        wPosX = o.wPosX;
        wPosY = o.wPosY;
        CharList = o.CharList;
        dwWaitTime = o.dwWaitTime;
        return *this;
    };
} CAPTION_DATA;

class CCaptionDllUtil
{
public:
    CCaptionDllUtil(void);
    ~CCaptionDllUtil(void);

    DWORD Initialize(void);
    BOOL CheckUNICODE(void);
    DWORD InitializeUNICODE(void);
    DWORD UnInitialize(void);
    DWORD AddTSPacket(BYTE *pbPacket);
    DWORD Clear(void);
    DWORD GetTagInfo(LANG_TAG_INFO_DLL **ppList, DWORD *pdwListCount);
    DWORD GetTagInfo(vector<LANG_TAG_INFO> *pList);
    DWORD GetCaptionData(unsigned char ucLangTag, CAPTION_DATA_DLL **ppList, DWORD *pdwListCount);
    DWORD GetCaptionData(unsigned char ucLangTag, vector<CAPTION_DATA> *pList);

protected:
    HMODULE m_hModule;

    InitializeCP pfnInitializeCP;
    InitializeUNICODECP pfnInitializeUNICODE;
    UnInitializeCP pfnUnInitializeCP;
    AddTSPacketCP pfnAddTSPacketCP;
    ClearCP pfnClearCP;
    GetTagInfoCP pfnGetTagInfoCP;
    GetCaptionDataCP pfnGetCaptionDataCP;

protected:
    BOOL LoadDll(void);
    BOOL UnLoadDll(void);
};

#endif // __CAPTION_DLL_UTIL_H__
