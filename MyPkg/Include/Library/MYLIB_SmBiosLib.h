#ifndef __MAY__SMBIOSLIB__H__
#define __MAY__SMBIOSLIB__H__

#include <Uefi.h>
#include <Base.h>
#include <IndustryStandard/SmBios.h>

#include <Protocol/Smbios.h>

CHAR8 *
GetSmbiosString (
  IN SMBIOS_STRUCTURE_POINTER  SmbiosTable,
  IN SMBIOS_TABLE_STRING       String
  );

#endif

