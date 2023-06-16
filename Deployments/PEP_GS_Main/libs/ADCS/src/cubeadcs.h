/*
 * cubelib.h
 */

#ifndef __CUBEADCS_H_
#define __CUBEADCS_H_

#include "types.h"
#include "common.h"


/*****************************************************************
 * High-level ADCS functions for retrieving file list and downloading files
 *****************************************************************/
uint8_t CUBEADCS_ReadFileList(COMMON_FileInfo_t** returnList);
bool CUBEADCS_DownloadFile(char* fileName, COMMON_FileInfo_t* targetFile);


/*****************************************************************
  * These are platform specific functions that have to be implemented,
  * or included using appropriate libraries (i.e. FatFs, stdio etc.)
  *****************************************************************/
// for sending/receiving comms messages
bool SendCommand(uint8_t* msg, uint16_t len);
bool RequestTelemetry(uint8_t tlmId, uint8_t* msgBuffer, uint16_t len);

// for miili-second accuracy timing purposes
void Delay(uint16_t ms);
uint32_t GetMsTick();

// for console/debug printout
int printf(const char *format, ... );

// for file handling. note, you have to replace these #define's and typedefs with the FatFs library
#define FR_OK 0
#define FA_CREATE_NEW 1
typedef int FIL;
typedef int FRESULT;
typedef char TCHAR;
typedef U8 BYTE;
typedef U32 UINT;
FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);
FRESULT f_close (FIL* fp);
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);

#endif /* __CUBEADCS_H_ */
