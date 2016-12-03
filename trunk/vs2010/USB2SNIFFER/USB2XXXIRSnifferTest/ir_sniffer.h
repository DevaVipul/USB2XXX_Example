/**
  ******************************************************************************
  * @file    ir_sniffer.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   ir sniffer��غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxyz.com">http://www.usbxyz.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __IR_SNIFFER_H_
#define __IR_SNIFFER_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

#define DECODE_WINDOW_SIZE  4

typedef struct _IRTimeSeries{
  int   DataTime;//���DataType��ʱ�䣬��λΪ0.25us
  char  DataType;//1-����ߵ�ƽ���ߵ��Ʋ���0-����͵�ƽ���߲�������Ʋ�
}IRTimeSeries,*PIRTimeSeries;

//������I2C���ݺ�Ļص�����
typedef  int (WINAPI IR_GET_DATA_HANDLE)(int DeviceIndex,int Channel,PIRTimeSeries pIRData,int IRDataNum);

//���庯�����ش������
#define SUCCESS             (0)   //����ִ�гɹ�
#define ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define ERR_CMD_FAIL        (-4)  //����ִ��ʧ��

#ifdef __cplusplus
extern "C"
{
#endif
	int WINAPI IR_SnifferStart(int DevIndex,int Channel,unsigned int SampleRateHz,IR_GET_DATA_HANDLE *pGetIRDataHandle);
	int WINAPI IR_SnifferStop(int DevIndex);
#ifdef __cplusplus
}
#endif

#endif
