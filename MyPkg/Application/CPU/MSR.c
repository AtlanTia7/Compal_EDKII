
#include "MSR.h"

// Sample of Main using Argv and Argc input parameters
//example using shell command line parameters passed from an EFI application

EFI_STATUS
EFIAPI
MsrStatus (
  IN UINTN Argc,
  IN CHAR16 **Argv
  )
{
	CPUID_VERSION_INFO_EAX     Eax;
  CPUID_VERSION_INFO_ECX     Ecx;
  CPUID_VERSION_INFO_EDX     Edx;
	UINT64 										 Msr_v;
	UINT32                     Msr_Addr;

	AsmCpuid(CPUID_VERSION_INFO, &Eax.Uint32, NULL, &Ecx.Uint32, &Edx.Uint32);
	
	if(Edx.Bits.MSR){

		if(Argc==1){
			Print(L"\n=================================================\n");
			Print(L"||                                             ||\n");
			Print(L"|| [ADDRESS]            READ MSR REGISTER INFO ||\n");
			Print(L"|| EX.10                                       ||\n");
			Print(L"||                                             ||\n");
			Print(L"=================================================\n\n");
		}
		
		if(Argc==2){
			
			Msr_Addr=(UINT32)StrHexToUintn(Argv[1]);
			Msr_v=AsmReadMsr64(Msr_Addr);
			
			Print(L"\n      MSR Regiter info\n");
			Print(L"============================\n");
			Print(L"  High bit (EDX): %08lx\n",Msr_v>>32);
			Print(L"   Low bit (EAX): %08lx\n",Msr_v&0xffffffff);
			Print(L"============================\n\n");
			
		}
		
	}
	else{Print(L"This Device Does NOT Support MSR.\n");}
	
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


  UINTN	  		Argc;
	CHAR16  		**Argv;
  EFI_STATUS  Status;
  EFI_GUID    mEfiShellParametersProtocolGuid = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;

	gEfiShellParametersProtocol = NULL;

	if (gEfiShellParametersProtocol != NULL){
		//Print (L"gEfiShellParametersProtocol is initialized\n");
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
		      //Print(L"\nSorry, Getting Shell params did NOT work or in the EFI Shell 1.0: \n");
			  return EFI_UNSUPPORTED;
		}else{
		  Argc = gEfiShellParametersProtocol->Argc;
			Argv = gEfiShellParametersProtocol->Argv;
		}
	

	}
    //
    // use shell 2.0 interface
    //
    MsrStatus( Argc, Argv);
   
	return EFI_SUCCESS;
}



