//------------------------------------------------------------------------------
// IniFile.h
//------------------------------------------------------------------------------
#ifndef __INI_FILE_H__
#define __INI_FILE_H__

//ref class IniFile
class IniFile
{

public:
    BOOL IniFile::ReadIni(void);
    BOOL IniFile::ReadIniARIB(void);
    BOOL IniFile::ReadIniUNICODE(void);
    BOOL IniFile::ReadIniARIBUNICODE(void);

};

#endif // __INI_FILE_H__
