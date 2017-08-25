  /*
  ******************************************************************************
  * @file     : USB2XXXLINTest.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX LIN test demo
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
#include "usb2lin.h"

int main(int argc, const char* argv[])
{
#if GET_FIRMWARE_INFO
    DEVICE_INFO DevInfo;
#endif
    int DevHandle[10];
    int LINMasterIndex = 0;
    int LINSlaveIndex = 1;
    bool state;
    int ret;
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
#if GET_FIRMWARE_INFO
    char FunctionStr[256]={0};
    //��ȡ�̼���Ϣ
    state = DEV_GetDeviceInfo(DevHandle[0],&DevInfo,FunctionStr);
    if(!state){
        printf("Get device infomation error!\n");
        return 0;
    }else{
        printf("Firmware Info:\n");
	    printf("Firmware Name:%s\n",DevInfo.FirmwareName);
        printf("Firmware Build Date:%s\n",DevInfo.BuildDate);
        printf("Firmware Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("Hardware Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
	    printf("Firmware Functions:%s\n",FunctionStr);
    }
#endif
    //��ʼ������LIN
    LIN_CONFIG LINConfig;
    LINConfig.BaudRate = 10000;
    LINConfig.BreakBits = LIN_BREAK_BITS_11;
    LINConfig.CheckMode = LIN_CHECK_MODE_EXT;
    LINConfig.MasterMode = LIN_MASTER;
    ret = LIN_Init(DevHandle[0],LINMasterIndex,&LINConfig);
    if(ret != LIN_SUCCESS){
        printf("Config LIN failed!\n");
        return 0;
    }else{
        printf("Config LIN Success!\n");
    }

    LINConfig.BaudRate = 10000;
    LINConfig.BreakBits = LIN_BREAK_BITS_11;
    LINConfig.CheckMode = LIN_CHECK_MODE_EXT;
    LINConfig.MasterMode = LIN_SLAVE;
    ret = LIN_Init(DevHandle[0],LINSlaveIndex,&LINConfig);
    if(ret != LIN_SUCCESS){
        printf("Config LIN failed!\n");
        return 0;
    }else{
        printf("Config LIN Success!\n");
    }
    //���ôӻ�LIN IDΪ0x00�Ĳ���ģʽΪ�ӽ�������ģʽ����ID�������LINSlaveData.DataLen�ֽڵ�����
    SLAVE_LIN_DATA LINSlaveData;
    LINSlaveData.DataLen = 8;
    LINSlaveData.WorkMode = LIN_SLAVE_READ;
    ret = LIN_SlaveSetIDOperation(DevHandle[0],LINSlaveIndex,0x00,LINSlaveData);
    if(ret != LIN_SUCCESS){
        printf("Set LIN operation mode failed!\n");
        return 0;
    }else{
        printf("Set LIN operation mode success!\n");
    }
    //���ôӻ�LIN IDΪ0x01�Ĳ���ģʽΪ�ӷ�������ģʽ����ID�������LINSlaveData.DataLen�ֽڵ�����
    LINSlaveData.DataLen = 8;
    LINSlaveData.WorkMode = LIN_SLAVE_WRITE;
    for(int i=0;i<LINSlaveData.DataLen;i++){
        LINSlaveData.Data[i] = i;
    }
    ret = LIN_SlaveSetIDOperation(DevHandle[0],LINSlaveIndex,0x01,LINSlaveData);
    if(ret != LIN_SUCCESS){
        printf("Set LIN operation mode failed!\n");
        return 0;
    }else{
        printf("Set LIN operation mode success!\n");
    }

    //����д����
    unsigned char write_buffer[8];
    for(int i=0;i<8;i++){
        write_buffer[i] = 8+i;
    }
    unsigned char ID = 0x00;
    ret = LIN_WriteData(DevHandle[0],LINMasterIndex,ID,write_buffer,8);
    if(ret != LIN_SUCCESS){
        printf("LIN write data failed!\n");
        return 0;
    }else{
        printf("LIN write data success!\n");
    }
    Sleep(10);
    //������������֮�󣬿��Զ�ȡ�ӻ����յ�������
    SLAVE_LIN_DATA LINSlaveDataBuffer[1024];//Ϊ�˷�ֹ��������������Խ��������ݻ��������ô�һ��
    ret = LIN_SlaveGetData(DevHandle[0],LINSlaveIndex,LINSlaveDataBuffer);
    if(ret < LIN_SUCCESS){
        printf("LIN slave read data error!\n");
        return 0;
    }else if(ret == 0){
        printf("LIN slave read no data!\n");
    }else{
        for(int i=0;i<ret;i++){
            printf("Data[%d]: ",i);
            printf("ID = 0x%02X ",LINSlaveDataBuffer[i].Data[0]&0x3F);
            printf("Data = ");
            for(int j=0;j<LINSlaveDataBuffer[i].DataLen;j++){
                printf("0x%02X ",LINSlaveDataBuffer[i].Data[1+j]);
            }
            printf("\n");
        }
    }
    //����������
    ID = 0x01;
    uint8_t read_buffer[9];
    ret = LIN_ReadData(DevHandle[0],LINMasterIndex,ID,read_buffer);
    if(ret < LIN_SUCCESS){
        printf("LIN read data failed!\n");
        return 0;
    }else if(ret == LIN_SUCCESS){
        printf("LIN read data no data!\n");
        return 0;
    }else{
        printf("LIN Read: ");
        for(int i=0;i<ret;i++){
            printf("0x%02X ",read_buffer[i]);
        }
        printf("\n");
    }
    //�ر��豸
    USB_CloseDevice(DevHandle[0]);
	return 0;
}

