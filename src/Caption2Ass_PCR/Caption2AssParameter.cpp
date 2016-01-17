//------------------------------------------------------------------------------
// Caption2AssParameter.cpp
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "CaptionDef.h"
#include "Caption2Ass_PCR.h"

CCaption2AssParameter::CCaption2AssParameter(void)
 : string_length(MAX_PATH)
{
    Initialize();
}

CCaption2AssParameter::CCaption2AssParameter(size_t string_length)
 : string_length(string_length)
{
    Initialize();
}

CCaption2AssParameter::~CCaption2AssParameter(void)
{
    Free();
}

void CCaption2AssParameter::Initialize(void)
{
    pid_information_t *pi = &pid_information;
    cli_parameter_t   *cp = &cli_parameter;
    ass_setting_t     *as = &ass_setting;

    // Initialize
    memset(pi, 0, sizeof(pid_information_t));
    memset(cp, 0, sizeof(cli_parameter_t));
    memset(as, 0, sizeof(ass_setting_t));

    // Setup default settings.
    cp->format  = FORMAT_ASS;
    cp->HLCmode = HLC_kigou;
    if (this->string_length < MAX_PATH)
        this->string_length = MAX_PATH;
}

int CCaption2AssParameter::Allocate(size_t string_length)
{
    cli_parameter_t *cp = &cli_parameter;
    ass_setting_t   *as = &ass_setting;

    if (this->string_length < string_length)
        this->string_length = string_length;

    // Allocate string buffers.
    TCHAR **string_list[] = {
        // cli_parameter_t
        &(cp->ass_type),
        &(cp->FileName),
        &(cp->TargetFileName),
        &(cp->LogFileName),
        // ass_setting_t
        // last(null)
        NULL
    };
    for (int i = 0; string_list[i]; i++) {
        *(string_list[i]) = new TCHAR[this->string_length];
        if (!*(string_list[i]))
            goto fail;
        memset(*(string_list[i]), 0, sizeof(TCHAR) * this->string_length);
    }

	// Allocate char buffers.
   CHAR **utf8str_list[] = {
        // cli_parameter_t
        // ass_setting_t
        &(as->Comment1),
        &(as->Comment2),
        &(as->Comment3),
        &(as->DefaultFontname),
        &(as->DefaultStyle),
        &(as->BoxFontname),
        &(as->BoxStyle),
        &(as->RubiFontname),
        &(as->RubiStyle),
        // last(null)
        NULL
    };
    for (int i = 0; utf8str_list[i]; i++) {
        *(utf8str_list[i]) = new CHAR[this->string_length];
        if (!*(utf8str_list[i]))
            goto fail;
        memset(*(utf8str_list[i]), 0, sizeof(CHAR) * this->string_length);
    }

    return 0;

fail:
    Free();
    return -1;
}

void CCaption2AssParameter::Free(void)
{
    cli_parameter_t *cp = &cli_parameter;
    ass_setting_t   *as = &ass_setting;

    // Free string buffers.
    TCHAR **string_list[] = {
        // cli_parameter_t
        &(cp->ass_type),
        &(cp->FileName),
        &(cp->TargetFileName),
        &(cp->LogFileName),
        // ass_setting_t
        // last(null)
        NULL
    };
		// Allocate char buffers.
   CHAR **utf8str_list[] = {
        // cli_parameter_t
        // ass_setting_t
        &(as->Comment1),
        &(as->Comment2),
        &(as->Comment3),
        &(as->DefaultFontname),
        &(as->DefaultStyle),
        &(as->BoxFontname),
        &(as->BoxStyle),
        &(as->RubiFontname),
        &(as->RubiStyle),
        // last(null)
        NULL
    };
    for (int i = 0; string_list[i]; i++)
        SAFE_DELETE_ARRAY(*(string_list[i]));
    for (int i = 0; utf8str_list[i]; i++)
        SAFE_DELETE_ARRAY(*(utf8str_list[i]));
}
