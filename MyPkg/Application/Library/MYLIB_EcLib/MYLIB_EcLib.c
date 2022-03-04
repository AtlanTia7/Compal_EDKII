#include <MYLIB_EcLib.h>

//this function can read and write EC
//if timeout, jump out if-loop, show nothing
VOID
EFIAPI
ReadWriteEC (UINTN port, UINT8 cmd, UINT8 dt)
{
	UINT8 cnt,temp;
	if(port==0x64){
		EcWait(EC_Sta,EC_Cmd,cmd,dt);
		if(Wait4OBF(EC_Sta)==0){goto UrTimeout;}
		Wait4OBF(EC_Sta);
		
		Print(L"   YOU ARE NOW READING PORT60\n");
		Print(L"===============================\n");
		for(cnt=0;cnt<5;cnt++){
			temp=IoRead8(EC_Cmd);
			Print(L"         Data 0%d: %lx[%s]\n",cnt+1,temp,ShowAsciiStr(temp));
		}
	}
	else if(port==0x66){
		EcWait(ACPI_Sta,ACPI_Cmd,cmd,dt);
		if(Wait4OBF(ACPI_Sta)==0){goto UrTimeout;}
		Wait4OBF(ACPI_Sta);
		
		Print(L"   YOU ARE NOW READING PORT62\n");
		Print(L"===============================\n");
		for(cnt=0;cnt<5;cnt++){
			temp=IoRead8(ACPI_Cmd);
			Print(L"         Data 0%d: %lx[%s]\n",cnt+1,temp,ShowAsciiStr(temp));
		}
	}
	else{UrTimeout:Print(L"");}
	
}

