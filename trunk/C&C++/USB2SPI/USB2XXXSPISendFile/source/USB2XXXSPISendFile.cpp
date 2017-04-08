  /*
  ******************************************************************************
  * @file     : USB2XXXSPISendFile.cpp
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

int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    int DevHandle[10];
    int SPIIndex = 0;
    bool state;
    int ret,i;
    //ɨ������豸
    ret = USB_ScanDevice(DevHandle);
    if(ret <= 0){
        printf("No device connected!\n");
        return 0;
	}else if (ret <= 1) {
		printf("Must connect two devices!\n");
		return 0;
	}
    //���豸
    state = USB_OpenDevice(DevHandle[1]);
    if(!state){
        printf("Open device error!\n");
        return 0;
    }
    //��ȡ�̼���Ϣ
    char FunctionStr[512]={0};
    state = DEV_GetDeviceInfo(DevHandle[1],&DevInfo,FunctionStr);
    if(!state){
        printf("Get device infomation error!\n");
        return 0;
    }else{
	    printf("Firmware Name:%s\n",DevInfo.FirmwareName);
        printf("Firmware Build Date:%s\n",DevInfo.BuildDate);
        printf("Firmware Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("Hardware Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
	    printf("Firmware Functions:%s\n",FunctionStr);
        printf("Firmware Serial Number:%08X%08X%08X\n",DevInfo.SerialNumber[0],DevInfo.SerialNumber[1],DevInfo.SerialNumber[2]);
    }
    //����SPI������ز���
    SPI_CONFIG SPIConfig;
    SPIConfig.Mode = 1;
    SPIConfig.ClockSpeedHz = 25000000>>2;
    SPIConfig.CPHA = 0;
    SPIConfig.CPOL = 0;
    SPIConfig.LSBFirst = 0;
    SPIConfig.Master = 1;
    SPIConfig.SelPolarity = 0;
    ret = SPI_Init(DevHandle[1],SPIIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Initialize device error!\n");
        return 0;
    }
    //�����ļ���
    printf("Please input file name:");
    char FileName[512]={0};
    gets(FileName);
    //���ļ�
    FILE *pReadFile=fopen(FileName,"rb"); //��ȡ�ļ���ָ��
    if(pReadFile == NULL){
	    printf("Open file error!\n");
	    return -2;
    }
    unsigned char *pInputBuf;  //�����ļ�ָ��
    fseek(pReadFile,0,SEEK_END); //��ָ���ƶ����ļ��Ľ�β ����ȡ�ļ�����
    int InputFileLen=ftell(pReadFile); //��ȡ�ļ�����
	pInputBuf = new unsigned char[InputFileLen]; //�������鳤��
	rewind(pReadFile); //��ָ���ƶ����ļ���ͷ ��Ϊ����һ��ʼ��ָ���ƶ�����β��������ƶ����������
	fread(pInputBuf,1,InputFileLen,pReadFile); //���ļ�
	fclose(pReadFile); // �ر��ļ�
    printf("FileSize = %d Byte\n",InputFileLen);
    //��ȡ��ʼʱ��,��Ҫ���ڲ��Է����ٶ�
    LARGE_INTEGER litmp;
    LONGLONG StartTime,EndTime;
    double dfFreq;
    QueryPerformanceFrequency(&litmp);// Get the performance counter frequency, in n/s
    dfFreq = (double)litmp.QuadPart;
    QueryPerformanceCounter(&litmp);  // Get the current value of the performance counter
    StartTime = litmp.QuadPart;       // Start time
    //ѭ��������ͨ��SPI�ڷ��ͳ�ȥ
    int PackSize = 20*1024;//ÿ�η���10K�ֽ�����
    int PackIndex = 0;
    for(PackIndex = 0;PackIndex<(InputFileLen/PackSize);PackIndex++){
        ret = SPI_WriteBytes(DevHandle[1],SPIIndex,&pInputBuf[PackIndex*PackSize],PackSize);
        if(ret != SPI_SUCCESS){
            printf("SPI write data error!\n");
            return 0;
        }
        Sleep(1);
    }
    if(InputFileLen%PackSize){
        ret = SPI_WriteBytes(DevHandle[1],SPIIndex,&pInputBuf[PackIndex*PackSize],InputFileLen%PackSize);
        if(ret != SPI_SUCCESS){
            printf("SPI write data error!\n");
            return 0;
        }
    }
	//��ȡ����ʱ�䲢��ӡ�����ʱ���ٶ�
    QueryPerformanceCounter(&litmp);// Get the current value of the performance counter
    EndTime = litmp.QuadPart; // Stop time
	// Print the write data speed information
	printf("-----------------------www.usbxyz.com-----------------------\n");
	printf("���������ֽ���: %.3f MBytes\n",InputFileLen/(1024*1024.0));
	printf("������������ʱ��: %f s\n",(EndTime-StartTime)/dfFreq);
	printf("���������ٶ�: %.3f MByte/s\n",InputFileLen/((EndTime-StartTime)/dfFreq)/(1024*1024));
	printf("-----------------------www.usbxyz.com-----------------------\n");
    //�ر��豸
    USB_CloseDevice(DevHandle[1]);
    printf("SPI send file test success!\n");
    return 0;
}