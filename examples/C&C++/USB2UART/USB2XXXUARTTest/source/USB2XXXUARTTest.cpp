  /*
  ******************************************************************************
  * @file     : USB2XXXUARTTest.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX UART test demo
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
#include "usb2uart.h"


int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    UART_CONFIG UARTConfig;
    int DevHandle[10];
    int UARTIndex = 1;
    bool state;
    int ret;
    unsigned char WriteBuffer[256];
    unsigned char ReadBuffer[20480];
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
    state = DEV_GetDeviceInfo(DevHandle[0],&DevInfo,NULL);
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

    //����UART������ز���
    UARTConfig.BaudRate = 115200;
    UARTConfig.Parity = UART_PARITY_NO;
    UARTConfig.StopBits = UART_STOP_BITS_1;
    UARTConfig.WordLength = UART_WORD_LENGTH_8BIT;
    UARTConfig.TEPolarity = 0x40;
    ret = UART_Init(DevHandle[0],0,&UARTConfig);
    ret = UART_Init(DevHandle[0],UARTIndex,&UARTConfig);
    if(ret != UART_SUCCESS){
        printf("Initialize device error!\n");
        return 0;
    }
    //UART��������
    for(int i=0;i<sizeof(WriteBuffer);i++){
        WriteBuffer[i] = i;
    }
    ret = UART_WriteBytes(DevHandle[0],UARTIndex,WriteBuffer,sizeof(WriteBuffer));
    if(ret != UART_SUCCESS){
        printf("UART write data error!\n");
        return 0;
    }
    //SPI�첽�������ݣ����øú�������������أ�����SPI���ݲ�һ��������ϣ���������һ�η�������֮ǰ�ᱣ֤���ݷ������
    for(int i=0;i<64;i++){
        ret = UART_WriteBytesAsync(DevHandle[0],UARTIndex,WriteBuffer,sizeof(WriteBuffer));
        if(ret != UART_SUCCESS){
            printf("UART async write data error!\n");
            return 0;
        }
    }
    //UART��������
    printf("Read Bytes:\n");
    int ReadDataNum = 0;
    int Time = 2000;
    while(Time > 0){
        ret = UART_ReadBytes(DevHandle[0],UARTIndex,ReadBuffer,10);
        if(ret > 0){
            ReadDataNum += ret;
            for(int i=0;i<ret;i++){
                printf("%02X ",ReadBuffer[i]);
                if(((i+1)%16)==0){
                    printf("\n");
                }
            }
            //printf("ret = %d\n",ret);
            printf("\nReadDataNum = %d\n",ReadDataNum);
        }else if(ret < 0){
            printf("ret = %d\n",ret);
        }
        Sleep(10);
        Time -= 10;
    }
    printf("Test UART_SUCCESS!\n");
    return 0;
}

