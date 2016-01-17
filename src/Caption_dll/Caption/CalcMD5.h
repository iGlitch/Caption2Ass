//------------------------------------------------------------------------------
// CalcMD5.h
//------------------------------------------------------------------------------
#ifndef __CALC_MD5_H__
#define __CALC_MD5_H__

#define MD5_HASH_HEX_LENGTH     32

extern BOOL CalcMD5FromDRCSPattern(BYTE *pbHash, char *pcHashStr, const BYTE *pbPatternData, const DWORD dwDataLen);

#endif // __CALC_MD5_H__
