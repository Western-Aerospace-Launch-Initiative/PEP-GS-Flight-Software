/************************************************************************************
 * This file was auto-generated by CIDEA                           .                *
 * Please do not modify the contents of this file manually.                         *
 ***********************************************************************************/


#include "bootloader.h"

uint16_t BOOTLOADER_GetTlmLen(BOOTLOADER_Telemetry_t tlm)
{
    switch(tlm)
    {
        case CopyToIntFlashProgress:
            return 1;
        case ProgramInfo:
            return 8;
        case State:
            return 6;
        default:
            return -1;
    }
}
CUBEADCS_Result_t BOOTLOADER_ExtractCopyToIntFlashProgressTlm(uint8_t* rxBuffer, BOOTLOADER_CopyToIntFlashProgress_t* returnVal)
{
    if (returnVal == 0)
        return PointerIsNull;

    returnVal->busy = (rxBuffer[0] & 0x01) >> 0;

    returnVal->error = (rxBuffer[0] & 0x02) >> 1;

    return CubeLibOk;
}

CUBEADCS_Result_t BOOTLOADER_ExtractProgramInfoTlm(uint8_t* rxBuffer, BOOTLOADER_ProgramInfo_t* returnVal)
{
    uint8_t enumVal;

    if (returnVal == 0)
        return PointerIsNull;

    enumVal = rxBuffer[0];
    returnVal->programIndex = (BOOTLOADER_ProgramsList_t) enumVal;

    returnVal->busy = (rxBuffer[1] & 0x01) >> 0;


    returnVal->fileSize = *( (U32*) (rxBuffer + 2) );

    returnVal->crc16 = *( (U16*) (rxBuffer + 6) );

    return CubeLibOk;
}

CUBEADCS_Result_t BOOTLOADER_ExtractStateTlm(uint8_t* rxBuffer, BOOTLOADER_State_t* returnVal)
{
    if (returnVal == 0)
        return PointerIsNull;

    returnVal->runtime = *( (U16*) (rxBuffer + 0) );

    returnVal->sram1Enabled = (rxBuffer[2] & 0x01) >> 0;

    returnVal->sram2Enabled = (rxBuffer[2] & 0x02) >> 1;

    returnVal->sramLatchup = (rxBuffer[2] & 0x04) >> 2;

    returnVal->sramLatchupRecovered = (rxBuffer[2] & 0x08) >> 3;

    returnVal->sdInitError = (rxBuffer[2] & 0x10) >> 4;

    returnVal->sdReadError = (rxBuffer[2] & 0x20) >> 5;

    returnVal->sdWriteError = (rxBuffer[2] & 0x40) >> 6;

    returnVal->extFlashError = (rxBuffer[2] & 0x80) >> 7;

    returnVal->intFlashError = (rxBuffer[3] & 0x01) >> 0;

    returnVal->eepromError = (rxBuffer[3] & 0x02) >> 1;

    returnVal->bootRegCorrupt = (rxBuffer[3] & 0x04) >> 2;

    returnVal->radioCommsError = (rxBuffer[3] & 0x08) >> 3;


    return CubeLibOk;
}


uint16_t BOOTLOADER_FormatBootIndexCmd(uint8_t* tcBuffer, BOOTLOADER_BootSetProgramsList_t programIndex)
{
    // write TtcMessage ID to first element in buffer
    tcBuffer[0] = 100;

    tcBuffer[1] = 
        (programIndex << 0);

    return 2;
}

uint16_t BOOTLOADER_FormatClearErrorsCmd(uint8_t* tcBuffer)
{
    // write TtcMessage ID to first element in buffer
    tcBuffer[0] = 7;


    return 1;
}

uint16_t BOOTLOADER_FormatCopyToInternalFlashCmd(uint8_t* tcBuffer, BOOTLOADER_ProgramsList_t srcIndex, U8 bootloaderOverwrite)
{
    // write TtcMessage ID to first element in buffer
    tcBuffer[0] = 103;

    tcBuffer[1] = 
        (srcIndex << 0);
    *( (U8*)(tcBuffer + 2) ) = bootloaderOverwrite;

    return 3;
}

uint16_t BOOTLOADER_FormatReadProgramInfoCmd(uint8_t* tcBuffer, BOOTLOADER_ProgramsList_t programIndex)
{
    // write TtcMessage ID to first element in buffer
    tcBuffer[0] = 102;

    tcBuffer[1] = 
        (programIndex << 0);

    return 2;
}

uint16_t BOOTLOADER_FormatRunSelectedProgramCmd(uint8_t* tcBuffer)
{
    // write TtcMessage ID to first element in buffer
    tcBuffer[0] = 101;


    return 1;
}


