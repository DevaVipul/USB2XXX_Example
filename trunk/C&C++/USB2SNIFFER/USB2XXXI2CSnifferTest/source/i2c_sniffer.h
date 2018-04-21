/**
  ******************************************************************************
  * @file    i2c_sniffer.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   i2c sniffer��غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxyz.com">http://www.usbxyz.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __I2C_SNIFFER_H_
#define __I2C_SNIFFER_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

#define DECODE_WINDOW_SIZE  2//12

typedef enum
{ 
    UNKNOWN = 0x00,
    START,
    ADDR,
    DATA,
    STOP
}I2C_DATA_TYPE;

typedef struct
{
    unsigned char DataType;
    unsigned char ACK;
    unsigned char WriteRead;
    unsigned char Data;
    unsigned short Addr;
    long long Timestamp;
}I2C_DATA;

//������I2C���ݺ�Ļص�����
typedef  int (WINAPI I2C_GET_DATA_HANDLE)(int DevHandle,int Channel,I2C_DATA *pI2CData,int I2CDataNum);

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
	int WINAPI I2C_SnifferStart(int DevHandle,int Channel,unsigned int SampleRateHz,I2C_GET_DATA_HANDLE *pGetI2CDataHandle);
	int WINAPI I2C_SnifferStop(int DevHandle);
#ifdef __cplusplus
}
#endif

#endif
