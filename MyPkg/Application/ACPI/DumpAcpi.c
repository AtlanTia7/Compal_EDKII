
#include "DumpAcpi.h"

EFI_STATUS
EFIAPI
SampleMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
	EFI_STATUS																		Status;
	UINTN 																				i,EntryCount;
	CHAR16																				Sign[20];
	UINT64																				*EntryPtr;
	EFI_GUID																			Acpi2TableGuid = EFI_ACPI_TABLE_GUID;
	EFI_ACPI_DESCRIPTION_HEADER				 						*XSDT,*Entry;
	EFI_ACPI_6_0_ROOT_SYSTEM_DESCRIPTION_POINTER	*Ptr;

	Status=EfiGetSystemConfigurationTable(&Acpi2TableGuid,(VOID**)&Ptr);
	EFI_ERROR(Status) ? Print(L"Can't Find Table.\n") : Print(L"");
			
	// Step2. Check the Revision, we olny accept Revision >= 2
	if (Ptr->Revision>=EFI_ACPI_6_0_ROOT_SYSTEM_DESCRIPTION_POINTER_REVISION)
	{
		// Step3. Get XSDT address, count=( length of the whole xsdt - header length ) / count in 8 byte
		XSDT=(EFI_ACPI_DESCRIPTION_HEADER *)(UINTN) Ptr->XsdtAddress;
		EntryCount = (XSDT->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER)) / 8; 
		
		// Step4. Check the signature of every entry
		EntryPtr=(UINT64 *)(XSDT+1);
		for (i=0;i<EntryCount; i++,EntryPtr++)
		{
			Entry=(EFI_ACPI_DESCRIPTION_HEADER *)((UINTN)(*EntryPtr));
			ZeroMem(Sign,sizeof(Sign));
			Sign[0]= (Entry->Signature & 0xFF);
			Sign[1]= (Entry->Signature >> 8 & 0xFF);
			Sign[2]= (Entry->Signature >> 16 & 0xFF);
			Sign[3]= (Entry->Signature >> 24 & 0xFF);
			Print(L"%02d: [ %s ] 0x%X\n",i+1,Sign,Entry);
		}
	}	
  return EFI_SUCCESS;
} 

