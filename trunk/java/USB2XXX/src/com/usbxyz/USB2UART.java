package com.usbxyz;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

public interface USB2UART extends Library {
	USB2UART INSTANCE  = (USB2UART)Native.loadLibrary("USB2XXX",USB2UART.class); 
	//���庯�����ش������
	public static int UART_SUCCESS             =(0);   //����ִ�гɹ�
	public static int UART_ERR_NOT_SUPPORT     =(-1);  //��������֧�ָú���
	public static int UART_ERR_USB_WRITE_FAIL  =(-2);  //USBд����ʧ��
	public static int UART_ERR_USB_READ_FAIL   =(-3);  //USB������ʧ��
	public static int UART_ERR_CMD_FAIL        =(-4);  //����ִ��ʧ��
	//����λ��
	public static byte UART_WORD_LENGTH_8BIT     =0;
	public static byte UART_WORD_LENGTH_9BIT     =1;
	//ֹͣλ
	public static byte UART_STOP_BITS_1          =0;
	public static byte UART_STOP_BITS_05         =1;
	public static byte UART_STOP_BITS_2          =2;
	public static byte UART_STOP_BITS_15         =3;
	//��żУ��λ
	public static byte UART_PARITY_NO            =0;
	public static byte UART_PARITY_EVEN          =4;
	public static byte UART_PARITY_ODD           =6;
	//TE�����ź����
	public static byte UART_TE_DISEN             =0x00;
	public static byte UART_TE_EN_LOW            =(byte)0x80;
	public static byte UART_TE_EN_HIGH           =(byte)0x81;
	
	public class UART_CONFIG  extends Structure{
		
	    public static class ByReference extends UART_CONFIG implements Structure.ByReference {}  
	    public static class ByValue extends UART_CONFIG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"BaudRate","WordLength","StopBits","Parity","TEPolarity"});
		}

		int  BaudRate;     //������
		byte WordLength;   //����λ��0-8bit,1-9bit
		byte StopBits;     //ֹͣλ��0-1bit,1-0.5bit,2-2bit,3-1.5bit
		byte Parity;       //��żУ�飬0-No,4-Even,6-Odd
		byte TEPolarity;   //TE������ƣ�0x80-���TE�źţ��ҵ͵�ƽ��Ч��0x81-���TE�źţ��Ҹߵ�ƽ��Ч��0x00�����TE�ź�
	};
	
	int  UART_Init(int DevIndex, byte Channel, UART_CONFIG pConfig);
	int  UART_WriteBytes(int DevIndex,byte Channel,byte[] pWriteData,int DataSize);
	int  UART_WriteBytesAsync(int DevIndex,byte Channel,byte[] pWriteData,int DataSize);
	int  UART_ReadBytes(int DevIndex,byte Channel,byte[] pReadData,int TimeOutMs);
}
