
#include <MYLIB_IoLib.h>

#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/LoadedImage.h>
#include <Protocol/EfiShellParameters.h>

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC

