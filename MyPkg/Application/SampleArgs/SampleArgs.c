/** @file
  This is a simple shell application

  Copyright (c) 2008, Intel Corporation                                                         
  All rights reserved. This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

#include <Base.h>
#include <Uefi.h>

#include <Library/ShellLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#include <Protocol/LoadedImage.h>
#include <Protocol/EfiShellParameters.h>

// Sample of Main using Argv and Argc input parameters
//example using shell command line parameters passed from an EFI application

EFI_STATUS
EFIAPI
SampleMain (
  IN UINTN Argc,
  IN CHAR16 **Argv
  )
{
  
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
    SampleMain ( Argc, Argv);
   
	return EFI_SUCCESS;
}



