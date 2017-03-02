package com.usbxyz;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

public interface USB2PWM extends Library {
	USB2PWM INSTANCE  = (USB2PWM)Native.loadLibrary("USB2XXX",USB2PWM.class); 
	//���庯�����ش������
	public static int PWM_SUCCESS             =(0);   //����ִ�гɹ�
	public static int PWM_ERR_NOT_SUPPORT     =(-1);  //��������֧�ָú���
	public static int PWM_ERR_USB_WRITE_FAIL  =(-2);  //USBд����ʧ��
	public static int PWM_ERR_USB_READ_FAIL   =(-3);  //USB������ʧ��
	public static int PWM_ERR_CMD_FAIL        =(-4);  //����ִ��ʧ��
	
	public class PWM_CONFIG  extends Structure{
		
	    public static class ByReference extends PWM_CONFIG implements Structure.ByReference {}  
	    public static class ByValue extends PWM_CONFIG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"Prescaler","Precision","Pulse","Polarity","ChannelMask"});
		}

		short[] Prescaler = new short[8];  //Ԥ��Ƶ��
		short[] Precision = new short[8];  //ռ�ձȵ��ھ���
		short[] Pulse = new short[8];      //ռ�ձȣ�ʵ��ռ�ձ�=(Pulse/Precision)*100%
		byte[]  Polarity = new byte[8];    //���μ��ԣ�ȡֵ0����1
		byte  	ChannelMask;    //ͨ���ţ���Ҫʹ��ĳ��ͨ�������ӦλΪ1�����λ��Ӧͨ��0
	};
	
	int  PWM_Init(int DevIndex, PWM_CONFIG pConfig);
	int  PWM_Start(int DevIndex,byte ChannelMask,int RunTimeUs);
	int  PWM_SetPulse(int DevIndex,byte ChannelMask,short[] pPulse);
	int  PWM_Stop(int DevIndex,byte ChannelMask);
}
