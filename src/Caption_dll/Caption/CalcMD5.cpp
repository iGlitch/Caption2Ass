//------------------------------------------------------------------------------
// CalcMD5.cpp
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "CalcMD5.h"

BOOL CalcMD5FromDRCSPattern(BYTE *pbHash, char *pcHashStr, const BYTE *pbPatternData, const DWORD dwDataLen)
{
    HCRYPTPROV hProv = NULL;
    HCRYPTHASH hHash = NULL;
    BOOL bRet = FALSE;
    if (!::CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        hProv = NULL;
        goto EXIT;
    }
    if (!::CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        hHash = NULL;
        goto EXIT;
    }
    if (!::CryptHashData(hHash, pbPatternData, dwDataLen, 0))
        goto EXIT;
    DWORD dwHashLen = 16;
    if (!::CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0))
        goto EXIT;
    char MD5tmp[10];
    for (DWORD i = 0; i < dwHashLen; i++) {
        sprintf_s(MD5tmp, 10, "%02X", pbHash[i]);
        strcat_s(pcHashStr, MD5_HASH_HEX_LENGTH + 1, MD5tmp);
    }
    bRet = TRUE;

EXIT:
    if (hHash)
        ::CryptDestroyHash(hHash);
    if (hProv)
        ::CryptReleaseContext(hProv, 0);
    return bRet;
}
