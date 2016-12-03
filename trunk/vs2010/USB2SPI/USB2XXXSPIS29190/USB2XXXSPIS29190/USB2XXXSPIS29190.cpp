  /*
  ******************************************************************************
  * @file     : USB2XXXSPIS29190.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX SPI S29190 test demo
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
#include <math.h>
#include "usb_device.h"
#include "usb2spi.h"


#define DATA_SIZE_OF_BYTE   128    //�ܵ��ֽ���
#define DATA_BITS           16
#define DATA_SIZE           (DATA_SIZE_OF_BYTE>>1)

int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    int DevIndex = 0;
    int SPIIndex = SPI1_CS0;
    bool state;
    int ret,k=0;
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
    char FuncStr[128]={0};
    state = USB_GetDeviceInfo(DevIndex,&DevInfo,FuncStr);
    if(!state){
        printf("Get device infomation error!\n");
        return 0;
    }else{
        printf("Firmware Name:%s\n",DevInfo.FirmwareName);
        printf("Firmware Build Date:%s\n",DevInfo.BuildDate);
        printf("Firmware Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("Hardware Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
        printf("Firmware Functions:%s\n",FuncStr);
    }
    //����SPI������ز���
    SPI_CONFIG SPIConfig;
    SPIConfig.Mode = SPI_MODE_SOFT_HDX;
    SPIConfig.ClockSpeedHz = 100000;
    SPIConfig.CPHA = 0;
    SPIConfig.CPOL = 0;
    SPIConfig.LSBFirst = SPI_MSB;
    SPIConfig.Master = SPI_MASTER;
    SPIConfig.SelPolarity = SPI_SEL_HIGH;
    ret = SPI_Init(DevIndex,SPIIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Initialize device error!\n");
        return 0;
    }
    //д���ݵ�оƬ
    printf("Start write data to chip...\n");
    char WriteBitsStr[256]={0};
    unsigned char PEN = 0x98;
    k = 0;
    //�ϳ������ַ���
    for(int j=0;j<8;j++){
        if(PEN&(1<<(7-j))){
            WriteBitsStr[k++] = '1';
        }else{
            WriteBitsStr[k++] = '0';
        }
    }
    //��Ч����
    for(int j=0;j<8;j++){
        WriteBitsStr[k++] = '0';
    }
    WriteBitsStr[k++] = '\0';//�ַ������������������
    ret = SPI_WriteBits(DevIndex,SPIIndex,WriteBitsStr);
    if(ret != SPI_SUCCESS){
        printf("Write bits errror!\n");
        return -1;
    }
    Sleep(1);
    unsigned short WriteDataBuffer[DATA_SIZE];
    for(int i=0;i<DATA_SIZE;i++){
        WriteDataBuffer[i] = (i<<8)|(i&0xFF);
    }
    //ѭ��������д��оƬ
    for(int i=0,addr=0;i<DATA_SIZE;addr++){
        char WriteBitsStr[256]={0};
        unsigned char PROGRAM = 0xA0;
        k = 0;
        //�ϳ������ַ���
        for(int j=0;j<8;j++){
            if(PROGRAM&(1<<(7-j))){
                WriteBitsStr[k++] = '1';
            }else{
                WriteBitsStr[k++] = '0';
            }
        }
        //�ϳɵ�ַ�ַ���
        for(int j=0;j<8;j++){
            if(addr&(1<<(7-j))){
                WriteBitsStr[k++] = '1';
            }else{
                WriteBitsStr[k++] = '0';
            }
        }
        //�ϳ����ݶ������ַ���
        for(int j=0;j<DATA_BITS;j++){
            if(WriteDataBuffer[i]&(1<<((DATA_BITS-1)-j))){
                WriteBitsStr[k++] = '1';
            }else{
                WriteBitsStr[k++] = '0';
            }
        }
        WriteBitsStr[k++] = '\0';//�ַ������������������
        //WRITE CYCLE (WRITE)
        ret = SPI_WriteBits(DevIndex,SPIIndex,WriteBitsStr);
        if(ret != SPI_SUCCESS){
            printf("Write bits errror!\n");
            return -1;
        }
        //��ӡ��ʾ����
        printf("%04X ",WriteDataBuffer[i]);
        i++;
        if((i%16)==0){
            printf("\n");
        }
        Sleep(10);
    }
    //�ϳ�PDS�Ķ���������
    unsigned char PDS = 0x80;
    k = 0;
    //�ϳ������ַ���
    for(int j=0;j<8;j++){
        if(PDS&(1<<(7-j))){
            WriteBitsStr[k++] = '1';
        }else{
            WriteBitsStr[k++] = '0';
        }
    }
    //��Ч����
    for(int j=0;j<8;j++){
        WriteBitsStr[k++] = '0';
    }
    WriteBitsStr[k++] = '\0';//�ַ������������������
    ret = SPI_WriteBits(DevIndex,SPIIndex,WriteBitsStr);
    if(ret != SPI_SUCCESS){
        printf("Write bits errror!\n");
        return -1;
    }
    //ѭ��������
    printf("Start read data from chip...\n");
    unsigned short ReadDataBuffer[DATA_SIZE];
    for(int i=0,addr=0;i<DATA_SIZE;addr++){
        char WriteBitsStr[256]={0};
        char ReadBitsStr[256]={0};
        unsigned char READ = 0xC0;
        k = 0;
        //�ϳ������ַ���
        for(int j=0;j<8;j++){
            if(READ&(1<<(7-j))){
                WriteBitsStr[k++] = '1';
            }else{
                WriteBitsStr[k++] = '0';
            }
        }
        //�ϳɵ�ַ�ַ���
        for(int j=0;j<8;j++){
            if(addr&(1<<(7-j))){
                WriteBitsStr[k++] = '1';
            }else{
                WriteBitsStr[k++] = '0';
            }
        }
        ret = SPI_WriteReadBits(DevIndex,SPIIndex,WriteBitsStr,ReadBitsStr,DATA_BITS);
        if(ret != SPI_SUCCESS){
            printf("WriteRead bits errror!\n");
            return -1;
        }else{
            //�������Ķ������ַ�����ԭΪʮ����������
            uint16_t ReadData = 0;
            for(int j=0;j<DATA_BITS;j++){
                ReadData <<= 1;
                if(ReadBitsStr[j]=='1'){
                    ReadData |= 1;
                }
            }
            //�����ݴ�ŵ����ݻ�����
            ReadDataBuffer[i] = ReadData;
            //��ӡ��ʾ����
            printf("%04X ",ReadDataBuffer[i]);
            i++;
            if((i%16)==0){
                printf("\n");
            }
        }
        Sleep(1);
    }
    return 0;
}

