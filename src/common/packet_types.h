//------------------------------------------------------------------------------
// packet_types.h
//------------------------------------------------------------------------------
#ifndef __PACKET_TYPES_H__
#define __PACKET_TYPES_H__

#include <windows.h>

typedef struct Packet_Header {
    BYTE    Sync;
    BYTE    TsErr;
    BYTE    PayloadStartFlag;
    BYTE    Priority;
    WORD    PID;
    BYTE    Scramble;
    BYTE    AdaptFlag;
    BYTE    PayloadFlag;
    BYTE    Counter;
} Packet_Header;

#pragma pack(push, 1)

typedef struct _Packet_Header {
    BYTE    Sync;
    WORD    PID;
    BYTE    Counter;
} _Packet_Header;

typedef struct PMT_PID {
    WORD        program_id;     // 0-> PMT_PID = NetwokPID
    WORD        PID;            // &0x1FFF
} PMT_PID;

typedef struct PAT_HEADER {
    BYTE        table_id;       //0x00
    WORD        section_length; // &0x0FFF
    WORD        transport_id;
    BYTE        version;        //version>>5 &0x1F
    BYTE        section_number;
    BYTE        last_section_number;
    PMT_PID     PMT_Array[1];
} PAT_HEADER;

typedef struct PMT_HEADER {
    BYTE        table_id;
    WORD        section_length; // &0x0FFF
    WORD        program_id;
    BYTE        version;        //version>>5 &0x1F
    BYTE        section_number;
    BYTE        last_section_number;
    WORD        pcrpid;         //13bit & 0x1fff
    WORD        program_info_length;    // &0x0FFF
    /*
    BYTE program_info[program_info_length];
    desc_records {
        BYTE    StreamTypeID;
        WORD    EsPID;              // +1,2
        WORD    DescLen;            // +3,4
        BYTE    Desc[DescLen]
    }
    */
} PMT_HEADER;

typedef struct PMT_PID_Desc {
    BYTE    StreamTypeID;
    WORD    EsPID;                  // +1,2
    WORD    DescLen;                // +3,4
    BYTE    descriptor_tag;
    BYTE    descriptor_length;
    BYTE    component_tag;
} PMT_PI_Desc;

#pragma pack(pop)

#define swap16(x) ((((WORD)(x) & 0xFF00) >> 8) | (((WORD)(x) & 0x00FF) << 8))

#endif // __PACKET_TYPES_H__
