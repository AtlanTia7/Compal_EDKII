
#include "PciDump.h"

EFI_STATUS
EFIAPI
ShowLog(UINTN tesk){
	switch(tesk){
		case 1:
		  Print(L"\n==========================================================================================================\n");
			Print(L"|| [L/l]                                       SHOW PCI LIST                                            ||\n");
			Print(L"||                                                                                                      ||\n");
			Print(L"|| [BUS#][DEVICE#][FUNCTION#]                  SHOW THE EXACT PCI DEVICE < DWORD >                      ||\n");
			Print(L"|| ex. 0 2 0                                                                                            ||\n");
			Print(L"||                                                                                                      ||\n");
			Print(L"|| [BUS#][DEVICE#][FUNCTION#][BYTE/WORD]       SHOW THE PCI DEVICE IN BYTE OR WORD < CASE-INSENSITIVE > ||\n");
			Print(L"|| ex. 0 2 0 Byte                                                                                       ||\n");
			Print(L"||                                                                                                      ||\n");
			Print(L"|| [BUS#][DEVICE#][FUNCTION#][OFFSET][VALUE]   WRITE THE VALUE IN TO THE EXACT PCI DEVICE < DWORD >     ||\n");
			Print(L"|| ex. 0 2 0 E0 67                                                                                      ||\n");
			Print(L"||                                                                                                      ||\n");
			Print(L"||======================================================================================================||\n");
			Print(L"||                            THE LENGTH OF ALL PARAMETER WILL BE RESTRICT TO TWO                       ||\n");
			Print(L"||                           VARIABLES MUST COMPLY WITH HEXADECIMAL SPECIFICATIONS                      ||\n");
			Print(L"==========================================================================================================\n");
			break;
			
		default:
			Print(L" < ENTER '-h' OR '-help' TO GET INSTRCTION. >\n");
			break;
	}
	return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
PciDumpMain (
  IN UINTN Argc,
  IN CHAR16 **Argv
  )
{
	UINT32 W_offset,W_Value,Bus_N,Device_N,Function_N,i,id,cfg_addr;

	//with no parameter, show device that exist
	if(Argc==1){
		ShowLog(999);
	}

	else if(Argc==2){

		if(StrCmp(Argv[1],L"L")==0 || StrCmp(Argv[1],L"l")==0){
			
		  Print(L"DEVICE ID    VENDOR ID    BUS#  DEVICE#  FUNCTION#\n");

			for(i=0;i<=0xfff800;i+=0x0100){
	      cfg_addr=0x80000000L+i;
	      IoWrite32( PCI_CONFIG_ADDRESS,cfg_addr);
	      id=IoRead32(PCI_CONFIG_DATA);
	      if(id!=0xffffffff){
					Print(L"%04lx         %04lx         ",id>>16,((id)&(0xffff)));
	        Print(L"%02lx    %02lx       %02lx\n", (cfg_addr>>16)&(0xff),(cfg_addr>>11)&(0x1f),(cfg_addr>>8)&(0x07));
	      }
			}
    }
		else if(StrCmp(Argv[1],L"-h")==0 || StrCmp(Argv[1],L"-help")==0){
			ShowLog(1);
    }
		else{ ShowLog(999); }
		
	}

	//With 4 parameter, show the table that read as DWord(default table setting).
	else if((Argc==4 || Argc==5 || Argc==6) && (StrLen(Argv[1])<3 && StrLen(Argv[2])<3 && StrLen(Argv[3])<3)
		)
	{
		
		Bus_N=(UINT32)StrHexToUintn(Argv[1]);//Parameter1 assign to Bus_Number
		Device_N=(UINT32)StrHexToUintn(Argv[2]);//Parameter2 assign to Device_Number
		Function_N=(UINT32)StrHexToUintn(Argv[3]);//Parameter3 assign to Function_Number
		
		if(Argc==4){
			PciFormat(8,Bus_N,Device_N,Function_N);
		}
		
		else if(Argc==5){
			if(StrCmp(Argv[4],L"Byte")==0 || StrCmp(Argv[4],L"byte")==0){
				PciFormat(2,Bus_N,Device_N,Function_N);
			}
			else if(StrCmp(Argv[4],L"Word")==0 || StrCmp(Argv[4],L"word")==0){
				PciFormat(4,Bus_N,Device_N,Function_N);
			}
			else{ ShowLog(999); }
		}
		
		else if(Argc==6 && (StrLen(Argv[4])<=2 && StrLen(Argv[5])<=2)
			)
		{
			W_offset=(UINT32)StrHexToUintn(Argv[4]);//Parameter4 assign to Write_in_Offset
			W_Value=(UINT32)StrHexToUintn(Argv[5]);//Parameter5 assign to Write_in_Value

			PciWrite32(PCI_LIB_ADDRESS(Bus_N,Device_N,Function_N,W_offset),(INT32)W_Value);
			PciFormat(8,Bus_N,Device_N,Function_N);
		}
 		else{ ShowLog(999); }
		
	}
	else{ ShowLog(999); }
	
	return EFI_SUCCESS;
} 


/**
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_SHELL_PARAMETERS_PROTOCOL *gEfiShellParametersProtocol;

    UINTN	  				  Argc;
		CHAR16  				**Argv;
    EFI_STATUS      Status;
    EFI_GUID  mEfiShellParametersProtocolGuid = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;

	gEfiShellParametersProtocol = NULL;

	if (gEfiShellParametersProtocol != NULL){
		Print (L"gEfiShellParametersProtocol is initialized\n");
        Argc = gEfiShellParametersProtocol->Argc;
        Argv = gEfiShellParametersProtocol->Argv;

	}else {
        // check out input parameters from command line using UEFI Shell 2.0
        //Print(L"\n Test\n");
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
    PciDumpMain ( Argc, Argv);
   
	return EFI_SUCCESS;
}



