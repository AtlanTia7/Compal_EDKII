
#include "SMBus.h"

//search SPD device//
// smbus have only 7 pins, the high bit in SPD address is set defult as 1010[A]
// however, we usually read as 8 bit. So the register address will be shown as
// A0[1010000+0],A2[1010001+0],A4[1010010+0],...,AE[1010111+0]
EFI_STATUS
EFIAPI
SMBusTool (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
	UINT32 IOPort,Index;
	UINT8 SlaveAdr, SPD_v[256];
	IOPort=GetSMBusIOport();//set SMBase Address as IO port

	for(SlaveAdr=0xA0;SlaveAdr<0xAF;SlaveAdr+=2){
	//run it one time, to check if the data correct or not
		ReadSmbus(IOPort,SlaveAdr,0);
		if(IoRead8(IOPort)&0x04){continue;}
		
		for(Index=0;Index<0x100;Index++){
			ReadSmbus(IOPort,SlaveAdr,Index);
			SPD_v[Index]= IoRead8(IOPort+0x05);
		}

		Print(L"          YOU ARE NOW READING SPD ADDRESS %lx        \n",SlaveAdr);
		Print(L"=====================================================\n");
		Print(L"    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
		//print table
		for(Index=0;Index<0x100;Index++){
			if(Index%16==0){Print(L"\n%02lx  ",Index);}
			Print(L"%02lx ",SPD_v[Index]);
			if(Index==0xff){Print(L"\n");}
		}
	}
	
	
	return EFI_SUCCESS;
} 

