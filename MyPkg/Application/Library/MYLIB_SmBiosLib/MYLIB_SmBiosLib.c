
#include <MYLIB_SmBiosLib.h>

CHAR8 *
GetSmbiosString (
  IN SMBIOS_STRUCTURE_POINTER  SmbiosTable,
  IN SMBIOS_TABLE_STRING       String
  )
{
  CHAR8      *AString;
  UINT8      Index;

  Index = 1;
  AString = (CHAR8 *)(SmbiosTable.Raw + SmbiosTable.Hdr->Length);
  while (Index != String) {
    while (*AString != 0) {
      AString ++;
    }
    AString ++;
    if (*AString == 0) {
      return AString;
    }
    Index ++;
  }

  return AString;
}


