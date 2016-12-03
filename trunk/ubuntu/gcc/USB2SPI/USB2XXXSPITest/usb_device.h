/**
  ******************************************************************************
  * @file    usb_device.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   USB���ò�����غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxzy.com">http://www.usbxzy.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __USB_DEVICE_H_
#define __USB_DEVICE_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

typedef struct _DEVICE_INFO
{
    char    FirmwareName[32];   //�̼������ַ���
    char    BuildDate[32];      //�̼�����ʱ���ַ���
    int     HardwareVersion;    //Ӳ���汾��
    int     FirmwareVersion;    //�̼��汾��
    int     SerialNumber[3];    //���������к�
    int     Functions;          //��������ǰ�߱��Ĺ���
}DEVICE_INFO,*PDEVICE_INFO;

#ifdef __cplusplus
extern "C"
{
#endif

    int  WINAPI USB_ScanDevice(int *pDevNum);
    bool WINAPI USB_OpenDevice(int DevIndex);
    bool WINAPI USB_CloseDevice(int DevIndex);
    bool WINAPI USB_GetDeviceInfo(int DevIndex,PDEVICE_INFO pDevInfo,char *pFunctionStr);

#ifdef __cplusplus
}
#endif

#endif

