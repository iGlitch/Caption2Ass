//------------------------------------------------------------------------------
// CaptionDef.h
//------------------------------------------------------------------------------
#ifndef __CAPTION_DEF_H__
#define __CAPTION_DEF_H__

#define ERR_FALSE   FALSE   //汎用エラー
#define NO_ERR      TRUE    //成功

#define ERR_INIT        10
#define ERR_NOT_INIT    11
#define ERR_SIZE        12

#define ERR_NEED_NEXT_PACKET    13  //次のTSパケット入れないと解析できない
#define ERR_CAN_NOT_ANALYZ      14  //本当にTSパケット？解析不可能
#define ERR_NOT_FIRST           15  //最初のTSパケット未入力
#define ERR_INVALID_PACKET      16  //本当にTSパケット？パケット飛んで壊れてるかも

#define CHANGE_VERSION      20
#define NO_ERR_TAG_INFO     21
#define NO_ERR_CAPTION      22

#define SAFE_DELETE(p)       { if (p) { delete (p);   (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p) = NULL; } }

#define STRING_BUFFER_SIZE      (1024)

typedef struct _CLUT_DAT_DLL {
    unsigned char ucR;
    unsigned char ucG;
    unsigned char ucB;
    unsigned char ucAlpha;
} CLUT_DAT_DLL;

typedef struct _CAPTION_CHAR_DATA_DLL {
    char *pszDecode;
    DWORD wCharSizeMode;

    CLUT_DAT_DLL stCharColor;
    CLUT_DAT_DLL stBackColor;
    CLUT_DAT_DLL stRasterColor;

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
} CAPTION_CHAR_DATA_DLL;

typedef struct _CAPTION_DATA_DLL {
    BOOL bClear;
    WORD wSWFMode;
    WORD wClientX;
    WORD wClientY;
    WORD wClientW;
    WORD wClientH;
    WORD wPosX;
    WORD wPosY;
    DWORD dwListCount;
    CAPTION_CHAR_DATA_DLL *pstCharList;
    DWORD dwWaitTime;
} CAPTION_DATA_DLL;

typedef struct _LANG_TAG_INFO_DLL {
    unsigned char ucLangTag;
    unsigned char ucDMF;
    unsigned char ucDC;
    char szISOLangCode[4];
    unsigned char ucFormat;
    unsigned char ucTCS;
    unsigned char ucRollupMode;
} LANG_TAG_INFO_DLL;

#endif // __CAPTION_DEF_H__
