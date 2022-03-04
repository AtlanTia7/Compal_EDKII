
#include "ECCMD.h"
/*
EFI_STATUS
EFIAPI
CheckDataRange(UINT8 data){
	if((data>=0x30 && data<=0x39) || (data>=0x41 && data<=0x5a) || (data>=0x61 && data<=0x7a)){
		return 1;
	}
	else{return 0;}
}*/

EFI_STATUS
EFIAPI
ReadEC (
  IN UINTN Argc,
  IN CHAR16 **Argv
  )
{
	UINT8 Port, Cmd, Data;
	UINTN cnt;
	cnt=1;
	
	if(Argc==1){
		Print(L"=======================================\n");
		Print(L"              TOOL USAGE\n");
		Print(L"   [Port][Command][Data]\n");
		Print(L"   EX. 66 52 A0\n");
		Print(L"   < MUST ENTER COMMAND BEFORE DATA >  \n");
		Print(L"=======================================\n");
	}
	else if(Argc==4){
		Port=(UINT8)StrHexToUintn(Argv[1]);
		Cmd=(UINT8)StrHexToUintn(Argv[2]);
		Data=(UINT8)StrHexToUintn(Argv[3]);

		if(Port==0x64 || Port==0x66){
			ReadWriteEC(Port,Cmd,Data);
		}
		else{LogShow(2);}
	}
	else{LogShow(3);}
	
	return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_SHELL_PARAMETERS_PROTOCOL *gEfiShellParametersProtocol;


  UINTN	  		   Argc;
  CHAR16  		  **Argv;
  EFI_STATUS   Status;
  EFI_GUID  mEfiShellParametersProtocolGuid = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;

	gEfiShellParametersProtocol = NULL;

	if (gEfiShellParametersProtocol != NULL){
		Print (L"gEfiShellParametersProtocol is initialized\n");
        Argc = gEfiShellParametersProtocol->Argc;
        Argv = gEfiShellParametersProtocol->Argv;

	}else {
        // check out input parameters from command line using UEFI Shell 2.0
        
		Status = gBS->OpenProtocol(ImageHandle,
                             &mEfiShellParametersProtocolGuid,
                             (VOID **)&gEfiShellParametersProtocol,
                             ImageHandle,
                             NULL,
                             EFI_OPEN_PROTOCOL_GET_PROTOCOL
                            ); 
		if (EFI_ERROR(Status)) {
	    Print(L"\nSorry, Getting Shell params did NOT work or in the EFI Shell 1.0: \n");
		  return EFI_UNSUPPORTED;
		}else{
		  Argc = gEfiShellParametersProtocol->Argc;
			Argv = gEfiShellParametersProtocol->Argv;
		}
	

	}
    //
    // use shell 2.0 interface
    //
  ReadEC( Argc, Argv);
	return EFI_SUCCESS;
}



