package com.usbxyz;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

public interface USB2CNT extends Library {
	USB2CNT INSTANCE  = (USB2CNT)Native.loadLibrary("USB2XXX",USB2CNT.class); 
	//���庯�����ش������
	public static int CNT_SUCCESS             =(0);   //����ִ�гɹ�
	public static int CNT_ERR_NOT_SUPPORT     =(-1);  //��������֧�ָú���
	public static int CNT_ERR_USB_WRITE_FAIL  =(-2);  //USBд����ʧ��
	public static int CNT_ERR_USB_READ_FAIL   =(-3);  //USB������ʧ��
	public static int CNT_ERR_CMD_FAIL        =(-4);  //����ִ��ʧ��
	//������ģʽ
	public static byte COUNTER_MODE_UP     =0;
	public static byte COUNTER_MODE_DOWN   =1;
	//��������������
	public static byte COUNTER_POL_RISING     =0;
	public static byte COUNTER_POL_FALLING    =1;
	public static byte COUNTER_POL_BOTHEDGE   =2;
	//���������
	public static byte COUNTER_BITS16        =16;
	public static byte COUNTER_BITS32        =32;
	//��������������ģʽ
	public static byte  COUNTER_PIN_NOPULL     =0x00;
	public static byte  COUNTER_PIN_UP         =0x01;
	public static byte  COUNTER_PIN_DOWN       =0x02;
	//������ͨ������
	public static byte COUNTER_CH0             =0x01;
	public static byte COUNTER_CH1             =0x02;
	public static byte COUNTER_CH2             =0x04;
	public static byte COUNTER_CH3             =0x08;
	
	//�����ʼ������������������
	public class CNT_CONFIG  extends Structure{
		
	    public static class ByReference extends CNT_CONFIG implements Structure.ByReference {}  
	    public static class ByValue extends CNT_CONFIG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"CounterMode","CounterPolarity","CounterBitWide","CounterPinMode"});
		}

		byte   CounterMode;      //����ģʽ��0-Up,1-Down
		byte   CounterPolarity;  //�������ԣ�0-Rising��1-Falling��2-BothEdge
		byte   CounterBitWide;   //����λ��16-16bitλ��32-32bitλ��
		byte   CounterPinMode;   //��������������ģʽ��0-�������룬1-�������룬2-��������
	};
	
	int  CNT_Init(int DevIndex, byte ChannelMask, CNT_CONFIG pConfig);
	int  CNT_Start(int DevIndex, byte ChannelMask);
	int  CNT_Stop(int DevIndex, byte ChannelMask);
	int  CNT_SetValue(int DevIndex, byte ChannelMask,int[] pCntValues);
	int  CNT_GetValue(int DevIndex, byte ChannelMask,int[] pCntValues);
}
