
#include <Uefi.h>
#include <Base.h>

#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#define WRITE_PORT 0x70
#define READ_PORT  0x71
#define SEC_NUM    0x00
#define MIN_NUM    0x02
#define HOUR_NUM   0x04

EFI_STATUS
UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE * SystemTable){

  UINT8 Hour,Min,Sec;

  IoWrite8(WRITE_PORT,SEC_NUM);
  Sec=IoRead8(READ_PORT);
  IoWrite8(WRITE_PORT,MIN_NUM);
  Min=IoRead8(READ_PORT);
  IoWrite8(WRITE_PORT,HOUR_NUM);
  Hour=IoRead8(READ_PORT);

  Print(L"%02lx : %02lx : %02lx\n",Hour,Min,Sec);

  return EFI_SUCCESS;
}