/*
 *ch36x_demo.c for ch365/ch367/ch368 pci card of WCH
 * 
 **********************************************************************
 ***********	  Copyright (C) WCH 2013.10.28		***************
 ***********	      web: www.wch.cn			***************
 ***********	  AUTHOR: TECH33 (tech@wch.cn)		***************
 ***********	 Used for PCI/PCIe Chip (CH365/7/8)	***************
 ***********	Nanjing	QinHeng Electronics Co.,Ltd	***************
 **********************************************************************
 *
 * Running Environment: Linux
 * This file is used for testing I/O\MEM\Configuration\ (Read and Write)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>

#include "ch34x_lib.h"
#include "spiflash.h"
#include "file_utils.h"

#ifndef CH34x_DEBUG
#define CH34x_DEBUG
#endif

#ifdef CH34x_DEBUG
#define dbg( format, arg...)	printf( format "\n", ##arg );
#endif
#define err( format, arg... )	\
	printf( "error %d: " format "\n", __LINE__, ##arg )

extern int dev_fd;
struct{
	void *DeviceId;
	void *Addr;
	unsigned char *Byte;
}i2c_device;


ULONG enable_data;
ULONG dir_data;
ULONG con_data;

/*
 * ********************************************************************
 * init_device( void )
 *
 * Function : open device, Get Driver Version, Get Chip ID
 * ********************************************************************
 */
int init_device( void )
{
	int retval = 0;
	
	system("clear");
	dev_fd = CH34xOpenDevice( 0 );
	if( dev_fd <= 0 )
	{
		err("CH34xOpenDevice Open Error");
		return -1;		
	}	
	dbg( "Open sucessful" );
	//Get Driver Version
	char *drv_version = (char *)malloc( sizeof( char ) * 30 );
	
	retval = CH34x_GetDrvVer( drv_version );
	if( retval == false )
	{
		err( "CH34x_GetDrvVer Error" );
		return -1;
	}
	
	printf( "drv_version : %s\n", drv_version );
	free( drv_version );
	//Get Chip Version
	PULONG VendorId = (char *)malloc( sizeof(unsigned long));
	retval = CH34x_GetVendorId( VendorId );
	if( retval == false )
	{
		err( "CH34x_GetVendorId Error" );
		return -1;
	}	
	printf( "VendorId : 0x%04x\n", *VendorId );
	free( VendorId );
	return true;

}


int ReadFlashId()
{
	ULONG mLen, iChipselect;
	UCHAR mWrBuf[6];
	mWrBuf[0] = ReadID;
	mWrBuf[1] = 0x00;
	mWrBuf[2] = 0x00;
	mWrBuf[3] = 0x00;
	iChipselect = 0x80;
	mLen = 6;
	if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
		return false;
	else	
		return (mWrBuf[5]|(mWrBuf[4]<<8));
}
int ReadFlashJedecId()
{
	ULONG mLen, iChipselect;
	
	UCHAR mWrBuf[6];
	mWrBuf[0] = JEDECID;
	mWrBuf[1] = 0x00;
	mWrBuf[2] = 0x00;
	mWrBuf[3] = 0x00;
	iChipselect = 0x80;
	mLen = 6;
	if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
		return false;
	else	
		return (mWrBuf[3]|(mWrBuf[2]<<8));
}


BOOL CH34xWriteEnable()
{
	ULONG mLen, iChipselect;
	UCHAR mWrBuf[2];
	mWrBuf[0] = WREN;
	mLen = 2;
	iChipselect = 0x80;
	if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
		return false;
	else
		return true;	
}

BOOL CH34xSectorErase( ULONG StartAddr )
{
	ULONG mLen, iChipselect;
	UCHAR mWrBuf[4];
	if( CH34xWriteEnable() == false )
		return false;
	mWrBuf[0] = Sector_Erase;
	mWrBuf[1] = (UCHAR)( StartAddr >> 16 & 0xff );
	mWrBuf[2] = (UCHAR)( StartAddr >> 8 & 0xff );
	mWrBuf[3] = (UCHAR)( StartAddr & 0xff );
	mLen = 4;
	iChipselect = 0x80;
	if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
		return false;
	
	if( CH34xFlash_Wait() == false )
		return false;
	return true;		
}

int CH34x_Flash_ReadByte( PVOID oBuffer, ULONG iAddr )
{
	ULONG mLen, iChipselect;
	UCHAR mWrBuf[16];
	mLen = 16;
	iChipselect = 0x80;
	mWrBuf[0] = ReadByte;
	mWrBuf[1] = (UCHAR)( iAddr >> 16 & 0xff );
	mWrBuf[2] = (UCHAR)( iAddr >> 8 & 0xff );
	mWrBuf[3] = (UCHAR)( iAddr & 0xff );
	if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
		return false;		
	printf("Read SPI Data,First is %x,Second is %x\n",mWrBuf[4],mWrBuf[5]);	
}

int CH34x_Flash_ReadBlock( PVOID oBuffer, ULONG iAddr)
{
	ULONG mLen, iChipselect;
	UCHAR mWrBuf[MAX_BUFFER_LENGTH];	
	ULONG i;
	mLen = 33;
	iChipselect = 0x80;
//	iAddr = iAddr - iAddr % 0x1000;
	mWrBuf[0] = ReadByte;	
	mWrBuf[1] = (UCHAR)( iAddr >> 16 & 0xff );
	mWrBuf[2] = (UCHAR)( iAddr >> 8 & 0xff );
	mWrBuf[3] = (UCHAR)( iAddr & 0xff );
	if( CH34xStreamSPI4( iChipselect, mLen+4, mWrBuf ) == false )
		return false;
	
	for( i = 0; i < mLen; i++ )
		printf("index is %d, Value is %x\n",i,mWrBuf[i + 4]);
	return true;
}

BOOL CH34xFlash_Wait()
{
	ULONG mLen, iChipselect;
	ULONG i = 0;
	UCHAR mWrBuf[3];
	UCHAR status;
	mLen = 3;
	iChipselect = 0x80;
	mWrBuf[0] = RDSR;
	do{
		mWrBuf[0] = RDSR;
		if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
			return false;		
		status = mWrBuf[1];
	}while( status & 1 );
	return true;
}

BOOL CH34xFlashReadStatus()
{
	ULONG mLen, iChipselect;
	UCHAR status;
	UCHAR mWrBuf[3];
	iChipselect = 0x80;
	mLen = 3;
	mWrBuf[0] = RDSR;
	if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
		return false;		
	status = mWrBuf[1];
	if( status & 0x0c )
	{
		mWrBuf[0] = EWSR;
		mLen = 1;
		if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
			return false;		
		mLen = 2;
		memset( mWrBuf, 0, sizeof( UCHAR ) * mLen );
		mWrBuf[0] = WRSR;
		mWrBuf[1] = status & (~0x0c);
		if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
			return false;
	}	
	mWrBuf[0] = RDSR;
	if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
		return false;		
	status = mWrBuf[1];
	
	return true;
}

BOOL CH34x_Flash_Write( PVOID iBuffer, ULONG iAddr )
{
	ULONG i;
	ULONG iChipselect = 0x80;
	UCHAR mWrBuf[5];
	ULONG mLen = 5;
	for( i = 0; i < 2; i++ )
	{
		if( !CH34xWriteEnable() )
			return false;
		mWrBuf[0] = Byte_Program;
		mWrBuf[1] = (UCHAR)(iAddr >> 16 & 0xff);
		mWrBuf[2] = (UCHAR)(iAddr >> 8 & 0xff);
		mWrBuf[3] = (UCHAR)(iAddr & 0xff);
		iAddr++;
		mWrBuf[4] = *((PUCHAR)iBuffer + i);
		if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
			return false;
		memset( mWrBuf, 0, sizeof( UCHAR ) * mLen );
		if( !CH34xFlash_Wait() )
			return false;		
	}
	return true;
}

BOOL CH34x_Flash_Write_Byte( PVOID iBuffer, ULONG iAddr )
{
	ULONG i;
	ULONG iChipselect = 0x80;
	UCHAR mWrBuf[5];
	ULONG mLen = 5;
	
	if( !CH34xWriteEnable() )
		return false;
	mWrBuf[0] = Byte_Program;
	mWrBuf[1] = (UCHAR)(iAddr >> 16 & 0xff);
	mWrBuf[2] = (UCHAR)(iAddr >> 8 & 0xff);
	mWrBuf[3] = (UCHAR)(iAddr & 0xff);
	mWrBuf[4] = *((PUCHAR)iBuffer );
	if( CH34xStreamSPI4( iChipselect, mLen, mWrBuf ) == false )
		return false;
	memset( mWrBuf, 0, sizeof( UCHAR ) * mLen );
	if( !CH34xFlash_Wait() )
		return false;

	return true;
}

BOOL CH34xReadSPI()
{
	ULONG mLen;
	CH34x_Flash_ReadByte( NULL, 0x0000 );
	return true;
}

BOOL CH34xWriteSPI()
{
	int retval;
	int i;
	PUCHAR BufData;
	BufData = malloc( sizeof( UCHAR ) * 4096 );
	if( BufData == NULL )
	{
		printf("malloc error\n");
	}	
	retval = CH34xFlashReadStatus();
	if( retval == false )
	{
		printf("error in flash status\n");
		return false;
	}
/*	retval = CH34x_Flash_ReadByte( BufData, 0x0000 );
f( retval == false )
	{
		printf("error in flash ReadByte\n");
		return false;
	}
*/
	retval = CH34xSectorErase( 0x0000 );
	if( retval == false )
	{
		printf("error in flash Sector Erase\n");
		return false;
	}

//	BufData[0] = 0xaa;
//	BufData[1] = 0x55;
	printf("Please input 2 number:\n");
	for( i = 0; i < 2; i++ )
		scanf("%x", &BufData[i]);
	retval = CH34x_Flash_Write( BufData, 0x0000 );
	if( retval == false )
	{
		printf("error in flash Write\n");
		return false;
	}
	free( BufData );
	return true;

	
}

int WriteBIOS(const char *file)
{ 
	FILE *fp;
	unsigned int *file_size=0;
	int retval=0;
	int i;
	int nbytes=0;
	unsigned int *file_siz=0;
	PUCHAR BufData=NULL;
	unsigned int addr=0;
  int count=0;

	
	if(file==NULL)
		return 0;

	retval=file_open(&fp, file, "rb+");
	if(retval!=0)
		return -1;
	get_file_size(fp, &file_size);
	BufData=(char *)malloc(file_size);
	memset(BufData,0,file_size);
	file_read(fp,BufData, file_size,&nbytes);
	printf("file_size=%d(0x%x)\n",file_size,file_size);
	retval = CH34xFlashReadStatus();
	if( retval == false )
	{
		printf("error in flash status\n");
		return false;
	}

	do{
		retval = CH34xSectorErase(addr);
		if( retval == false )
		{
			printf("error in flash Sector Erase\n");
			return false;
		}
		addr += 0x1000;
		if((addr%(4*0x1000))==0)
    {
			printf(".");
      count++;
      if((count%32)==0)
        printf("\n");
    }
		usleep(1);
	}while(addr<file_size);
	printf("\nErase Ok!\n");
	addr = 0;
  count=0;
	for(i=0;i<file_size;i++)
	{
		retval =CH34x_Flash_Write_Byte(BufData+i, addr+i);
		if( retval == false )
		{
			printf("error in flash Write\n");
			return false;
		}
		if((i%(4*0x1000))==0)
    {
			printf(".");
      count++;
      if((count%32)==0)
        printf("\n");
    }
	}
	printf("\nProgram Ok!\n");

	file_close(&fp);
	free(BufData);
}
void ShowMainMenu( void )
{
	printf("This is main menu listed\n");
	printf("-->1: Read Id\n");
	printf("-->2: Read JEDEC Id\n");
	printf("-->3: SectorErase\n");
	printf("-->4: ReadStatus\n");
	printf("-->5: ReadSpi\n");
	printf("-->6: WriteSpi\n");
	printf("-->7: ReadBIOS\n");
	printf("-->8: WriteBIOS\n");
	printf("Please enter your selection:\n");
	
}
int main( int argc, char **argv )
{
	int ch;
	char button = '\0';
	int retval = 0;
	retval = init_device();
	int id;
	if( retval == -1 )
	{	
		printf("Init device error\n");
		return false;
	}

	while(1)
	{
		ShowMainMenu();
		scanf("%d",&ch);
		printf("You choose %d \n",ch);
		switch(ch)
		{
			case 1:
				id = ReadFlashId();
				if(id!=false)
					printf("Device id:0x%x\n",id);
				break;
		    case 2:
				id = ReadFlashJedecId();
				if(id!=false)
					printf("JEDEC id:0x%x\n",id);
				break;
			break;
		    case 3:
			;// EPP_TEST();
			break;
		    case 4:
			;// MEM_TEST();
			break;
		    case 5:
			;// SPI_FLASH_TEST();
			case 8:
				WriteBIOS("LS3A40007A.fd");

		}
		do
		{
			printf("\nenter 'q' to exit or 'b' to come back\n");
			scanf(" %c", &button);
		}while( button != 'q' && button != 'b' );
		if( button == 'q' )
			break;
	}

	CH34xCloseDevice(); 
	return 0;
}

