
#include "SmBiosRead.h"

EFI_STATUS
SmbiosRead(
	IN UINTN Argc,
  IN CHAR16 **Argv
  )
{
	//EFI_STATUS Status;
	
	SMBIOS_TABLE_ENTRY_POINT *SmBiosEntryTable;
	SMBIOS_STRUCTURE_POINTER SmBiosStruc;
	SMBIOS_TABLE_TYPE0 *type0;
	
	EFI_SMBIOS_PROTOCOL *protocol_smbios;
	EFI_SMBIOS_HANDLE handle;
	EFI_SMBIOS_TABLE_HEADER *header;
	CHAR8 *str;
	
	EfiGetSystemConfigurationTable(&gEfiSmbiosTableGuid,(VOID**)&SmBiosEntryTable);
	gBS->LocateProtocol(&gEfiSmbiosProtocolGuid,NULL,(VOID**)&protocol_smbios);

	if(Argc==2 && StrCmp(Argv[1],L"-t")==0){

	Print(L"SMBios Ver: %d.%d  Rev: %d\n"
				,SmBiosEntryTable->MajorVersion
				,SmBiosEntryTable->MinorVersion
				,SmBiosEntryTable->EntryPointRevision);
	}
	
	if(Argc==2 && StrCmp(Argv[1],L"-t0")==0){
		
		SmBiosStruc.Raw = (UINT8*)(UINTN)SmBiosEntryTable->TableAddress;
		type0=SmBiosStruc.Type0;
		
		Print(L"Type                      : %02lx\n",type0->Hdr.Type);
		Print(L"Length                    : 0x%lx\n",type0->Hdr.Length);
		Print(L"Handle                    : 0x%04lx\n",type0->Hdr.Handle);
		Print(L"Start Addr Bios Segment   : %04lx\n",type0->BiosSegment);
		str=GetSmbiosString(SmBiosStruc,type0->Vendor);
		Print(L"BIOS Vendor               : %s\n",ASCII_to_UCS2(str,StrLen((UINT16*)str)));
		str=GetSmbiosString(SmBiosStruc,type0->BiosVersion);
		Print(L"BIOS Version              : %s\n",ASCII_to_UCS2(str,StrLen((UINT16*)str)));
		Print(L"BIOS Size                 : %lx\n",type0->BiosSize);
		str=GetSmbiosString(SmBiosStruc,type0->BiosReleaseDate);
		Print(L"Release Date              : %s\n",ASCII_to_UCS2(str,StrLen((UINT16*)str)));
		Print(L"Characteristics           : %lx\n",type0->BiosCharacteristics);
		Print(L"ExtensionBytes            : %02lx %02lx\n",type0->BIOSCharacteristicsExtensionBytes[0],
																											 type0->BIOSCharacteristicsExtensionBytes[1]);
		Print(L"System Bios Major Release : %lx\n",type0->SystemBiosMajorRelease);
		Print(L"System Bios Minor Release : %lx\n",type0->SystemBiosMinorRelease);
		Print(L"EC Firmware Major Release : %lx\n",type0->EmbeddedControllerFirmwareMajorRelease);
		Print(L"EC Firmware Minor Release : %lx\n",type0->EmbeddedControllerFirmwareMinorRelease);

	}
	
	else if(Argc==2 && StrCmp(Argv[1],L"-t1")==0){
		
		handle=0;
		protocol_smbios->GetNext(protocol_smbios,&handle,NULL,&header,NULL);
		SmBiosStruc.Hdr=(SMBIOS_STRUCTURE*)header;
		
		Print(L"Type               : %02lx\n",header->Type);
		Print(L"Length             : 0x%lx\n",header->Length);
		Print(L"Handle             : 0x%04lx\n",header->Handle);
		str=GetSmbiosString(SmBiosStruc,SmBiosStruc.Type1->Manufacturer);
		Print(L"BIOS Manufacture   : %s\n",ASCII_to_UCS2(str,StrLen((UINT16*)str)));
		str=GetSmbiosString(SmBiosStruc,SmBiosStruc.Type1->ProductName);
		Print(L"BIOS Product Name  : %s\n",ASCII_to_UCS2(str,StrLen((UINT16*)str)));
		str=GetSmbiosString(SmBiosStruc,SmBiosStruc.Type1->Version);
		Print(L"BIOS Version       : %s\n",ASCII_to_UCS2(str,StrLen((UINT16*)str)));
		str=GetSmbiosString(SmBiosStruc,SmBiosStruc.Type1->SerialNumber);
		Print(L"BIOS Serial Number : %s\n",ASCII_to_UCS2(str,StrLen((UINT16*)str)));
		Print(L"UUID               : %lx-%lx-%lx-%lx%lx-%lx%lx%lx%lx%lx%lx\n",SmBiosStruc.Type1->Uuid.Data1
																																			   ,SmBiosStruc.Type1->Uuid.Data2
																																			   ,SmBiosStruc.Type1->Uuid.Data3
																																			   ,SmBiosStruc.Type1->Uuid.Data4[0]
																																			   ,SmBiosStruc.Type1->Uuid.Data4[1]
																																			   ,SmBiosStruc.Type1->Uuid.Data4[2]
																																			   ,SmBiosStruc.Type1->Uuid.Data4[3]
																																			   ,SmBiosStruc.Type1->Uuid.Data4[4]
																																			   ,SmBiosStruc.Type1->Uuid.Data4[5]
																																			   ,SmBiosStruc.Type1->Uuid.Data4[6]
																																			   ,SmBiosStruc.Type1->Uuid.Data4[7]);
		Print(L"Wakeup Type        : %lx\n",SmBiosStruc.Type1->WakeUpType);
		str=GetSmbiosString(SmBiosStruc,SmBiosStruc.Type1->SKUNumber);
		Print(L"BIOS SKU Number    : %s\n",ASCII_to_UCS2(str,StrLen((UINT16*)str)));
		str=GetSmbiosString(SmBiosStruc,SmBiosStruc.Type1->Family);
		Print(L"BIOS Family        : %s\n",ASCII_to_UCS2(str,StrLen((UINT16*)str)));

	}
	else if(Argc==2 && StrCmp(Argv[1],L"-t2")==0){
		
	}
	else{}
	
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
    SmbiosRead( Argc, Argv);
   
	return EFI_SUCCESS;
}

