/* ===========================================================================
* @file file_utils.h
*
*
* @desc 
* 
* Copyright (c) Bluetop Technology Co.,Ltd  2012
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* If you find any bug,please tell me.
* Email:zhaogongchen@bluetop.com.cn
* =========================================================================== */

#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define FILE_ERROR(STR...)       fprintf(stderr, "[BT-ERROR]: "__FILE__": " STR)

#define FILE_DEBUG 0

#if FILE_DEBUG
#define FILE_PRINTF(STR...)      printf(STR)
#else
#define FILE_PRINTF(STR...) 
#endif

#define FILE_ASSERT(_x)  { if (!(_x)) { FILE_ERROR("Assertion Failed :"); FILE_PRINTF(#_x); FILE_PRINTF("\n"); return 0; } }


int get_file_size(FILE *fp, unsigned int *file_size);

int file_read(FILE *fp, char *buff, int read_data, int *nbytes);

int file_write(FILE *fp, char *buff, int write_data);

int file_open(FILE **fp, const char * file_name, const char * mode);

void file_close(FILE **fp);

#ifdef __cplusplus
};
#endif

#endif
