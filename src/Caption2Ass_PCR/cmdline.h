//------------------------------------------------------------------------------
// cmdline.h
//------------------------------------------------------------------------------
#ifndef __CMD_LINE_H__
#define __CMD_LINE_H__

#include <stdlib.h>
#include <tchar.h>

#include "Caption2Ass_PCR.h"

extern int ParseCmd(int argc, TCHAR **argv, CCaption2AssParameter *param);
extern void _tMyPrintf(IN  LPCTSTR tracemsg, ...);

#endif // __CMD_LINE_H__
