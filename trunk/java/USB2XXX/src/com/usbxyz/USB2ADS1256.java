package com.usbxyz;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

public interface USB2ADS1256 extends Library {
	USB2ADS1256 INSTANCE  = (USB2ADS1256)Native.loadLibrary("USB2XXX",USB2ADS1256.class); 
	//���庯�����ش������
	public static int ADS1256_SUCCESS             =(0);   //����ִ�гɹ�
	public static int ADS1256_ERR_NOT_SUPPORT     =(-1);  //��������֧�ָú���
	public static int ADS1256_ERR_USB_WRITE_FAIL  =(-2);  //USBд����ʧ��
	public static int ADS1256_ERR_USB_READ_FAIL   =(-3);  //USB������ʧ��
	public static int ADS1256_ERR_CMD_FAIL        =(-4);  //����ִ��ʧ��
	public static int ADS1256_ERR_CH_NO_INIT      =(-5);  //��ͨ��δ��ʼ��

	//����ADS������
	public static int ADS1256_DRATE_30000SPS   =0xF0; 
	public static int ADS1256_DRATE_15000SPS   =0xE0; 
	public static int ADS1256_DRATE_7500SPS    =0xD0; 
	public static int ADS1256_DRATE_3750SPS    =0xC0; 
	public static int ADS1256_DRATE_2000SPS    =0xB0; 
	public static int ADS1256_DRATE_1000SPS    =0xA1; 
	public static int ADS1256_DRATE_500SPS     =0x92; 
	public static int ADS1256_DRATE_100SPS     =0x82; 
	public static int ADS1256_DRATE_60SPS      =0x72; 
	public static int ADS1256_DRATE_50SPS      =0x63; 
	public static int ADS1256_DRATE_30SPS      =0x53; 
	public static int ADS1256_DRATE_25SPS      =0x43; 
	public static int ADS1256_DRATE_15SPS      =0x33; 
	public static int ADS1256_DRATE_10SPS      =0x23; 
	public static int ADS1256_DRATE_5SPS       =0x13; 
	public static int ADS1256_DRATE_2_5SPS     =0x03;

	//�����ʼ��ADS1256����������
	public class ADS1256_CONFIG  extends Structure{
		
	    public static class ByReference extends ADS1256_CONFIG implements Structure.ByReference {}  
	    public static class ByValue extends ADS1256_CONFIG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"SampleRate","PGA","BufferEn","SampleMode"});
		}

		short  SampleRate;   //������
		byte   PGA;          //�ڲ����棬2^n
		byte   BufferEn;     //1��ʹ��Buffer,0����ֹBuffer
		int    SampleMode;   //����bit����һ��ͨ����00����ʹ�ø�ͨ����01����ͨ��Ϊ����ģʽ��10����ͨ��Ϊ��ָ�����11����ͨ��Ϊ�������
	};
	/**
	  * @brief  ��ʼ������ADS1256
	  * @param  DevHandle �豸���
	  * @param  Channel ��Ҫ���õ�ADSͨ���ţ�ȡֵ0����1
	  * @param  pConfig ADS1256���ò���ָ��
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  ADS1256_Init(int DevHandle,char Channel,ADS1256_CONFIG pConfig);
	/**
	  * @brief  ����ADSת�������øú��������������Զ���ȡADSת������
	  * @param  DevHandle �豸���
	  * @param  Channel ��Ҫ������ADSͨ���ţ�ȡֵ0����1
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  ADS1256_Start(int DevHandle,char Channel);
	/**
	  * @brief  ����ADC����ת��ģʽ
	  * @param  DevHandle �豸���
	  * @param  Channel ��Ҫ��ȡ���ݵ�ADSͨ���ţ�ȡֵ0����1
	  * @param  pData ���ݴ洢�������׵�ַ
	  * @retval ����ִ��״̬��С��0����ִ�г�������0Ϊʵ�ʲɼ�����ADC����
	  */
	int  ADS1256_Read(int DevHandle,char Channel,int[] pData);
	/**
	  * @brief  ֹͣADSת�������øú��������������Զ�ֹͣADSת������
	  * @param  DevHandle �豸���
	  * @param  Channel ��Ҫ������ADSͨ���ţ�ȡֵ0����1
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  ADS1256_Stop(int DevHandle,char Channel);

}
