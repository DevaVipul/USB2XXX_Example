  /*
  ******************************************************************************
  * @file     : USB2XXXPWMTest.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX PWM test demo
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
#include "usb2pwm.h"

int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    int DevHandle[10];
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
    //��ȡ�̼���Ϣ
    char FuncStr[256]={0};
    state = DEV_GetDeviceInfo(DevHandle[0],&DevInfo,FuncStr);
    if(!state){
        printf("Get device infomation error!\n");
        return 0;
    }else{
        printf("Firmware Info:\n");
        printf("    Name:%s\n",DevInfo.FirmwareName);
        printf("    Build Date:%s\n",DevInfo.BuildDate);
        printf("    Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("    Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
        printf("    Functions:%08X\n",DevInfo.Functions);
        printf("    Functions:%s\n",FuncStr);
    }
    //����PWM��ز�������ʼ��PWM
    PWM_CONFIG PWMConfig;
    PWMConfig.ChannelMask = 0xFF;//��ʼ������ͨ��
    for(int i=0;i<8;i++){
        PWMConfig.Polarity[i] = 1;//������PWMͨ��������Ϊ������
    }
    for(int i=0;i<8;i++){
        PWMConfig.Precision[i] = 100;//������ͨ����ռ�ձȵ��ھ��ȶ�����Ϊ1%
    }
    for(int i=0;i<8;i++){
        PWMConfig.Prescaler[i] = 1;//������ͨ����Ԥ��Ƶ��������Ϊ10����PWM���Ƶ��Ϊ200MHz/(PWMConfig.Precision*PWMConfig.Prescaler)
    }
    for(int i=0;i<8;i++){
        PWMConfig.Pulse[i] = PWMConfig.Precision[i]*20/100;//������ͨ����ռ�ձȶ�����Ϊ20%
    }
    //��ʼ��PWM
    ret = PWM_Init(DevHandle[0],&PWMConfig);
    if(ret != PWM_SUCCESS){
        printf("Initialize pwm faild!\n");
        return ret;
    }else{
        printf("Initialize pwm sunccess!\n");
    }
    //������λ,����Precisionֵ�����ã����ֵ���ܴ���Precision
    unsigned short Phase[8]={0};
    Phase[0] = 0;
    Phase[1] = 0;
    Phase[2] = 0;
    Phase[3] = 0;
    ret = PWM_SetPhase(DevHandle[0],PWMConfig.ChannelMask,Phase);
    if(ret != PWM_SUCCESS){
        printf("Set pwm phase faild!\n");
        return ret;
    }else{
        printf("Set pwm phase sunccess!\n");
    }
    //����PWM,RunTimeOfUs֮���Զ�ֹͣ�����ø����Կ��Կ����������������������=RunTimeOfUs*200/(PWMConfig.Precision*PWMConfig.Prescaler)
    unsigned int RunTimeOfUs = 0;
    ret = PWM_Start(DevHandle[0],PWMConfig.ChannelMask,RunTimeOfUs);
    if(ret != PWM_SUCCESS){
        printf("Start pwm faild!\n");
        return ret;
    }else{
        printf("Start pwm sunccess!\n");
    }
    //�ı�PWM����ռ�ձ�
    /*uint16_t Plse[8];
    for(int i=0;i<100;i+=5){
        for(int j=0;j<8;j++){
            Plse[j] = i;
        }
        ret = PWM_SetPulse(DevHandle[0],PWMConfig.ChannelMask,Plse);
        if(ret != PWM_SUCCESS){
            printf("Start pwm faild!\n");
            return ret;
        }
    }
    printf("Set pulse success!\n");*/
    //ֹͣPWM
/*
    ret = PWM_Stop(DevHandle[0],PWMConfig.ChannelMask);
    if(ret != PWM_SUCCESS){
        printf("Stop pwm faild!\n");
        return ret;
    }else{
        printf("Stop pwm sunccess!\n");
    }
*/
    //�ر��豸
    USB_CloseDevice(DevHandle[0]);
	return 0;
}

