#include "ReadEDID.h"

EFI_STATUS
EFIAPI
ShowDigitalBitDepth(UINT8 bit_d){
	if(CheckBit(bit_d,6)&&CheckBit(bit_d,5)&&CheckBit(bit_d,4)){
		Print(L"Reserved");
	}
	else if(CheckBit(bit_d,6)&&CheckBit(bit_d,5)){
		Print(L"16 bits per color");
	}
	else if(CheckBit(bit_d,6)&&CheckBit(bit_d,4)){
		Print(L"14 bits per color");
	}
	else if(CheckBit(bit_d,6)){
		Print(L"12 bits per color");
	}
	else if(CheckBit(bit_d,5)&&CheckBit(bit_d,4)){
		Print(L"10 bits per color");
	}
	else if(CheckBit(bit_d,5)){
		Print(L"8 bits per color");
	}
	else if(CheckBit(bit_d,4)){
		Print(L"6 bits per color");
	}
	else{Print(L"undefined");}
	Print(L"\n");

	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ShowVideoInterface(UINT8 vdo){
	if(CheckBit(vdo,2)&&CheckBit(vdo,0)){
		Print(L"DisplayPort");
	}
	else if(CheckBit(vdo,2)){
		Print(L"MDDI");
	}
	else if(CheckBit(vdo,1)&&CheckBit(vdo,0)){
		Print(L"HDMIb");
	}
	else if(CheckBit(vdo,1)){
		Print(L"HDMIa");
	}
	else{Print(L"undefined");}
	Print(L"\n");
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ShowDigitalDisplayType(UINT8 ddp_type){
	if(CheckBit(ddp_type,3)&&CheckBit(ddp_type,4)){
		Print(L"RGB 4:4:4 + YCrCb 4:4:4 + YCrCb 4:2:2");
	}
	else if(CheckBit(ddp_type,3)){
		Print(L"RGB 4:4:4 + YCrCb 4:4:4");
	}
	else if(CheckBit(ddp_type,4)){
		Print(L"RGB 4:4:4 + YCrCb 4:2:2");
	}
	else{Print(L"RGB 4:4:4");}
	Print(L"\n");
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ShowAnalogBitDepth(UINT8 b_d){
	if(CheckBit(b_d,6)&&CheckBit(b_d,5)){
		Print(L"+0.7/0 V (EVC)");
	}
	else if(CheckBit(b_d,6)){
		Print(L"+1.0/?0.4 V");
	}
	else if(CheckBit(b_d,5)){
		Print(L"+0.714/?0.286 V");
	}
	else{Print(L"+0.7/?0.3 V");}
	Print(L"\n");
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ShowAnalogDisplayType(UINT8 adp_type){
	if(CheckBit(adp_type,3)&&CheckBit(adp_type,4)){
		Print(L"undefined");
	}
	else if(CheckBit(adp_type,3)){
		Print(L"RGB color");
	}
	else if(CheckBit(adp_type,4)){
		Print(L"non-RGB color");
	}
	else{Print(L"monochrome or grayscale");}
	Print(L"\n");
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ShowGamma(UINT8 value){
	UINT8 Dec,Flot;
	Dec=value/100;
	Flot=value%100;

	Print(L"%d",Dec+1);
	Print(L".");
	Print(L"%d",Flot);
	Print(L" gamma\n");

	return EFI_SUCCESS;
} 

EFI_STATUS
EFIAPI
ShowManufacTiming(UINT8 manu_time){
	if(CheckBit(manu_time,7)){
		Print(L"1152x870 @ 75 Hz (Apple Macintosh II)");
	}
	else{Print(L"Other manufacturer-specific display modes");}
	Print(L"\n");
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ImageRatioShow(UINT8 Image_ratio){
	if(CheckBit(Image_ratio,7)&&CheckBit(Image_ratio,6)){
		Print(L"16:9");
	}
	else if(CheckBit(Image_ratio,7)){
		Print(L"5:4");
	}
	else if(CheckBit(Image_ratio,6)){
		Print(L"4:3");
	}
	else{Print(L"16:10");}
	Print(L"\n");
	return EFI_SUCCESS;
}

VOID
EFIAPI
PrintEdid(EFI_EDID_DISCOVERED_PROTOCOL *Edid)
{
  EDID_DATA_BLOCK *EdidDataBlock = (EDID_DATA_BLOCK *)Edid->Edid;
  UINT8 i,tmp;

  Print(L"EDID Version           : V %d.%d\n", EdidDataBlock->EdidVersion,EdidDataBlock->EdidRevision);
	
	Print(L"Model   ID             : ");
	for(i=0;i<17;i++){
		Print(L"%s",ShowAsciiStr(EdidDataBlock->DescriptionBlock4[i]));
	}
	Print(L"\n");
	
  Print(L"Vendor  ID             : %s\n", ManufacturerAbbrev(&EdidDataBlock->ManufactureName));
  Print(L"Product ID             : %lX\n", EdidDataBlock->ProductCode);
	//
	Print(L"Serial Number          : ");
	if(EdidDataBlock->SerialNumber==0){
		Print(L"<NONE USE>\n");
	}else{
  	Print(L"%lX\n", EdidDataBlock->SerialNumber);
	}
	//
  Print(L"Manufacture Week       : %d\n", EdidDataBlock->WeekOfManufacture);
  Print(L"Manufacture Year       : %d\n", EdidDataBlock->YearOfManufacture + 1990);
	//
  tmp = EdidDataBlock->VideoInputDefinition;
  Print(L"Video Input            : ");
  if(CheckBit(tmp, 7)){
    Print(L"Digital\n");
		Print(L"Bit Depth              : ");ShowDigitalBitDepth(tmp);
		Print(L"Video Interface        : ");ShowVideoInterface(tmp);
		tmp=EdidDataBlock->DpmSupport;
		Print(L"Display Type           : ");ShowDigitalDisplayType(tmp);
  } 
	else {
    Print(L"Analog\n");
		Print(L"Bit Depth              : ");ShowAnalogBitDepth(tmp);
		tmp=EdidDataBlock->DpmSupport;
		Print(L"Display Type           : ");ShowAnalogDisplayType(tmp);
  }
	//
	Print(L"Display Gamma          : ");ShowGamma(EdidDataBlock->DisplayGamma);
	Print(L"Max Horizonal Size     : %1d cm\n", EdidDataBlock->MaxHorizontalImageSize);
  Print(L"Max Vertical  Size     : %1d cm\n", EdidDataBlock->MaxVerticalImageSize);
	tmp=EdidDataBlock->EstablishedTimings[2];
	Print(L"Manufacturer's Timings : ");ShowManufacTiming(tmp);
	tmp=EdidDataBlock->StandardTimingIdentification[0];
	Print(L"Resolution             : %ld pixels\n",(tmp+31)*8);
	tmp=EdidDataBlock->StandardTimingIdentification[1];
	Print(L"Image Aspect Ratio     : ");ImageRatioShow(tmp);
	Print(L"Field Refresh Rate     : %ld Hz\n",(tmp&0xffffff)+60);

}

EFI_STATUS
EFIAPI
GetEDIDInfo(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
	)
{
	EFI_STATUS Status;
	EFI_HANDLE *EDIDHandleBuffer;
	UINTN EDIDHandleCount, Index, i;
	EFI_EDID_DISCOVERED_PROTOCOL *EDID;
	
	Status = gBS->LocateHandleBuffer(ByProtocol,
																	&gEfiEdidDiscoveredProtocolGuid,
																	NULL,
																	&EDIDHandleCount,
																	&EDIDHandleBuffer);

	if(EFI_ERROR(Status)){
		Print(L"ERROR : CAN'T GET EdidDiscoveredProtocol.\n");
		return FALSE;
	}

	Print(L"EDID count : %d\n",EDIDHandleCount);

	for(Index=0;Index<EDIDHandleCount;Index++){
		Status=gBS->OpenProtocol( EDIDHandleBuffer[Index],
														 &gEfiEdidDiscoveredProtocolGuid,
														 (VOID**)&EDID,
														 gImageHandle,
														 NULL,
														 EFI_OPEN_PROTOCOL_GET_PROTOCOL
													  );

		if(EFI_ERROR(Status)){
			Print(L"ERROR : OPEN EDID PROTOCOL FAILED.\n");
			return FALSE;
		}

		Print(L"EDID size  : %d\n", EDID->SizeOfEdid);
		Print(L"    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n\n");
		for(i=0; i<128; i++){
			if(i%16==0){ Print(L"%02lx  ",i);}
			Print(L"%02X ", EDID->Edid[i]);
			if((i+1)%16==0){ Print(L"\n");}
		}
		Print(L"\n");
		PrintEdid(EDID);

		Status=gBS->CloseProtocol(EDIDHandleBuffer[Index],
														 &gEfiEdidDiscoveredProtocolGuid,
														 gImageHandle,
														 NULL
														 );
		if(EFI_ERROR(Status)){
			Print(L"ERROR : CLOSE EDID DEVICE HANDLE FAILED.\n");
			return FALSE;
		}
	}
	return EFI_SUCCESS;
}
