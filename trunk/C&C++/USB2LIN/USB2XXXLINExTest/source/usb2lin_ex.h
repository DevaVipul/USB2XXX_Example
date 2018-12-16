                                                     /**
  ******************************************************************************
  * @file    usb2lin_ex.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   usb2lin��غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxyz.com">http://www.usbxyz.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __USB2LIN_EX_H_
#define __USB2LIN_EX_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif
//ע�⣺ʹ����Щ������Ҫ1.5.30�����ϵĹ̼���֧��
//���庯�����ش������
#define LIN_EX_SUCCESS             (0)   //����ִ�гɹ�
#define LIN_EX_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define LIN_EX_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define LIN_EX_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define LIN_EX_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��
#define LIN_EX_ERR_CH_NO_INIT      (-5)  //��ͨ��δ��ʼ��
#define LIN_EX_ERR_READ_DATA       (-6)  //LIN������ʧ��

#define LIN_EX_CHECK_STD     0	//��׼У�飬����PID
#define LIN_EX_CHECK_EXT     1	//��ǿУ�飬����PID
#define LIN_EX_CHECK_USER    2	//�Զ���У�����ͣ���Ҫ�û��Լ����㲢����Check���������Զ�У��
#define LIN_EX_CHECK_NONE    3  //��������У�����
#define LIN_EX_CHECK_ERROR   4  //��������У�����

#define LIN_EX_MASTER              1//����
#define LIN_EX_SLAVE               0//�ӻ�

#define	LIN_EX_MSG_TYPE_UN      0   //δ֪����
#define	LIN_EX_MSG_TYPE_MW		1	//������ӻ���������
#define	LIN_EX_MSG_TYPE_MR		2	//�����Ӵӻ���ȡ����
#define	LIN_EX_MSG_TYPE_SW		3	//�ӻ���������
#define	LIN_EX_MSG_TYPE_SR		4	//�ӻ���������
#define	LIN_EX_MSG_TYPE_BK		5	//ֻ����BREAK�źţ����Ƿ������������ݣ�����ֻ��⵽BREAK�ź�
#define	LIN_EX_MSG_TYPE_SY		6	//������⵽��BREAK��SYNC�ź�
#define	LIN_EX_MSG_TYPE_ID		7	//������⵽��BREAK��SYNC��PID�ź�
#define	LIN_EX_MSG_TYPE_DT		8	//������⵽��BREAK��SYNC��PID,DATA�ź�
#define	LIN_EX_MSG_TYPE_CK		9	//������⵽��BREAK��SYNC��PID,DATA,CHECK�ź�

typedef struct _LIN_EX_MSG{
    unsigned int  Timestamp;    //ʱ���
	unsigned char MsgType;	    //֡����
    unsigned char CheckType;    //У������
	unsigned char DataLen;	    //LIN���ݶ���Ч�����ֽ���
	unsigned char Sync;			//�̶�ֵ��0x55
	unsigned char PID;			//֡ID		
	unsigned char Data[8];	    //����
	unsigned char Check;		//У��,ֻ��У����������ΪLIN_EX_CHECK_USER��ʱ�����Ҫ�û���������
    unsigned char Reserve0;
    unsigned char Reserve1;
}LIN_EX_MSG,*PLIN_EX_MSG;

#ifdef __cplusplus
extern "C"
{
#endif

int WINAPI  LIN_EX_Init(int DevHandle,unsigned char LINIndex,unsigned int BaudRate,unsigned char MasterMode);
int WINAPI  LIN_EX_MasterSync(int DevHandle,unsigned char LINIndex,LIN_EX_MSG *pInMsg,LIN_EX_MSG *pOutMsg,unsigned int MsgLen);
int WINAPI  LIN_EX_SlaveSetIDMode(int DevHandle,unsigned char LINIndex,LIN_EX_MSG *pLINMsg,unsigned int MsgLen);
int WINAPI  LIN_EX_SlaveGetData(int DevHandle,unsigned char LINIndex,LIN_EX_MSG *pLINMsg);

#ifdef __cplusplus
}
#endif
#endif

