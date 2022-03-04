#ifndef __MAY_IO_H__
#define __MAY_IO_H__

#include <Base.h>
#include <Uefi.h>

#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/UefiLib.h>

//----------------------------------------------

EFI_STATUS
EFIAPI
PciFormat
(
	UINT8  T2R,//Type to read, [2]:Byte [4]:Word [8]:DWord
	UINT32 BN,
	UINT32 DN,
	UINT32 FN
);

//----------------------------------------------

UINT32 
GetSMBusIOport();

VOID
EFIAPI
ReadSmbus
(
	UINT32 IOPort,
	UINT8  Slave,
	UINT32 Index
);

//----------------------------------------------

EFI_STATUS
EFIAPI
BankPrint
(
	IN INT8  BankChoose,//[0]:Bank0, [1]:Bank1
	IN INT8  ReadOrWrite,//[1]:Write
	IN UINT8 Write_Offset,
	IN UINT8 Write_Value
);

//----------------------------------------------

VOID
EFIAPI
LogShow(UINTN num);

EFI_STATUS
Wait4IBF(UINT8 port);

EFI_STATUS
Wait4OBF(UINT8 port);

VOID
EFIAPI
EcWait(
	UINT8 StaPort,
	UINT8 CmdPort,
	UINT8 cmd,
	UINT8 dt
	);


#endif