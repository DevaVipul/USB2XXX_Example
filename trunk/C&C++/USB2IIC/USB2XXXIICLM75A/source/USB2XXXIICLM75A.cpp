  /*
  ******************************************************************************
  * @file     : USB2XXXIICLM75A.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX IIC test demo
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
#include "usb2iic.h"

#define GET_FIRMWARE_INFO   1

int main(int argc, const char* argv[])
{
#if GET_FIRMWARE_INFO
    DEVICE_INFO DevInfo;
#endif
    char IICChannel[8]={};
    int DevHandle[10];
    int IICIndex = 0;
    bool state;
    unsigned char WriteBuffer[8];
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
    IICIndex = 0;
    for(int i=0;i<8;i++){
        //��ʼ������I2C
        IIC_CONFIG IIC_Config;
        IIC_Config.EnablePu = 1;            //ʹ���ڲ���������
        IIC_Config.AddrBits = 7;            //7bit��ַģʽ
        IIC_Config.ClockSpeedHz = 400000;   //ʱ��Ƶ��400KHz
        IIC_Config.Master = 1;              //����ģʽ
        ret = IIC_Init(DevHandle[0],i,&IIC_Config);
        if(ret != IIC_SUCCESS){
            printf("Config IIC failed!\n");
            return 0;
        }else{
            printf("Config IIC IIC_SUCCESS!\n");
        }
        //��⵱ǰͨ���������Ƿ�����
        //�����������������ô�����
        WriteBuffer[0] = 0x01;
        WriteBuffer[1] = 0x00;
        ret = IIC_WriteBytes(DevHandle[0],i,0x48,WriteBuffer,2,10);
        if(ret == IIC_SUCCESS){
            IICChannel[IICIndex++] = i;
        }
    }
    printf("��⵽%d������������\n",IICIndex);
    int ErrorDataCnt = 0;
    int ErrorReadCnt[8]={0};
    int ReadDataCnt = 0;
    while(true)
    {
        system("cls");//���֮ǰ��ʾ��Ϣ
        double Temperature[8];
        for(int i=0;i<IICIndex;i++){
            //��ȡ����������
            unsigned char ReadBuffer[8];
            WriteBuffer[0] = 0x00;
            ret = IIC_WriteReadBytes(DevHandle[0],IICChannel[i],0x48,WriteBuffer,1,ReadBuffer,2,10);
            if (ret != IIC_SUCCESS){
                printf("Read IIC failed!  %d\n",ret);
                ErrorReadCnt[i]++;//�����ݳ��������һ
            }else{
                short Temp = ((ReadBuffer[0] << 8) | ReadBuffer[1]);
                Temp >>= 5;
                Temperature[i] = Temp*0.125;
                printf("Temperature[I2C-%d]: %.1f\n",IICChannel[i],Temperature[i]);//��ʾ�¶�ֵ
            }
        }
        //�����ȡ�����¶�ֵ���ֵ����Сֵ֮��
        double MaxValue = Temperature[0],MinValue = Temperature[0];
        for(int i=0;i<IICIndex;i++){
            if(Temperature[i] > MaxValue){
                MaxValue = Temperature[i];
            }
            if(Temperature[i] < MinValue){
                MinValue = Temperature[i];
            }
        }
        //�����Сֵ���ﵽ1�����ж���������
        if((MaxValue-MinValue)>1){
            ErrorDataCnt++;
        }
        //��ʾ�����ݳ������
        for(int i=0;i<IICIndex;i++){
            printf("ErrorReadCnt[I2C-%d] = %d\n",IICChannel[i],ErrorReadCnt[i]);
        }
        //��ʾ�ɹ������ݵ�����������Ĵ���
        printf("ErrorDataCnt = %d\n",ErrorDataCnt);
        //���¶ȴ�����һ
        ReadDataCnt++;
        printf("ReadDataCnt = %d\n",ReadDataCnt);
        //��ʱ
#ifndef OS_UNIX
        Sleep(50);
#else
        usleep(100*1000);
#endif
    }
    return 0;
}