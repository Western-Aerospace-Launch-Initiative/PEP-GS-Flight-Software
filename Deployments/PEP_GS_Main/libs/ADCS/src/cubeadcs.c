
#include "cubeadcs.h"
#include "common.h"
#include "cubeacp.h"

#define maxFileList 10

COMMON_FileInfo_t FileList [maxFileList];

static uint8_t downloadMessageLen = 20;
static uint16_t downloadBurstLength = 1024;
static uint8_t downloadHoleMapTcLen = 16;
uint8_t Block [20480];
uint8_t holemap[128];
uint8_t holeMapPart[16];
bool DownloadCancel = false;

static uint16_t CRC_Calc(uint8_t *start, uint32_t len);
bool CUBEADCS_DownloadBlock(COMMON_FileInfo_t* targetFile, uint16_t fileOffset, uint16_t* numBytes);

uint8_t CUBEADCS_ReadFileList(COMMON_FileInfo_t** returnList)
{
	uint8_t counter = 0;
	uint32_t tick, tock;
	uint8_t i;
	bool end = false;
	uint8_t txbuffer[500];
	uint8_t rxbuffer[500];
	uint32_t txlen;

	// clear current FileList
	memset((uint8_t*)FileList, 0, maxFileList*sizeof(COMMON_FileInfo_t));

	// reset file pointer
	txlen = COMMON_FormatResetFileListPtrCmd(txbuffer);
	if (!SendCommand(txbuffer, txlen))
	{
		// handle error
		return 0;
	}

	Delay(100);

	tick = GetMsTick();
	tock = GetMsTick();
	do
	{
		// request file info
		if (!RequestTelemetry(FileInfo, rxbuffer, COMMON_GetTlmLen(FileInfo)))
		{
			// handle error
			return 0;
		}

		// extract data from byte array into COMMON_FileInfo_t struct
		COMMON_ExtractFileInfoTlm(rxbuffer, &FileList[counter]);

		// check if ADCS was still busy updating file info
		if(FileList[counter].busyUpdating == false)
		{
			// check to see if the end of the file list has been reached
			if((FileList[counter].fileType == 0) && (FileList[counter].fileCtr == 0) && (FileList[counter].size == 0) && (FileList[counter].checksum == 0))
			{
				end = true;
			}
			else
			{
				// not the end yet. valid file info received, reset timeout counter
				tick = GetMsTick();

				// advance file pointer
				txlen = COMMON_FormatAdvanceFileListPtrCmd(txbuffer);
				if (!SendCommand(txbuffer, txlen))
				{
					// handle error
					return 0;
				}

				// increment number of valid file info received
				counter++;
			}
		}
		else
		{
			// wait a bit, and try again
			Delay(20);
		}

		tock = GetMsTick();
	}while((end == false) && (tock-tick < 1000));

	printf("Total files: %d", counter);

	for(i = 0;i<counter;i++)
	{
		printf("FileType %d\tFileCounter %d\tFileSize %d\tCRC %d", FileList[i].fileType, FileList[i].fileCtr, FileList[i].size, FileList[i].checksum);
	}

	if((tock - tick >= 1000))
	{
		printf("Reading file list timeout");
	}

	*returnList = FileList;
	return counter;
}

bool CUBEADCS_DownloadFile(char* fileName, COMMON_FileInfo_t* targetFile)
{
	uint8_t i = 0;
	uint16_t numBytes;
	bool success = true;
	FIL file;
	FRESULT fres;
	UINT numWritten;

	fres = f_open( &file, fileName,FA_CREATE_NEW );
	if(fres != FR_OK)
	{
		success  = false;
	}
	else
	{
		do
		{
			numBytes = 0;
			success = CUBEADCS_DownloadBlock(targetFile, i*downloadBurstLength*downloadMessageLen, &numBytes);

			if(success)
			{
				printf("Writing block %d", i);
				f_write(&file, Block, numBytes, &numWritten);
			}

			i++;
		}while((i<targetFile->size/(downloadBurstLength*downloadMessageLen)) && success);

		if(f_close(&file) != 0)
		{
			success = false;
		}
	}

	return success;
}

bool CUBEADCS_DownloadBlock(COMMON_FileInfo_t* targetFile, uint16_t fileOffset, uint16_t* numBytes)
{
	COMMON_DownloadBlockReady_t downloadBlockReady;
	COMMON_FileDownload_t filePacket;

	bool blockdone;
	bool newBytes;
	bool cont;
	bool firstBurst = true;
	uint16_t counter;
	uint16_t counterRef;
	uint16_t crcRX;
	uint16_t i;
	uint16_t packetsLost = 0;
	uint32_t tick, tock;

	uint8_t txbuffer[500];
	uint8_t rxbuffer[500];
	uint32_t txlen;

	uint16_t holeMapLen = downloadBurstLength / 8;
	uint16_t downloadHoleMapNumTcs = holeMapLen / downloadHoleMapTcLen;

	// Clear holemap
	memset(holemap,0,128);
	memset(Block,0,20480);

	*numBytes = 0;

	printf("Download Block");

	// Load new block into memory
	txlen =  COMMON_FormatLoadDownloadBlockCmd(txbuffer, targetFile->fileType, targetFile->fileCtr, fileOffset, (uint16_t)(downloadBurstLength * downloadMessageLen));
	if (!SendCommand(txbuffer, txlen))
	{
		// handle error
		return false;
	}

	Delay(1000);

	printf("Load Block Command");

	// Wait until block has been loaded successful
	tick = GetMsTick();
	tock = GetMsTick();
	do
	{
		if (!RequestTelemetry(DownloadBlockReady, rxbuffer, COMMON_GetTlmLen(DownloadBlockReady)))
		{
			// handle error
			return false;
		}
		COMMON_ExtractDownloadBlockReadyTlm(rxbuffer, &downloadBlockReady);

		// check if block is loaded, else give a short time before next poll
		if(!downloadBlockReady.ready)
		{
			Delay(20);
		}

		tock = GetMsTick();
	} while (!downloadBlockReady.ready && (tock - tick < 1000));

	// check timeout
	if((tock - tick >= 1000))
	{
		printf("Download Block Ready Error");
		return false;
	}

	blockdone = false;
	while(!blockdone && !DownloadCancel)
	{
		// initialise download burst
		txlen = COMMON_FormatDownloadBurstCmd(txbuffer, downloadMessageLen, firstBurst);
		if (!SendCommand(txbuffer, txlen))
		{
			return false;
		}

		// set reference for number of file packets to request
		if(firstBurst)
		{
			counterRef = (downloadBlockReady.length+19)/20;	// 1023
		}
		else
		{
			counterRef = packetsLost;	// number packets i expect to have lost
		}
		firstBurst = false;

		// ... get actual data
		cont = false;
		counter = 0;
		do
		{
			cont = false;
			if(counter < counterRef)
			{
				if (!RequestTelemetry(FileDownload, rxbuffer, COMMON_GetTlmLen(FileDownload)))
				{
					return false;
				}
				COMMON_ExtractFileDownloadTlm(rxbuffer, &filePacket);

				newBytes = true;

				counter++;

				Delay(20);
			}
			else
			{
				newBytes = false;
			}

			if(newBytes)
			{
				memcpy(Block+filePacket.packetNo*20, filePacket.fileBytes, 20);

				holemap[filePacket.packetNo >> 3] = (uint8_t)(holemap[filePacket.packetNo >> 3] | (1 << (filePacket.packetNo & 0x07)));
			}
			cont = true;
		} while (cont);

		// check holemap for gaps
		blockdone = true;
		packetsLost = 0;

		// test holemap for any errors
		for (i = 0; i < downloadBurstLength; i++)
		{
			if (i * downloadMessageLen >= downloadBlockReady.length)
				break;

			if ((holemap[i >> 3] & (1 << (i & 0x07))) == 0)
			{
				blockdone = false;
				packetsLost++;
			}
		}
		printf("No Packets Lost: %d", packetsLost);

		// calculate CRC
		crcRX = CRC_Calc(Block, downloadBlockReady.length);
		printf("Reference: %d Calculated: %d", downloadBlockReady.checksum, crcRX);
		if((downloadBlockReady.checksum != crcRX) && (packetsLost == 0))
		{
			// if CRC fails and no packets are reported to missing then entire block must be reinitialized
			printf("Byte errors in block");
			return false;
		}

		// send holemap telecommands if block is not complete
		if(!blockdone)
		{
			printf("Sending holemap back");
			for (i = 0; i < downloadHoleMapNumTcs; i++)
			{
				memcpy(holeMapPart, holemap+i * downloadHoleMapTcLen, downloadHoleMapTcLen);
				switch (i)
				{
					case 0: txlen = COMMON_FormatHoleMap1Cmd(txbuffer, holeMapPart); break;
					case 1: txlen = COMMON_FormatHoleMap2Cmd(txbuffer, holeMapPart); break;
					case 2: txlen = COMMON_FormatHoleMap3Cmd(txbuffer, holeMapPart); break;
					case 3: txlen = COMMON_FormatHoleMap4Cmd(txbuffer, holeMapPart); break;
					case 4: txlen = COMMON_FormatHoleMap5Cmd(txbuffer, holeMapPart); break;
					case 5: txlen = COMMON_FormatHoleMap6Cmd(txbuffer, holeMapPart); break;
					case 6: txlen = COMMON_FormatHoleMap7Cmd(txbuffer, holeMapPart); break;
					case 7: txlen = COMMON_FormatHoleMap8Cmd(txbuffer, holeMapPart); break;
				}
				if (!SendCommand(txbuffer, txlen))
				{
					return false;
				}
			}
		}
	}

	*numBytes = downloadBlockReady.length;
	return blockdone;
}


static uint16_t CRC_Calc(uint8_t *start, uint32_t len)
{
	uint16_t crc = 0;
	uint8_t  *data;
	uint8_t  *end = start + len;

	for (data = start; data < end; data++)
	{
		crc  = (crc >> 8) | (crc << 8);
		crc ^= *data;
		crc ^= (crc & 0xff) >> 4;
		crc ^= crc << 12;
		crc ^= (crc & 0xff) << 5;
	}
	return crc;
}
