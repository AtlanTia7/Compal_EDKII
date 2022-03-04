#ifndef __MAY_STRING_H__
#define __MAY_STRING_H__

#include <Uefi.h>
#include <Library/UefiLib.h>

#include <Library/MemoryAllocationLib.h>

CHAR16 *
ManufacturerAbbrev(UINT16 *ManufactureName);

UINT8
EFIAPI
CheckBit(
	UINT8 Input,
	UINT8  Num
);

CHAR16*
ShowAsciiStr(UINT8 data);

CHAR16 *
ASCII_to_UCS2(const char *s, UINTN len);

#define EDID_COMBINE_HI_8LO( hi, lo )     ((((unsigned)hi) << 8) | (unsigned)lo )

#endif
