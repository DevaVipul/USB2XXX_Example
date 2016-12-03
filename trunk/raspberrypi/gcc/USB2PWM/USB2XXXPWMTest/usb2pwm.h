/**
  ******************************************************************************
  * @file    usb2pwm.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   usb2pwm��غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxyz.com">http://www.usbxyz.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __USB2PWM_H_
#define __USB2PWM_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

//�����ʼ��PWM����������
typedef struct _PWM_CONFIG{
  uint16_t Prescaler[8];  //Ԥ��Ƶ��
  uint16_t Precision[8];  //ռ�ձȵ��ھ���
  uint16_t Pulse[8];      //ռ�ձȣ�ʵ��ռ�ձ�=(Pulse/Precision)*100%
  uint8_t Polarity[8];    //���μ���
  uint8_t ChannelMask;    //ͨ����
}PWM_CONFIG,*PPWM_CONFIG;

//���庯�����ش������
#define PWM_SUCCESS             (0)   //����ִ�гɹ�
#define PWM_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define PWM_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define PWM_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define PWM_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��

#ifdef __cplusplus
extern "C"
{
#endif

int WINAPI PWM_Init(int DevIndex, PPWM_CONFIG pConfig);
int WINAPI PWM_Start(int DevIndex,unsigned char ChannelMask,unsigned int RunTimeUs);
int WINAPI PWM_Stop(int DevIndex,unsigned char ChannelMask);

#ifdef __cplusplus
}
#endif
#endif
