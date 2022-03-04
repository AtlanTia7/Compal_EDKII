#include <MYLIB_StringLib.h>

CHAR16 *
ManufacturerAbbrev(UINT16 *ManufactureName)
{
    static CHAR16 mcode[8];
    UINT8 *block = (UINT8 *)ManufactureName;
    UINT16 h = EDID_COMBINE_HI_8LO(block[0], block[1]);
 
    mcode[0] = (CHAR16)((h>>10) & 0x1f) + 'A' - 1;
    mcode[1] = (CHAR16)((h>>5) & 0x1f) + 'A' - 1;
    mcode[2] = (CHAR16)(h & 0x1f) + 'A' - 1;
    mcode[3] = (CHAR16)'\0';
  
    return mcode;
}

UINT8
EFIAPI
CheckBit(
	UINT8 Input,
	UINT8  Num
)
{
	return (Input>>Num)&(0x01);
}

//this function can change Integer to String
//but only in the specify range
CHAR16*
ShowAsciiStr(UINT8 data){
	static CHAR16 Str[1];
	
	if(data>=0x30 && data<=0x39){
		Str[0]=(CHAR16)(data&0x0f)+'0';
	}
	else if(data>=0x41 && data<=0x5a){
		Str[0]=(CHAR16)(data&0x1f)+'A'-1;
	}
	else if(data>=0x61 && data<=0x7a){
		Str[0]=(CHAR16)(data&0x1f)+'a'-1;
	}
	else if(data==0x2d){
		Str[0]='-';
	}
	else{}
	
	return Str;
}

//
//SMBIOS
//
CHAR16 *
ASCII_to_UCS2(const char *s, UINTN len)
{
	CHAR16 *ret = NULL;
	int i;

	ret = AllocateZeroPool(len*2 + 2);
	
	if (!ret){
		return NULL; 
	}

	for (i = 0; i < len; i++){
		ret[i] = s[i]; 
	}

	return ret;
}



