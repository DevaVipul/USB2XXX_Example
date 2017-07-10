  /*
  ******************************************************************************
  * @file     : USB2XXXSPISniffer.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX SPI slave receive file test demo
  ******************************************************************************
  * @attention
  *
  * Copyright 2009-2014, usbxyz.com
  * http://www.usbxyz.com/
  * All Rights Reserved
  * 
  ******************************************************************************
  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "usb_device.h"
#include "usb2spi.h"

FILE *pMISOFile;
int MISOFileSize = 0;
int __stdcall MISOGetDataCallback(int DevHandle,int SPIIndex,unsigned char *pData,int DataNum)
{
    for(int i=0;i<(DataNum/16);i++){
        for(int j=0;j<16;j++,MISOFileSize++){
            fprintf(pMISOFile,"%02X ",*pData++);
        }
        if((MISOFileSize%16)==0){
            fprintf(pMISOFile,"\n");
        }
    }
    for(int j=0;j<(DataNum%16);j++,MISOFileSize++){
        fprintf(pMISOFile,"%02X ",*pData++);
        if((MISOFileSize%16)==0){
            fprintf(pMISOFile,"\n");
        }
    }
    printf("MISO Get Data Num:%d\n",DataNum);
    return 0;
}


FILE *pMOSIFile;
int MOSIFileSize = 0;
int __stdcall MOSIGetDataCallback(int DevHandle,int SPIIndex,unsigned char *pData,int DataNum)
{
    for(int i=0;i<(DataNum/16);i++){
        for(int j=0;j<16;j++,MOSIFileSize++){
            fprintf(pMOSIFile,"%02X ",*pData++);
        }
        if((MISOFileSize%16)==0){
            fprintf(pMOSIFile,"\n");
        }
    }
    for(int j=0;j<(DataNum%16);j++,MOSIFileSize++){
        fprintf(pMOSIFile,"%02X ",*pData++);
        if((MISOFileSize%16)==0){
            fprintf(pMOSIFile,"\n");
        }
    }
    printf("MOSI Get Data Num:%d\n",DataNum);
    return 0;
}

int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    SPI_CONFIG SPIConfig;
    int DevHandleArry[20];
    int DevHandle;
    int MOSISPIIndex = SPI1_CS0;
    int MISOSPIIndex = SPI2_CS0;
    bool state;
    int ret;
    unsigned char ReadBuffer[20480];
    //ɨ������豸
    ret = USB_ScanDevice(DevHandleArry);
    if(ret <= 0){
        printf("No device connected!\n");
        getchar();
        return 0;
    }
    //ѡ���һ���豸
    DevHandle = DevHandleArry[0];
    //���豸
    state = USB_OpenDevice(DevHandle);
    if(!state){
        printf("Open device error!\n");
        getchar();
        return 0;
    }
    //��ȡ�̼���Ϣ
    char FunctionStr[512]={0};
    state = DEV_GetDeviceInfo(DevHandle,&DevInfo,FunctionStr);
    if(!state){
        printf("Get device infomation error!\n");
        getchar();
        return 0;
    }else{
	    printf("Firmware Name:%s\n",DevInfo.FirmwareName);
        printf("Firmware Build Date:%s\n",DevInfo.BuildDate);
        printf("Firmware Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("Hardware Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
	    printf("Firmware Functions:%s\n",FunctionStr);
        printf("Firmware Serial Number:%08X%08X%08X\n",DevInfo.SerialNumber[0],DevInfo.SerialNumber[1],DevInfo.SerialNumber[2]);
    }
    //����SPI��ز��������������ƥ��
    int DataTemp;
    printf("Please input CPHA(0 or 1):");
    scanf("%d",&DataTemp);
    SPIConfig.CPHA = DataTemp;
    printf("Please input CPOL(0 or 1):");
    scanf("%d",&DataTemp);
    SPIConfig.CPOL = DataTemp;
    printf("SPIConfig.CPHA = %d\n",SPIConfig.CPHA);
    printf("SPIConfig.CPOL = %d\n",SPIConfig.CPOL);
    //����SPI������ز���(����Ϊ�ӻ�ģʽ)
    SPIConfig.Mode = SPI_MODE_HARD_FDX;
    SPIConfig.ClockSpeedHz = 50000000;
    SPIConfig.CPHA = 0;
    SPIConfig.CPOL = 0;
    SPIConfig.LSBFirst = SPI_MSB;
    SPIConfig.Master = SPI_SLAVE;
    SPIConfig.SelPolarity = SPI_SEL_LOW;
    ret = SPI_Init(DevHandle,MOSISPIIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Config SPI error!\n");
        getchar();
        return 0;
    }
    ret = SPI_Init(DevHandle,MISOSPIIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Config SPI error!\n");
        getchar();
        return 0;
    }
    //�����ļ���
    //printf("Please input file name:");
    const char *pMISOFileName = "MISO_Data.txt";
    const char *pMOSIFileName = "MOSI_Data.txt";
    //gets(FileName);
    printf("Start receive data to file!\n");
    printf("Input 'q' to exit the data reception!\n");
    //printf("Data saved to data.csv\n");
    pMISOFile=fopen(pMISOFileName,"wb"); //��ȡ�ļ���ָ��
    if(pMISOFile == NULL){
        printf("Open file faild\n");
        getchar();
        return 0;
    }
    pMOSIFile=fopen(pMOSIFileName,"wb"); //��ȡ�ļ���ָ��
    if(pMOSIFile == NULL){
        printf("Open file faild\n");
        getchar();
        return 0;
    }
    SPI_SlaveContinueRead(DevHandle,MOSISPIIndex,MOSIGetDataCallback);
    SPI_SlaveContinueRead(DevHandle,MISOSPIIndex,MISOGetDataCallback);
    while(1){
        scanf("%c",&DataTemp);
        if(DataTemp=='q'){
            break;
        }
    }
    SPI_SlaveContinueReadStop(DevHandle,MOSISPIIndex);
    SPI_SlaveContinueReadStop(DevHandle,MISOSPIIndex);
    USB_CloseDevice(DevHandle);
    fclose(pMISOFile);
    fclose(pMOSIFile);
    printf("MOSI Data Num = %d Byte\n",MOSIFileSize);
    printf("MISO Data Num = %d Byte\n",MISOFileSize);
    printf("Test SPI_SUCCESS!\n");
    return 0;
}
