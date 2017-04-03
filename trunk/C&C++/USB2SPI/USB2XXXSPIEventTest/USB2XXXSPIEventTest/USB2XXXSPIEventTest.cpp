  /*
  ******************************************************************************
  * @file     : USB2XXXSPIEventTest.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX SPI test demo
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
    SPI_CONFIG SPIConfig;
    int DevIndex = 0;
    int SPIIndex = 0;
    bool state;
    int ret;
    unsigned char WriteBuffer[64];
    unsigned char ReadBuffer[64];
    //ɨ������豸
    ret = USB_ScanDevice(NULL);
    if(ret <= 0){
        printf("No device connected!\n");
        return 0;
    }
    //���豸
    state = USB_OpenDevice(DevIndex);
    if(!state){
        printf("Open device error!\n");
        return 0;
    }
    //��ȡ�̼���Ϣ
    state = USB_GetDeviceInfo(DevIndex,&DevInfo,NULL);
    if(!state){
        printf("Get device infomation error!\n");
        return 0;
    }else{
	    printf("Firmware Name:%s\n",DevInfo.FirmwareName);
        printf("Firmware Build Date:%s\n",DevInfo.BuildDate);
        printf("Firmware Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("Hardware Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
	    printf("Firmware Functions:%08X\n",DevInfo.Functions);
    }
 
    //����SPI������ز���
    SPIConfig.Mode = 0;
    SPIConfig.ClockSpeedHz = 50000000;
    SPIConfig.CPHA = 0;
    SPIConfig.CPOL = 0;
    SPIConfig.LSBFirst = 0;
    SPIConfig.Master = 1;
    SPIConfig.SelPolarity = 0;
    ret = SPI_Init(DevIndex,SPIIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Initialize device error!\n");
        return 0;
    }
    //SPI��������
    for(int i=0;i<sizeof(WriteBuffer);i++){
        WriteBuffer[i] = i;
    }
    //ָ������Ϊ�͵�ƽ��ʱ��������
    ret = SPI_WriteBytesOfEvent(DevIndex,SPIIndex,WriteBuffer,sizeof(WriteBuffer),SPI_EVENT_P15,EVENT_TYPE_LOW,10000);
    if(ret != SPI_SUCCESS){
        printf("SPI write data error!\n");
        return 0;
    }else{
        printf("SPI_WriteBytesOfEvent Success!\n");
    }
    getchar();
    //ָ������Ϊ�ߵ�ƽ��ʱ���ȡ����
    ret = SPI_ReadBytesOfEvent(DevIndex,SPIIndex,ReadBuffer,sizeof(ReadBuffer),SPI_EVENT_P15,EVENT_TYPE_HIGH,10000);
    if(ret != SPI_SUCCESS){
        printf("SPI read data error!\n");
        return 0;
    }else{
        printf("Read Data:\n");
        for(int i=0;i<sizeof(ReadBuffer);i++){
            printf("%02X ",ReadBuffer[i]);
            if(((i+1)%16)==0){
                printf("\n");
            }
        }
        printf("\n");
    }
    getchar();
    //ָ�����ų����½��ص�ʱ��SPI�ȷ������ݣ��ٽ������ݣ���������Ƭѡ�ź�һֱ��Ч
    int IntervalTime = 10;//���ͺͽ�������֮���ʱ��������λΪus
    ret = SPI_WriteReadBytesOfEvent(DevIndex,SPIIndex,WriteBuffer,sizeof(WriteBuffer),ReadBuffer,sizeof(ReadBuffer),IntervalTime,SPI_EVENT_P15,EVENT_TYPE_FALLING,10000);
    if(ret != SPI_SUCCESS){
        printf("SPI write read data error!\n");
        return 0;
    }else{
        printf("Read Data:\n");
        for(int i=0;i<sizeof(ReadBuffer);i++){
            printf("%02X ",ReadBuffer[i]);
            if(((i+1)%16)==0){
                printf("\n");
            }
        }
        printf("\n");
    }
    getchar();
    printf("Test SPI_SUCCESS!\n");
    return 0;
}

