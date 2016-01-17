//------------------------------------------------------------------------------
// ARIBGaiji.h
//------------------------------------------------------------------------------
#ifndef __ARIB_GAIJI_H__
#define __ARIB_GAIJI_H__

#include <string>

#ifdef GLOBAL
#define EXTERN
#else
#define EXTERN extern
#endif

// ARIBの追加記号 ＆ 追加漢字のテーブル定義
// 実体は、「CaptionMain.cpp」で宣言

#define ARIB_MAX        495
#define ARIB_MAX2       137

typedef struct _GAIJI_TABLE {
    string usARIB8;
    string strChar;
} GAIJI_TABLE;

EXTERN GAIJI_TABLE GaijiTable[ARIB_MAX];

EXTERN GAIJI_TABLE GaijiTbl2[ARIB_MAX2];

EXTERN BOOL m_bUnicode;

#endif // __ARIB_GAIJI_H__
