//------------------------------------------------------------------------------
// CaptionMain.h
//------------------------------------------------------------------------------
#ifndef __CAPTION_MAIN_H__
#define __CAPTION_MAIN_H__

#include "CaptionDef.h"

#define RESET_JD_SYSTEMTIME(p)   { if (p) { *p.wYear = 1991; *p.wMonth = 12; *p.wDay = 31; *p.wHour = 0; *p.wMinute = 0; *p.wSecond = 0; *p.wMilliseconds = 0; *p.wDayOfWeek = 0; } }
#define RESET_MJD_SYSTEMTIME(p)  { if (p) { *p.wYear = 1858; *p.wMonth = 11; *p.wDay = 17; *p.wHour = 0; *p.wMinute = 0; *p.wSecond = 0; *p.wMilliseconds = 0; *p.wDayOfWeek = 0; } }

class CCaptionMain
{
public:
    typedef struct _LANG_TAG_INFO {
        unsigned char ucLangTag;
        unsigned char ucDMF;
        unsigned char ucDC;
        char szISOLangCode[4];
        unsigned char ucFormat;
        unsigned char ucTCS;
        unsigned char ucRollupMode;
        //=オペレーターの処理
        _LANG_TAG_INFO & operator= (const _LANG_TAG_INFO & o) {
            ucLangTag = o.ucLangTag;
            ucDMF = o.ucDMF;
            ucDC = o.ucDC;
            memcpy(szISOLangCode, o.szISOLangCode, 4);
            ucFormat = o.ucFormat;
            ucTCS = o.ucTCS;
            ucRollupMode = o.ucRollupMode;
            return *this;
        };
    } LANG_TAG_INFO;

public:
    CCaptionMain(BOOL bUNICODE);
    ~CCaptionMain(void);

    DWORD AddTSPacket(BYTE *pbPacket);
    DWORD Clear(void);

    DWORD GetTagInfo(LANG_TAG_INFO_DLL **ppList, DWORD *pdwListCount);
    DWORD GetCaptionData(unsigned char ucLangTag, CAPTION_DATA_DLL **ppList, DWORD *pdwListCount);

protected:
    typedef struct _PAYLOAD_DATA {
        BYTE bBuff[188];
        WORD wSize;
    } PAYLOAD_DATA;
    vector<PAYLOAD_DATA*> m_PayloadList;

    map<WORD, LANG_TAG_INFO> m_LangTagList;

    typedef struct _CAPTION_LIST {
        WORD wGroupID;
        vector<CAPTION_DATA> CaptionList;
    } CAPTION_LIST;
    map<WORD, CAPTION_LIST> m_CaptionMap;

    unsigned char m_ucVersion;

    int m_iLastCounter;
    BOOL m_bAnalyz;
    DWORD m_dwNowReadSize;
    DWORD m_dwNeedSize;

    LANG_TAG_INFO_DLL *m_pLangList;
    DWORD m_dwLangListCount;
    CAPTION_DATA_DLL *m_pCapList;
    DWORD m_dwCapListCount;

protected:
    DWORD GetTagInfo(vector<CCaptionMain::LANG_TAG_INFO> *pList);
    DWORD GetCaptionData(unsigned char ucLangTag, vector<CAPTION_DATA> *pList);

    DWORD ParseListData(void);
    DWORD ParseCaption(BYTE *pbBuff, DWORD dwSize);
    DWORD ParseCaptionManagementData(BYTE *pbBuff, DWORD dwSize, vector<CAPTION_DATA> *pCaptionList);
    DWORD ParseCaptionData(BYTE *pbBuff, DWORD dwSize, vector<CAPTION_DATA> *pCaptionList);
    DWORD ParseUnitData(BYTE *pbBuff, DWORD dwSize, DWORD *pdwReadSize, vector<CAPTION_DATA> *pCaptionList);

    BOOL InsertCaptionList(WORD wGroupID, vector<CAPTION_DATA> *pCaptionList);
};

#endif // __CAPTION_MAIN_H__
