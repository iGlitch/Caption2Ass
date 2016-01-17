//------------------------------------------------------------------------------
// ARIB8CharDecode.h
//------------------------------------------------------------------------------
#ifndef __ARIB8CHAR_DECODE_H__
#define __ARIB8CHAR_DECODE_H__

#include <string>
#include <vector>
#include <map>
using namespace std;

extern map<string, string> dicHash_Char_map;
extern map<WORD, string> dicCharcode_Char_map;

//文字符号集合
//Gセット
#define MF_JIS_KANJI1   0x39    //JIS互換漢字1面
#define MF_JIS_KANJI2   0x3A    //JIS互換漢字2面
#define MF_KIGOU        0x3B    //追加記号
#define MF_ASCII        0x4A    //英数
#define MF_HIRA         0x30    //平仮名
#define MF_KANA         0x31    //片仮名
#define MF_KANJI        0x42    //漢字
#define MF_MOSAIC_A     0x32    //モザイクA
#define MF_MOSAIC_B     0x33    //モザイクB
#define MF_MOSAIC_C     0x34    //モザイクC
#define MF_MOSAIC_D     0x35    //モザイクD
#define MF_PROP_ASCII   0x36    //プロポーショナル英数
#define MF_PROP_HIRA    0x37    //プロポーショナル平仮名
#define MF_PROP_KANA    0x38    //プロポーショナル片仮名
#define MF_JISX_KANA    0x49    //JIX X0201片仮名
//DRCS
#define MF_DRCS_0   0x40    //DRCS-0
#define MF_DRCS_1   0x41    //DRCS-1
#define MF_DRCS_2   0x42    //DRCS-2
#define MF_DRCS_3   0x43    //DRCS-3
#define MF_DRCS_4   0x44    //DRCS-4
#define MF_DRCS_5   0x45    //DRCS-5
#define MF_DRCS_6   0x46    //DRCS-6
#define MF_DRCS_7   0x47    //DRCS-7
#define MF_DRCS_8   0x48    //DRCS-8
#define MF_DRCS_9   0x49    //DRCS-9
#define MF_DRCS_10  0x4A    //DRCS-10
#define MF_DRCS_11  0x4B    //DRCS-11
#define MF_DRCS_12  0x4C    //DRCS-12
#define MF_DRCS_13  0x4D    //DRCS-13
#define MF_DRCS_14  0x4E    //DRCS-14
#define MF_DRCS_15  0x4F    //DRCS-15
#define MF_MACRO    0x70    //マクロ

//符号集合の分類
#define MF_MODE_G       1   //Gセット
#define MF_MODE_DRCS    2   //DRCS
#define MF_MODE_OTHER   3   //その他

//文字サイズ
typedef enum{
    STR_SMALL = 0,  //SSZ
    STR_MEDIUM,     //MSZ
    STR_NORMAL,     //NSZ
    STR_MICRO,      //SZX 0x60
    STR_HIGH_W,     //SZX 0x41
    STR_WIDTH_W,    //SZX 0x44
    STR_W,          //SZX 0x45
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
    BYTE bHLC; //must ignore low 4bits

    WORD wCharW;
    WORD wCharH;
    WORD wCharHInterval;
    WORD wCharVInterval;
    //=オペレーターの処理
    _CAPTION_CHAR_DATA & operator= (const _CAPTION_CHAR_DATA & o) {
        strDecode = o.strDecode;
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
    //=オペレーターの処理
    _CAPTION_DATA & operator= (const _CAPTION_DATA & o) {
        bClear = o.bClear;
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
//DRCS図形の縦横最大サイズ(運用規定より)
#define DRCS_SIZE_MAX 36

struct DRCS_PATTERN {
    WORD wDRCCode;
    WORD wGradation;
    BITMAPINFOHEADER bmiHeader;
    BYTE bBitmap[(DRCS_SIZE_MAX * 4 + 31) / 32 * 4 * DRCS_SIZE_MAX];
    DRCS_PATTERN() {}
};

class CARIB8CharDecode
{
public:
    CARIB8CharDecode(void);
    ~CARIB8CharDecode(void);

    //字幕を想定したSJISへの変換
    BOOL Caption(const BYTE *pbSrc, DWORD dwSrcSize, vector<CAPTION_DATA> *pCaptionList);
    //dllのパスの取得
    string GetAppPath(void)
    {
        CHAR wkPath[_MAX_PATH], wkDrive[_MAX_DRIVE], wkDir[_MAX_DIR], wkFileName[_MAX_FNAME], wkExt[_MAX_EXT];
        DWORD dwRet = GetModuleFileNameA(NULL, wkPath, sizeof(wkPath));
        if (dwRet == 0) {
            //エラー処理など(省略)
        }
        _splitpath_s(wkPath, wkDrive, _MAX_DRIVE, wkDir, _MAX_DIR, wkFileName, _MAX_FNAME, wkExt, _MAX_EXT);
        string strAppPath = "";
        strAppPath += wkDrive;
        strAppPath += wkDir;
        return strAppPath;
    }
    BOOL CARIB8CharDecode::DRCSHeaderparse(const BYTE *pbSrc, DWORD dwSrcSize, BOOL bDRCS_0);

protected:
    typedef struct _MF_MODE {
        int iMF; //文字符号集合
        int iMode; //符号集合の分類
        int iByte; //読み込みバイト数
        //=オペレーターの処理
        _MF_MODE & operator= (const _MF_MODE & o) {
            iMF = o.iMF;
            iMode = o.iMode;
            iByte = o.iByte;
            return *this;
        }
    } MF_MODE;

    BOOL m_bPSI;

    MF_MODE  m_G0;
    MF_MODE  m_G1;
    MF_MODE  m_G2;
    MF_MODE  m_G3;
    MF_MODE *m_GL;
    MF_MODE *m_GR;

    BOOL m_bModGL;

    //デコードした文字列
    string m_strDecode;
    //文字サイズ
    STRING_SIZE m_emStrSize;

    //CLUTのインデックス
    BYTE m_bCharColorIndex;
    BYTE m_bBackColorIndex;
    BYTE m_bRasterColorIndex;
    BYTE m_bDefPalette;

    BOOL m_bUnderLine;
    BOOL m_bShadow;
    BOOL m_bBold;
    BOOL m_bItalic;
    BYTE m_bFlushMode;
    BYTE m_bHLC;
    //map<string, string> dicHash_Char_map;
    //map<int, string> dicCharcode_Char_map;
    WORD m_wMaxPosX;
    WORD m_wTmpPosX;
    // RPC対応
    BOOL m_bRPC;
    WORD m_wRPC;
    // DRCSとARIBの代用文字用iniファィルのUnicode
//  BOOL m_bUnicode;
    BOOL m_bGaiji;

    //表示書式
    WORD m_wSWFMode;
    WORD m_wClientX;
    WORD m_wClientY;
    WORD m_wClientW;
    WORD m_wClientH;
    WORD m_wPosX;
    WORD m_wPosY;
    WORD m_wCharW;
    WORD m_wCharH;
    WORD m_wCharHInterval;
    WORD m_wCharVInterval;
    WORD m_wMaxChar;

    DWORD m_dwWaitTime;

    vector<CAPTION_DATA> *m_pCaptionList;
protected:
    void InitCaption(void);
    BOOL Analyze(const BYTE *pbSrc, DWORD dwSrcSize, DWORD *pdwReadSize);

    BOOL IsSmallCharMode(void);
    BOOL IsChgPos(void);
    void CreateCaptionData(CAPTION_DATA *pItem);
    void CreateCaptionCharData(CAPTION_CHAR_DATA *pItem);
    void CheckModify(void);

    //制御符号
    BOOL C0(const BYTE *pbSrc, DWORD *pdwReadSize);
    BOOL C1(const BYTE *pbSrc, DWORD *pdwReadSize);
    BOOL GL(const BYTE *pbSrc, DWORD *pdwReadSize);
    BOOL GR(const BYTE *pbSrc, DWORD *pdwReadSize);
    //シングルシフト
    BOOL SS2(const BYTE *pbSrc, DWORD *pdwReadSize);
    BOOL SS3(const BYTE *pbSrc, DWORD *pdwReadSize);
    //エスケープシーケンス
    BOOL ESC(const BYTE *pbSrc, DWORD *pdwReadSize);
    //２バイト文字変換
    BOOL ToSJIS(const BYTE bFirst, const BYTE bSecond);
    BOOL ToCustomFont(const BYTE bFirst, const BYTE bSecond);

    BOOL CSI(const BYTE *pbSrc, DWORD *pdwReadSize);

    BOOL AddToString(const char *cDec, BOOL m_bGaiji);

public:
    string Get_dicCharcode_Char(WORD DRCSCharCode)
    {
        string strRet = "NF";
        map<WORD, string>::iterator iter = dicCharcode_Char_map.find(DRCSCharCode);
        if (iter != dicCharcode_Char_map.end()) {
            strRet = iter->second;
        }
        return strRet;
    }
    void Add_dicCharcode_Char(WORD DRCSCharCode, string gaijichar)
    {
        dicCharcode_Char_map.insert(std::make_pair(DRCSCharCode, map<WORD, string>::mapped_type())).first->second = gaijichar;
    }
    string Get_dicHash_Char(string hash)
    {
        string strRet = "NF";
        map<string, string>::iterator iter = dicHash_Char_map.find(hash);
        if (iter != dicHash_Char_map.end()) {
            strRet = iter->second;
        }
        return strRet;
    }
    VOID Add_dicHash_Char(string hash, string gaijichar)
    {
        dicHash_Char_map.insert(map<string, string>::value_type(hash, gaijichar));
    }
};

#endif // __ARIB8CHAR_DECODE_H__
