
#include <MYLIB_IoLib.h>

//
//--------------------------------------------------------------------
//Dump Pci
//
//
EFI_STATUS
EFIAPI
PciFormat(
	UINT8 T2R,//Type to read, [2]:Byte [4]:Word [8]:DWord
	UINT32 BN,
	UINT32 DN,
	UINT32 FN
	)
{
	UINT16 R,C;
	UINT32 PrintOff_N;

	PrintOff_N=PciRead32(PCI_LIB_ADDRESS(BN,DN,FN,0));
	
	if(PrintOff_N!=0xffffffff){

		if(T2R==2){
			Print(L"     ");
			for(C=0;C<0x10;C++){
				Print(L"%02lx ",C);
			}Print(L"\n\n");
		}
		else if(T2R==4){
			Print(L"     ");
			for(C=0;C<0x10;C+=2){
				Print(L"%02lx%02lx ",C+1,C);
			}Print(L"\n\n");
		}
		else if(T2R==8){
			Print(L"     ");
			for(C=0;C<0x10;C+=4){
				Print(L"%02lx%02lx%02lx%02lx ",C+3,C+2,C+1,C);
			}Print(L"\n\n");
		}

		for(R=0;R<0x100;R+=0x10){
			for(C=0;C<0x10;C+=4){
				
				PrintOff_N=PciRead32(PCI_LIB_ADDRESS(BN,DN,FN,C+R));//Scan offset
				if(C==0x00){Print(L"%02lx   ",R);}//Print Row
				
				if(T2R==2){
					Print(L"%02lx %02lx %02lx %02lx ",PrintOff_N&(0xff),(PrintOff_N>>8)&(0xff),(PrintOff_N>>16)&(0xff),(PrintOff_N>>24)&(0xff));
				}
				else if(T2R==4){
					Print(L"%04lx %04lx ",PrintOff_N&0xffff,(PrintOff_N>>16)&0xffff);
				}
				else if(T2R==8){
					Print(L"%08lx ",PrintOff_N);//Print offset
				}
				
			}Print(L"\n");
		}
		
	}
	else{Print(L"CAN'T FIND DEVICE.\n");}

	return EFI_SUCCESS;
}
//
//
//--------------------------------------------------------------------
//Read SmBus
//
//find the IOport to access SPD from SMBus
//

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC

UINT32 
GetSMBusIOport(){
	UINT32 i,addr;
  
	for(i=0; i<=0xfff800; i+=0x100){
		addr=0x80000000+i;
		IoWrite32(PCI_CONFIG_ADDRESS,addr+0x08);//class code
		if((IoRead32(PCI_CONFIG_DATA)>>16)==0xc05){//check class code
			IoWrite32(PCI_CONFIG_ADDRESS,addr+0x20);//find out SMBase Address
			goto find;
		}
	}
	find:
	return IoRead32(PCI_CONFIG_DATA)& 0xFFFE;//return SMBase Address
}

VOID
EFIAPI
ReadSmbus(
	UINT32 IOPort,
	UINT8  Slave,
	UINT32 Index
	)
{
	IoWrite8(IOPort,0xFE);//set offset 0x00 to defult (clean data)
	IoWrite8(IOPort+0x04,Slave+1);//read Slave (ex.A0+1=10100000+1(read))
	IoWrite8(IOPort+0x03,(UINT8)Index);//move offset
	IoWrite8(IOPort+0x02,0x48);//read as Byte (see spec)(48=01001000,[010]=read as byte)
	while(IoRead8(IOPort)&0x01);//wait for SMBus finish task
}
//
//
//--------------------------------------------------------------------
//Read Cmos
//
#define Bank0_index 0x70
#define Bank0_data  0x71
#define Bank1_index 0x72
#define Bank1_data  0x73
//
//this function will print out bank0 or bank1
//must enter four parameter
// < first parameter > choose bank0 or bank1
// < second parameter > enter 1 as write, else will be read
// < third parameter > the offset you want to write in
// < fourth parameter > the value you want to write for
EFI_STATUS
EFIAPI
BankPrint(
	IN INT8 BankChoose,//[0]:Bank0, [1]:Bank1
	IN INT8 ReadOrWrite,//[1]:Write
	IN UINT8 Write_Offset,
	IN UINT8 Write_Value
	)
{
	UINT16 Row;
	UINT8 Offsets;
	
	Print(L"\n                ## This is Bank%d ##\n",BankChoose);
	Print(L"    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
	
	//determine wether bank0 or bank1
	if(BankChoose==0){

		//if is write then do the following
		if(ReadOrWrite==1){
			IoWrite8 (Bank0_index, Write_Offset);
			IoWrite8 (Bank0_data, Write_Value);
		}

		//print out bank0
		for(Row=0;Row<0x80;Row++){
			IoWrite8(Bank0_index,(UINT8)Row);
			Offsets=IoRead8(Bank0_data);
			if(Row%16==0){ Print(L"\n%02lx  ",Row); 
		}
			Print(L"%02lx ",Offsets);
		}Print(L"\n");
		
	}
	
	//determine wether bank0 or bank1
	else if(BankChoose==1){

		//if is write then assign offset and value
		if(ReadOrWrite==1){
			IoWrite8 (Bank1_index, Write_Offset);
			IoWrite8 (Bank1_data, Write_Value);
		}

		//print out bank1
		for(Row=0;Row<0x80;Row++){
			IoWrite8(Bank1_index,(UINT8)Row);
			Offsets=IoRead8(Bank1_data);
			if(Row%16==0){ Print(L"\n%02lx  ",Row); 
		}
			Print(L"%02lx ",Offsets);
		}Print(L"\n");
		
	}
	
	return EFI_SUCCESS;
}

//--------------------------------------------------------------------
//Read ECcmd
//

#define TIMEOUT 0x1f4

//this function will show the warning
VOID
EFIAPI
LogShow(UINTN num){
	if(num==0){Print(L"  WARNING: IBF WAITING TIMEOUT\n");}
	else if(num==1){Print(L"  WARNING: OBF WAITING TIMEOUT\n");}
	else if(num==2){Print(L"WARNING: PLEASE ENTER PORT 64 OR 66\n");}
	else if(num==3){Print(L"WARNING: YOU CAN ONLY ENTER THREE PARAMETERS IN\n");}
	else{}
}

//you can use this function to wait for input buffer while you read ec
EFI_STATUS
Wait4IBF(UINT8 port){
	UINT8 KBC_Sta;
	UINTN cnt;

	cnt=0;
  KBC_Sta=IoRead8(port);
	//if bit 1 of status is not 0, then keep read, till it's 0 or timeout 
	while(((KBC_Sta>>1)&0x01)!=0){
		KBC_Sta=IoRead8(port);
		cnt++;
		//if time out, set status as 0 and break
		if(cnt>TIMEOUT){
			LogShow(0);
			KBC_Sta=0;
			break;
		}
	}
	return KBC_Sta;
}


//you can use this function to wait for output buffer while you read ec
EFI_STATUS
Wait4OBF(UINT8 port){
	UINT8 KBC_Sta;
	UINTN cnt;

  KBC_Sta=IoRead8(port);
	cnt=0;
	//if bit 0 of status is not 0, then keep read, till it's 0 or timeout 
	while((KBC_Sta&0x01)!=1){
		KBC_Sta=IoRead8(port);
		cnt++;
		//if time out, set status as 0 and break
		if(cnt>TIMEOUT){
			LogShow(1);
			KBC_Sta=0; 
			break;
		}
	}
	return KBC_Sta;
}


VOID
EFIAPI
EcWait(
	UINT8 StaPort,
	UINT8 CmdPort,
	UINT8 cmd,
	UINT8 dt
	)
{
	Wait4IBF(StaPort);
	IoWrite8(StaPort,cmd);
	Wait4IBF(StaPort);
	IoWrite8(CmdPort,dt);
}


//--------------------------------------------------------------------
//


