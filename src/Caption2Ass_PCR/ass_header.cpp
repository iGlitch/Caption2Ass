//------------------------------------------------------------------------------
// ass_header.cpp
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ass_header.h"
#include "Caption2Ass_PCR.h"

extern void assHeaderWrite(FILE *fp, ass_setting_t *as)
{
    fprintf(fp, "[Script Info]\r\n");
    if(strlen(as->Comment1) > 0 ) fprintf(fp, "; %s\r\n", as->Comment1);
    if(strlen(as->Comment2) > 0 ) fprintf(fp, "; %s\r\n", as->Comment2);
    if(strlen(as->Comment3) > 0 ) fprintf(fp, "; %s\r\n", as->Comment3);
    fprintf(fp, "%s", ASS_HEADER1);
	if(as->PlayResX != 0)
    fprintf(fp, "PlayResX: %d\r\n", as->PlayResX);
	if(as->PlayResY != 0)
    fprintf(fp, "PlayResY: %d\r\n", as->PlayResY);
    fprintf(fp, "%s", ASS_HEADER2);
    fprintf(fp, "Style: %s,%s,%d,%s\r\n", "Default", as->DefaultFontname, as->DefaultFontsize, as->DefaultStyle);
    fprintf(fp, "Style: %s,%s,%d,%s\r\n", "Box", as->BoxFontname, as->BoxFontsize, as->BoxStyle);
    fprintf(fp, "Style: %s,%s,%d,%s\r\n//\r\n", "Rubi", as->RubiFontname, as->RubiFontsize, as->RubiStyle);
    fprintf(fp, "%s", ASS_HEADER3);

    return;
}
