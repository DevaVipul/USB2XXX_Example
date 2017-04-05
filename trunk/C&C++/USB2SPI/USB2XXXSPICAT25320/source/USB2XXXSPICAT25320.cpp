  /*
  ******************************************************************************
  * @file     : USB2XXXSPICAT25320.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX SPI CAT25320 test demo
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

#define DATA_SIZE   256    //�ܵ��ֽ���

int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    unsigned char WriteBuffer[8]={0};
    unsigned char ReadDataBuffer[8];
    int DevHandle[10];
    int SPIIndex = SPI1_CS0;
    bool state;
    int ret,k=0;
    //ɨ������豸
    ret = USB_ScanDevice(DevHandle);
    if(ret <= 0){
        printf("No device connected!\n");
        return 0;
    }
    //���豸
    state = USB_OpenDevice(DevHandle[0]);
    if(!state){
        printf("Open device error!\n");
        return 0;
    }
    //��ȡ�̼���Ϣ
    char FuncStr[128]={0};
    state = DEV_GetDeviceInfo(DevHandle[0],&DevInfo,FuncStr);
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
    SPIConfig.Mode = SPI_MODE_SOFT_HDX;//��оƬ֧�ֵ�ʱ��Ƶ�ʽϵͣ�����ʹ�����ģʽ
    SPIConfig.ClockSpeedHz = 100000;
    SPIConfig.CPHA = 0;
    SPIConfig.CPOL = 0;
    SPIConfig.LSBFirst = SPI_MSB;
    SPIConfig.Master = SPI_MASTER;
    SPIConfig.SelPolarity = SPI_SEL_LOW;
    ret = SPI_Init(DevHandle[0],SPIIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Initialize device error!\n");
        return 0;
    }
    //д���ݵ�оƬ
    printf("Start write data to chip...\n");
    //ѭ��������д��оƬ
    for(int i=0,addr=0;i<DATA_SIZE;addr++){
        //����WREN����
        WriteBuffer[0]=0x06;
        ret = SPI_WriteBytes(DevHandle[0],SPIIndex,WriteBuffer,1);
        if(ret != SPI_SUCCESS){
            printf("Write byte error!\n");
            return -1;
        }
        k = 0;
        //д����
        WriteBuffer[k++] = 0x02;//WRITE����
        WriteBuffer[k++] = addr>>8;//��ַ��8λ
        WriteBuffer[k++] = addr&0xFF;//��ַ��8λ
        WriteBuffer[k++] = i&0xFF;//����д��õ�ַ������
        ret = SPI_WriteBytes(DevHandle[0],SPIIndex,WriteBuffer,4);
        if(ret != SPI_SUCCESS){
            printf("Write byte error!\n");
            return -1;
        }
        //��ȡ״̬
        k = 0;
        //��ȡ״̬,һֱ�ȵ�RDYλΪ0Ϊֹ
        do{
            WriteBuffer[k++] = 0x05;//RDSR����
            ret = SPI_WriteReadBytes(DevHandle[0],SPIIndex,WriteBuffer,1,ReadDataBuffer,1,0);
            if(ret != SPI_SUCCESS){
                printf("WriteRead byte error!\n");
                return -1;
            }
        }while((ReadDataBuffer[0]&0x01)!=0x00);
        //��ʾ����
        printf("%02X ",i&0xFF);
        i++;
        if((i%16)==0){
            printf("\n");
        }
    }
    //ѭ��������
    printf("Start read data from chip...\n");
    for(int i=0,addr=0;i<DATA_SIZE;addr++){
        k = 0;
        //�ϳ�READ����
        WriteBuffer[k++] = 0x03;//READ����
        WriteBuffer[k++] = addr>>8;//��ַ��8λ
        WriteBuffer[k++] = addr&0xFF;//��ַ��8λ
        ret = SPI_WriteReadBytes(DevHandle[0],SPIIndex,WriteBuffer,3,ReadDataBuffer,1,0);
        if(ret != SPI_SUCCESS){
            printf("WriteRead byte error!\n");
            return -1;
        }else{
            //��ӡ��ʾ����
            printf("%02X ",ReadDataBuffer[0]);
            i++;
            if((i%16)==0){
                printf("\n");
            }
        }
        Sleep(1);
    }
    return 0;
}


