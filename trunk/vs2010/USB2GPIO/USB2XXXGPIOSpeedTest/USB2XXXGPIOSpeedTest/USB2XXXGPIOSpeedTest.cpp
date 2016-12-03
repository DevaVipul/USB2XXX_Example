  /*
  ******************************************************************************
  * @file     : USB2XXXGPIOSpeedTest.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX GPIO speed test demo
  ******************************************************************************
  * @attention
  *
  * Copyright 2009-2014, usbxyz.com
  * http://www.usbxyz.com/
  * All Rights Reserved
  * 
  ******************************************************************************
  */
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "usb2gpio.h"
#include "usb_device.h"


int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    int DevIndex = 0;
    bool state;
    int ret;
    unsigned int PinValue;
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
    char FuncStr[256]={0};
    state = USB_GetDeviceInfo(DevIndex,&DevInfo,FuncStr);
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
    //������ԡ���û������
    GPIO_SetOutput(DevIndex,0xFFFF,1);
    //��ȡ��ʼʱ��,��Ҫ���ڲ��Է����ٶ�
    LARGE_INTEGER litmp;
    LONGLONG StartTime,EndTime;
    double dfFreq;
    QueryPerformanceFrequency(&litmp);// Get the performance counter frequency, in n/s
    dfFreq = (double)litmp.QuadPart;
    QueryPerformanceCounter(&litmp);  // Get the current value of the performance counter
    StartTime = litmp.QuadPart;       // Start time
    int TestNum = 100000;
    CRITICAL_SECTION  _critical;
    /*��ʼ�������ȵ��õĺ�����ûʲô��˵�ģ�һ��windows��̶������Ƴ�ʼ���ķ���*/
    InitializeCriticalSection(&_critical);
    /*
    �Ѵ��뱣�����������ô˺��������Ժ����Դ�����߳̾Ͳ��ܷ����ˡ�
    */
    EnterCriticalSection(& _critical);
    for(int i=0;i<TestNum;i++){
        GPIO_Write(DevIndex,0xFFFF,0xFFFF);
        GPIO_Write(DevIndex,0xFFFF,0x0000);
    }
    /*
    �뿪�ٽ�������ʾ�����߳��ܹ������ˡ�ע��EnterCritical��LeaveCrticalSection�����ǳɶԳ��ֵ�!��Ȼ�������������������
    */
    LeaveCriticalSection(&_critical);
    /*�ͷ���Դ��ȷ����ʹ��_criticalʱ���ã�һ���ڳ����˳���ʱ����á�����Ժ�Ҫ��_critical����Ҫ���µ���InitializeCriticalSection
    */
    DeleteCriticalSection(&_critical); 
	//��ȡ����ʱ�䲢��ӡ�����ʱ���ٶ�
    QueryPerformanceCounter(&litmp);// Get the current value of the performance counter
    EndTime = litmp.QuadPart; // Stop time
	// Print the write data speed information
	printf("-----------------------www.usbxyz.com-----------------------\n");
	printf("����GPIO����: %d  \n",TestNum*2);
	printf("������ʱ��: %f s\n",(EndTime-StartTime)/dfFreq);
	printf("����GPIO���ٶ�: %.3f ��/s\n",(TestNum*2)/((EndTime-StartTime)/dfFreq));
	printf("-----------------------www.usbxyz.com-----------------------\n");

    //�ر��豸
    USB_CloseDevice(DevIndex);
    return 0;
}

