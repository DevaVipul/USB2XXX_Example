  /*
  ******************************************************************************
  * @file     : USB2XXXSPISlaveTest.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX SPI slave test demo
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

FILE *pFile;
int FileSize = 0;
int __stdcall SlaveGetData(int DevHandle,int SPIIndex,unsigned char *pData,int DataNum)
{
    fwrite(pData,1,DataNum,pFile);
    FileSize += DataNum;
    return 0;
}

int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    SPI_CONFIG SPIConfig;
    int DevHandle[10];
    int SPIIndex = SPI1_CS0;
    bool state;
    int ret;
    unsigned char ReadBuffer[20480];
    //ɨ������豸
    ret = USB_ScanDevice(DevHandle);
    if(ret <= 0){
        printf("No device connected!\n");
        getchar();
        return 0;
    }
    //���豸
    state = USB_OpenDevice(DevHandle[0]);
    if(!state){
        printf("Open device error!\n");
        getchar();
        return 0;
    }
    //��ȡ�̼���Ϣ
    char FunctionStr[512]={0};
    state = DEV_GetDeviceInfo(DevHandle[0],&DevInfo,FunctionStr);
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
    /*printf("Please input CPHA(0 or 1):");
    scanf("%d",&DataTemp);
    SPIConfig.CPHA = DataTemp;
    printf("Please input CPOL(0 or 1):");
    scanf("%d",&DataTemp);
    SPIConfig.CPOL = DataTemp;
    printf("SPIConfig.CPHA = %d\n",SPIConfig.CPHA);
    printf("SPIConfig.CPOL = %d\n",SPIConfig.CPOL);*/
    //����SPI������ز���(����Ϊ�ӻ�ģʽ)
    SPIConfig.Mode = SPI_MODE_HARD_FDX;
    SPIConfig.ClockSpeedHz = 50000000;
    SPIConfig.CPHA = 0;
    SPIConfig.CPOL = 0;
    SPIConfig.LSBFirst = SPI_MSB;
    SPIConfig.Master = SPI_SLAVE;
    SPIConfig.SelPolarity = SPI_SEL_LOW;
    ret = SPI_Init(DevHandle[0],SPIIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Initialize device error!\n");
        getchar();
        return 0;
    }
    //�����ļ���
    printf("Please input file name:");
    char FileName[512]={0};
    gets(FileName);
    printf("Start receive data to file,the file name is %s\n",FileName);
    printf("Press any key to exit the data reception!\n");
    pFile=fopen(FileName,"wb"); //��ȡ�ļ���ָ��
    if(pFile == NULL){
        printf("Open file faild\n");
        getchar();
        return 0;
    }
    SPI_SlaveContinueRead(DevHandle[0],SPIIndex,SlaveGetData);
    getchar();
    SPI_SlaveContinueReadStop(DevHandle[0],SPIIndex);
    USB_CloseDevice(DevHandle[0]);
    fclose(pFile);
    printf("FileSize = %d Byte\n",FileSize);
    printf("Test SPI_SUCCESS!\n");
    getchar();
    return 0;
}
