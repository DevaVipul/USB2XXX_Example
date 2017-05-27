/**
  ******************************************************************************
  * @file    usb2m29dw.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   usb2can��غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxyz.com">http://www.usbxyz.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __USB2M29DW_H_
#define __USB2M29DW_H_

#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

//6.�������ش�����붨��
#define M29DW_SUCCESS             (0)   //����ִ�гɹ�
#define M29DW_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define M29DW_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define M29DW_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define M29DW_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��
#define M29DW_ERR_TIME_OUT        (-5)
#ifdef __cplusplus
extern "C"
{
#endif

int WINAPI M29DW_Init(int DevHandle);
int WINAPI M29DW_WriteData(int DevHandle,unsigned int StartAddr,unsigned short *pWriteData,int WriteDataLen);
int WINAPI M29DW_ReadData(int DevHandle,unsigned int StartAddr,unsigned short *pReadData,int ReadDataLen);
int WINAPI M29DW_BlockErase(int DevHandle,unsigned int BlockAddr);
int WINAPI M29DW_ReadID(int DevHandle,unsigned short *pManufacturerCode,unsigned short *pDeviceCode);

#ifdef __cplusplus
}
#endif
#endif
