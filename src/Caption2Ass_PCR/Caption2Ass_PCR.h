//------------------------------------------------------------------------------
// Caption2Ass_PCR.h
//------------------------------------------------------------------------------
#ifndef __CAPTION2ASS_PCR_H__
#define __CAPTION2ASS_PCR_H__

#include <tchar.h>

#include "Caption2AssParameter.h"

extern void assHeaderWrite(FILE *fp, ass_setting_t *as);
extern int IniFileRead(TCHAR *ass_type, ass_setting_t *as);
#ifdef _DEBUG
extern int load_debug(int *argc_p, TCHAR ***argv_p);
extern void unload_debug(int argc, TCHAR **argv);
#endif

typedef enum {
    FORMAT_INVALID = 0,
    FORMAT_LOG     = 0,
    FORMAT_SRT     = 1,
    FORMAT_ASS     = 2,
    FORMAT_TAW     = 3,
    FORMAT_DUAL    = 4,
    FORMAT_MAX
} format_type;

enum {
    HLC_INVALID = 0,
    HLC_kigou   = 1,
    HLC_box     = 2,
    HLC_draw    = 3
};

#define TIMESTAMP_INVALID_VALUE     (-1LL)

#endif // __CAPTION2ASS_PCR_H__
