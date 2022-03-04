#ifndef __MAY_EC_H__
#define __MAY_EC_H__

#include <MYLIB_IoLib.h>
#include <MYLIB_StringLib.h>

#include <Library/UefiLib.h>

#define EC_Cmd 0x60
#define EC_Sta 0X64
#define ACPI_Cmd 0x62
#define ACPI_Sta 0x66

#define TIMEOUT 0x1f4

VOID
EFIAPI
ReadWriteEC (UINTN port, UINT8 cmd, UINT8 dt);

#endif