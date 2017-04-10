package com.usbxyz;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface USB2GPIO extends Library {
	USB2GPIO INSTANCE  = (USB2GPIO)Native.loadLibrary("USB2XXX",USB2GPIO.class); 
	//���庯�����ش������
	public static int GPIO_SUCCESS             =(0);   //����ִ�гɹ�
	public static int GPIO_ERR_NOT_SUPPORT     =(-1);  //��������֧�ָú���
	public static int GPIO_ERR_USB_WRITE_FAIL  =(-2);  //USBд����ʧ��
	public static int GPIO_ERR_USB_READ_FAIL   =(-3);  //USB������ʧ��
	public static int GPIO_ERR_CMD_FAIL        =(-4);  //����ִ��ʧ��
	
	/**
	  * @brief  ��GPIO��������Ϊ����ģʽ
	  * @param  DevHandle �豸������
	  * @param  PinMask ��Ҫ����Ϊ����ģʽ�����ţ�ÿ��bitλ����һ�����ţ���ӦbitλΪ1ʱ�����Ŷ�������Ч�����λΪP0
	  * @param  PuPd 0-�������룬����������������1-�������룬2-��������
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  GPIO_SetInput(int DevHandle,int PinMask, byte PuPd);
	/**
	  * @brief  ��GPIO��������Ϊ���ģʽ
	  * @param  DevHandle �豸������
	  * @param  PinMask ��Ҫ����Ϊ���ģʽ�����ţ�ÿ��bitλ����һ�����ţ���ӦbitλΪ1ʱ�����Ŷ�������Ч�����λ��ӦP0
	  * @param  PuPd 0-�������������������������1-���������2-�������
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  GPIO_SetOutput(int DevHandle,int PinMask, byte PuPd);
	/**
	  * @brief  ��GPIO��������Ϊ��©ģʽ����ģʽ�¿���Ϊ˫������
	  * @param  DevHandle �豸������
	  * @param  PinMask ��Ҫ����Ϊ��©ģʽ�����ţ�ÿ��bitλ����һ�����ţ���ӦbitλΪ1ʱ�����Ŷ�������Ч�����λ��ӦP0
	  * @param  PuPd 0-�ڲ�����������������1-ʹ��������2-ʹ������
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  GPIO_SetOpenDrain(int DevHandle,int PinMask, byte PuPd);
	/**
	  * @brief  ����GPIO���ŵ����״̬
	  * @param  DevHandle �豸������
	  * @param  PinMask ��Ҫ���״̬�����ţ�ÿ��bitλ����һ�����ţ���ӦbitλΪ1ʱ�����Ŷ�������Ч�����λ��ӦP0
	  * @param  PinValue ��Ӧ���ŵ�״̬��ÿ��bitλ����һ�����ţ���ӦbitλΪ1����ߵ�ƽ��Ϊ0����͵�ƽ�����λ��ӦP0
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  GPIO_Write(int DevHandle,int PinMask, int PinValue);
	/**
	  * @brief  ��ȡGPIO���ŵ�����״̬
	  * @param  DevHandle �豸������
	  * @param  PinMask ��Ҫ��ȡ״̬�����ţ�ÿ��bitλ����һ�����ţ���ӦbitλΪ1ʱ�����Ŷ�������Ч�����λ��ӦP0
	  * @param  pPinValue ��Ӧ���ŵ�״̬��ÿ��bitλ����һ�����ţ���ӦbitλΪ1����Ϊ�ߵ�ƽ��Ϊ0����Ϊ�͵�ƽ�����λ��ӦP0
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  GPIO_Read(int DevHandle,int PinMask, int[] pPinValue);

}
