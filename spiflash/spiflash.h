//
//
//****************************************
//
//**  Copyright  (C)  W.ch  2013        **
//
//**  Web:  http://www.wch.cn	        **
//
//****************************************
//
//**  LIB for USB interface chip CH341  **
//
//**  C, LINUX                          **
//
//****************************************
//
//

#ifndef		_SPI_FLASH_H_
#define		_SPI_FLASH_H_

#define ReadByte		0x03
#define Sector_Erase	0x20
#define Block_Erase		0x52
#define Chip_Erase		0x60
#define Byte_Program	0x02
#define AAI				0xAF
#define RDSR			0x05
#define EWSR			0x50
#define WRSR			0x01
#define WREN			0x06
#define WRDI			0x04
#define ReadID			0x90
#define JEDECID			0x9F


//Manufacturer ID
#define WINBOND    0XEF
#define AMIC       0X37
#define MXIC       0XC2
#define GD         0XC8
#define EON   	   0x1c
#define PMC		   0X7F

//Device ID

//WINBOND
#define W25Q80BV_ID   0X4014
#define W25Q16BV_ID   0X4015
#define W25Q32BV_ID   0X4016
#define W25Q64BV_ID   0X4017
#define W25Q128BV_ID  0X4018

//MXIC
#define  MX25L3235D_ID 0x5e16
#define  MX25L6445E_ID 0X2017
#define  MX25L8035E_ID 0x2014
#define  MX25L1636_ID  0x2515
#define  MX25L12835F_ID 0x2018

//GD
#define  GD25Q64B_ID   0x4017
#define  GD25Q128B_ID  0x4018

//AMIC
#define  A25LQ32A_ID   0X4016

//EON
#define EN25Q32A_ID    0x3016
#define EN25Q64_ID     0x3017

//PMC
#define PM25LQ032      0x9d46 

//type
#define OSPI_TYPE_A  0  // WRSR 01 -> (STATUS 0~7,8~15)  two bytes
#define OSPI_TYPE_B  1  // WRSR 05 35 15 (STATUS 0~7) (STATUS 8~15) (STATUS 16~23) three bytes 
#define OSPI_TYPE_C  2  // WRSR 01 -> (STATUS 0~7) one byte
#define UN_KNOW_MF_ID 0xff
#define UN_KNOW_DV_ID 0xff
#define UN_KNOW_TY_ID 0xff

#define OSPI_TYPE_A_HPM_TOGGLE_VALUE 0xAA 
#define OSPI_TYPE_B_HPM_TOGGLE_VALUE 0xAA
#define OSPI_TYPE_C_HPM_TOGGLE_VALUE 0xA5

#define OSPI_TYPE_A_NON_TOGGLE_VALUE 0X55
#define OSPI_TYPE_B_NON_TOGGLE_VALUE 0x55
#define OSPI_TYPE_C_NON_TOGGLE_VALUE 0XCC

struct spi_flash_type_id {
    unsigned int manu_id;
    unsigned int dev_id;
	unsigned int type;
};

static const struct spi_flash_type_id spi_flash_id[]={
{WINBOND,W25Q80BV_ID,OSPI_TYPE_A},
{WINBOND,W25Q16BV_ID,OSPI_TYPE_A},
{WINBOND,W25Q32BV_ID,OSPI_TYPE_A},
{WINBOND,W25Q64BV_ID,OSPI_TYPE_A},
{WINBOND,W25Q128BV_ID,OSPI_TYPE_B},
{AMIC,A25LQ32A_ID,OSPI_TYPE_A},
{MXIC,MX25L3235D_ID,OSPI_TYPE_C},
{MXIC,MX25L6445E_ID,OSPI_TYPE_C},
{MXIC,MX25L8035E_ID,OSPI_TYPE_C},
{MXIC,MX25L1636_ID,OSPI_TYPE_C},
{MXIC,MX25L12835F_ID,OSPI_TYPE_C},
{GD,GD25Q64B_ID,OSPI_TYPE_A},
{GD,GD25Q128B_ID,OSPI_TYPE_B},
{EON,EN25Q32A_ID,OSPI_TYPE_C},
{EON,EN25Q64_ID,OSPI_TYPE_C},
{PMC,PM25LQ032,OSPI_TYPE_C},
{UN_KNOW_MF_ID,UN_KNOW_DV_ID,UN_KNOW_TY_ID},
};

int ReadFlashId();

BOOL CH34xWriteEnable();

BOOL CH34xSectorErase( ULONG StartAddr );

int CH34x_Flash_ReadByte( PVOID oBuffer,
			ULONG iAddr);

int CH34x_Flash_ReadBlock( PVOID oBuffer,
			ULONG iAddr);

BOOL CH34xFlash_Wait();

BOOL CH34x_Flash_Write( PVOID iBuffer,
			ULONG iAddr );

BOOL CH34xReadSPI();

BOOL CH34xWriteSPI();

#endif
