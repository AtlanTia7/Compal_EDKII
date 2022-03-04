#ifndef __MAY_EDIDINFO_H__
#define __MAY_EDIDINFO_H__


typedef struct {
    UINT8   Header[8];                        //EDID header "00 FF FF FF FF FF FF 00"
    UINT16  ManufactureName;                  //EISA 3-character ID
    UINT16  ProductCode;                      //Vendor assigned code
    UINT32  SerialNumber;                     //32-bit serial number
    UINT8   WeekOfManufacture;                //Week number
    UINT8   YearOfManufacture;                //Year
    UINT8   EdidVersion;                      //EDID Structure Version
    UINT8   EdidRevision;                     //EDID Structure Revision
    UINT8   VideoInputDefinition;
    UINT8   MaxHorizontalImageSize;           //cm
    UINT8   MaxVerticalImageSize;             //cm
    UINT8   DisplayGamma;
    UINT8   DpmSupport;
    UINT8   RedGreenLowBits;                  //Rx1 Rx0 Ry1 Ry0 Gx1 Gx0 Gy1Gy0
    UINT8   BlueWhiteLowBits;                 //Bx1 Bx0 By1 By0 Wx1 Wx0 Wy1 Wy0
    UINT8   RedX;                             //Red-x Bits 9 - 2
    UINT8   RedY;                             //Red-y Bits 9 - 2
    UINT8   GreenX;                           //Green-x Bits 9 - 2
    UINT8   GreenY;                           //Green-y Bits 9 - 2
    UINT8   BlueX;                            //Blue-x Bits 9 - 2
    UINT8   BlueY;                            //Blue-y Bits 9 - 2
    UINT8   WhiteX;                           //White-x Bits 9 - 2
    UINT8   WhiteY;                           //White-x Bits 9 - 2
    UINT8   EstablishedTimings[3];
    UINT8   StandardTimingIdentification[16];
    UINT8   DescriptionBlock1[18];
    UINT8   DescriptionBlock2[18];
    UINT8   DescriptionBlock3[18];
    UINT8   DescriptionBlock4[18];
    UINT8   ExtensionFlag;                    //Number of (optional) 128-byte EDID extension blocks to follow
    UINT8   Checksum;
} EDID_DATA_BLOCK;

#endif

