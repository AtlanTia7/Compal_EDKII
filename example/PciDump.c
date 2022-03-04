
#include <Uefi.h>
#include <Base.h>

#include <Library/UefiLib.h>
#include <Library/IoLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC

EFI_STATUS
UefiMain(IN EFI_HANDLE        ImageHandle,
          IN EFI_SYSTEM_TABLE  *SystemTable)
{
    UINT32 i,id,cfg_addr;

    for(i=0;i<=0xf800;i+=0x0800){
        cfg_addr=0x80000000L+i;
        IoWrite32( 0xCF8,cfg_addr);
        id=IoRead32(0xCFC);
        if(id!=0xffffffff){
            Print(L"%08lx %08lx \n", cfg_addr, id);
        }
    }
    return EFI_SUCCESS;
}


    
/**    for(i=0;i<=0xf800;i+=0x0800){
        cfg_adder=0x80000000L+i;
        Outport32( 0xCF8,cfg_addr);
        id=Inport32(0xCFC);
        if(id!=0xffffffff){
            printf("%08lx %08lx \n", cfg_addr, id);
        }
    }


    IoWrite8(PCI_CONFIG_ADDRESS, IN UINT8 Value)
    id=IoRead8(PCI_CONFIG_DATA)
    Print(L"%08lx \n",id);
**/