/**
  ******************************************************************************
  * @file    usb2m29dw.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   usb2can相关函数和数据类型定义.
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

//6.函数返回错误代码定义
#define M29DW_SUCCESS             (0)   //函数执行成功
#define M29DW_ERR_NOT_SUPPORT     (-1)  //适配器不支持该函数
#define M29DW_ERR_USB_WRITE_FAIL  (-2)  //USB写数据失败
#define M29DW_ERR_USB_READ_FAIL   (-3)  //USB读数据失败
#define M29DW_ERR_CMD_FAIL        (-4)  //命令执行失败

#ifdef __cplusplus
extern "C"
{
#endif

int WINAPI M29DW_Init(int DevHandle);
int WINAPI M29DW_Write(int DevHandle,unsigned int StartAddr,unsigned short *pWriteData,int WriteDataLen);
int WINAPI M29DW_Read(int DevHandle,unsigned int StartAddr,unsigned short *pReadData,int ReadDataLen);

#ifdef __cplusplus
}
#endif
#endif
