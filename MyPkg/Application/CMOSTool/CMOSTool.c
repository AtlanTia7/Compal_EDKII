#include "CMOSTool.h"

EFI_STATUS
EFIAPI
ShowLog(UINTN tesk){
	switch(tesk){
		case 1:
			Print(L"\n==================================================================================\n");
			Print(L"||                                                                              ||\n");
			Print(L"||  [r/R] [0/1]                      READ THE CHOOSEN BANK.                     ||\n");
			Print(L"||  ex. r 0                          -----------------------------------------  ||\n");
			Print(L"||                                   <  FIRST PARAMETER SPECIFIC AS READ     >  ||\n");
			Print(L"||                                   < SECOND PARAMETER SPECIFIC AS THE BANK >  ||\n");
			Print(L"||                                                                              ||\n");
			Print(L"||  [w/W] [0/1] [OFFSET#] [VALUE]    WRITE VALUE IN TO THE BANK.                ||\n");
			Print(L"||  ex. w 0 30 26                    -----------------------------------------  ||\n");
			Print(L"||                                   <  FIRST PARAMETER SPECIFIC AS WRITE    >  ||\n");
			Print(L"||                                   < SECOND PARAMETER SPECIFIC AS THE BANK >  ||\n");
			Print(L"||                                   <  THIRD PARAMETER SPECIFIC AS OFFSET#  >  ||\n");
			Print(L"||                                   < FOURTH PARAMETER SPECIFIC AS VALUE    >  ||\n");
			Print(L"||                                                                              ||\n");
			Print(L"==================================================================================\n");
			break;

		default:
			Print(L"PLEASE ENTER '-h' OR '-help' TO GET INSTRUCTION OF THE TOOL.\n");
			break;
	}
			

	return EFI_SUCCESS;
}	

EFI_STATUS
EFIAPI
CMOSTool (
  IN UINTN Argc,
  IN CHAR16 **Argv
  )
{
	UINT8 bk,Offset_w,value_w;
	INT8  WriteIn;

	//showing instruction
	if(Argc==2 && (StrCmp(Argv[1],L"-help")==0 || StrCmp(Argv[1],L"-h")==0)){
	 ShowLog(1);
	}

	//read
	else if(Argc==3 && (StrCmp(Argv[1],L"r")==0 || StrCmp(Argv[1],L"R")==0)){

		//asign second parameter
		bk=(UINT8)StrHexToUintn(Argv[2]);

		if(bk==0 || bk==1){
			BankPrint(bk,0,0,0);//calling function to print bank0 or bank1
		}
		else{ShowLog(999);}
		
	}

	//write
	// < restrict >
	//the length of the parameter user enter can only smaller then 2
	else if(Argc==5 && (StrCmp(Argv[1],L"w")==0 || StrCmp(Argv[1],L"W")==0) && (StrLen(Argv[2])==1 && StrLen(Argv[3])<=2 && StrLen(Argv[4])<=2)){

		//assign second to fourth parameter 
		WriteIn=1;
		bk=(UINT8)StrHexToUintn(Argv[2]);
		Offset_w=(UINT8)StrHexToUintn(Argv[3]);
		value_w=(UINT8)StrHexToUintn(Argv[4]);
		
		if(bk==0 || bk==1){
			BankPrint(bk,WriteIn,Offset_w,value_w);//calling function to print bank0 or bank1
		}
		else{ShowLog(999);}
		
	}
	else{ShowLog(999);}
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
	UINTN	  		  Argc;
	CHAR16  		**Argv;
  EFI_STATUS      Status;
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
    CMOSTool( Argc, Argv);
   
	return EFI_SUCCESS;
}



