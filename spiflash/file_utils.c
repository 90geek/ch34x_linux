/* ===========================================================================
 * @file file_utils.c
 *
 *
 * @desc An easier file interface.
 *
 * Copyright (c) Bluetop Technology Co.,Ltd  2012
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 *
 * If you find any bug,please tell me.
 * Email:zhaogongchen@bluetop.com.cn
 * =========================================================================== */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "file_utils.h"


/**
 * @brief Get file size from current position.
 * @param fp [IN] file structure pointer.
 * @param file_size[OUT] buffer that save the file size from current position.
 * @return 0 get file size succeed, else, get file size failed.
 */
int get_file_size(FILE *fp, unsigned int *file_size)
{
	int ret = 0;
	FILE_ASSERT(fp);
	do
	{
		errno = 0;
		fseek(fp, 0L, SEEK_END);
		if(errno)
		{
			ret = -1;
			FILE_ERROR("File tell failed with ERROR #%s\n", strerror(errno));
			break;
		}

		errno = 0;
		*file_size = ftell(fp);
		if(errno)
		{
			ret = -1;
			FILE_ERROR("File tell failed with ERROR #%s\n", strerror(errno));
			break;
		}

		errno = 0;
		fseek(fp, -(*file_size), SEEK_CUR);
		if(errno)
		{
			ret = -1;
			FILE_ERROR("File seek failed with ERROR #%s\n", strerror(errno));
			break;
		}
	}
	while(0);

	return ret;
}

/**
 * @brief Read file.
 * @param fp [IN] file structure pointer.
 * @param buff[OUT] pointer to the receive data buffer.
 * @param read_data[IN] number of read bytes.
 * @param nbytes[OUT] real number of read bytes.
 * @return 0.
 */
int file_read(FILE *fp, char *buff, int read_data, int *nbytes)
{
	int ret = 0;

	FILE_ASSERT(fp);
	FILE_ASSERT(buff);
	do
	{
		errno = 0;
		*nbytes = fread(buff, 1, read_data, fp);
		if(errno)
		{
			ret = -1;
			FILE_ERROR("File read failed with ERROR #%s\n", strerror(errno));
		}
	}
	while(0);
	
	return ret;
}

/**
 * @brief Write file.
 * @param fp [IN] file structure pointer.
 * @param buff[IN] pointer to buffer that the data will be written to file.
 * @param write_data[IN] number of write bytes.
 * @return 0, write file succeed, else, write file failed.
 */
int file_write(FILE *fp, char *buff, int write_data)
{
	int ret = 0;
	FILE_ASSERT(buff);
	FILE_ASSERT(fp);
	do
	{
		errno = 0;
		fwrite(buff, 1, write_data, fp);
		if(errno)
		{
			ret = -1;
			FILE_ERROR("File write failed with ERROR #%s\n", strerror(errno));
		}
	}
	while(0);

	return ret;
}

/**
 * @brief Open file.
 * @param fp [OUT] pointer to the file structure pointer.
 * @param file_name[IN] file name that will be opened.
 * @param mode[IN] open mode.
 * @return 0, open file succeed, else, open file failed.
 */
int file_open(FILE **fp, const char * file_name, const char *mode)
{
	int ret = 0;
	struct stat stat_buf;

	FILE_ASSERT(file_name);
	FILE_ASSERT(fp);

	errno = 0;
	*fp = fopen(file_name, mode);
	if(NULL == *fp)
	{
		ret = -1;
		FILE_ERROR("File open failed %s with ERROR #%s\n",file_name, strerror(errno));
	}
	else
	{
		if(-1 == stat(file_name, &stat_buf))
		{
			ret = -1;
			FILE_ERROR("File %s open failed with \n", file_name);
			fclose(*fp);
			*fp = NULL;
		}
		else
		{
			if(S_ISDIR(stat_buf.st_mode))
			{
				ret = -1;
				FILE_ERROR("File %s open failed with\n", file_name);
				fclose(*fp);
				*fp = NULL;
			}
		}
	}
	return ret;
}

/***********************************************************
* Function:file_close
* Description:Close file.
* Input:fp [IN] pointer to the file structure pointer.
* Output:
* Return:none
* Others:
***********************************************************/
void file_close(FILE **fp)
{
	//FILE_ASSERT(fp);
	if(*fp)
	{
		fclose(*fp);
		*fp = NULL;
	}
	return;
}


/************************************** The End Of File **************************************/
