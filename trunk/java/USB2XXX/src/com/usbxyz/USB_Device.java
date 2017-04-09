package com.usbxyz;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

public interface USB_Device extends Library{
	USB_Device INSTANCE  = (USB_Device)Native.loadLibrary("USB2XXX",USB_Device.class); 
	
	public class DEVICE_INFO  extends Structure{
		
	    public static class ByReference extends DEVICE_INFO implements Structure.ByReference {}  
	    public static class ByValue extends DEVICE_INFO implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"FirmwareName", "BuildDate", "HardwareVersion", "FirmwareVersion", "SerialNumber", "Functions"});
		}
	    
		public byte[]   FirmwareName = new byte[32];   //�̼������ַ���
		public byte[]   BuildDate = new byte[32];      //�̼�����ʱ���ַ���
		public int     	HardwareVersion;    //Ӳ���汾��
		public int     	FirmwareVersion;    //�̼��汾��
		public int[]    SerialNumber = new int[3];    //���������к�
		public int     	Functions;          //��������ǰ�߱��Ĺ���
	}
	/**
	  * @brief  ��ʼ��USB�豸����ɨ���豸���������������
	  * @param  pDevNum ÿ���豸���豸�Ŵ洢��ַ��������Ҫ�豸�ţ����Դ���NULL
	  * @retval ɨ�赽���豸����
	  */
	int  USB_ScanDevice(int[] pDevNum);
	/**
	  * @brief  ���豸���������
	  * @param  DevIndex �豸������
	  * @retval ���豸��״̬
	  */
	boolean USB_OpenDevice(int DevIndex);

	/**
	  * @brief  �ر��豸
	  * @param  DevIndex �豸������
	  * @retval �ر��豸��״̬
	  */
	boolean USB_CloseDevice(int DevIndex);

	/**
	  * @brief  ��ȡ�豸��Ϣ�������豸���ƣ��̼��汾�ţ��豸��ţ��豸����˵���ַ�����
	  * @param  DevIndex �豸������
	  * @param  pDevInfo �豸��Ϣ�洢�ṹ��ָ��
	  * @param  pFunctionStr �豸����˵���ַ���
	  * @retval ��ȡ�豸��Ϣ��״̬
	  */
	boolean USB_GetDeviceInfo(int DevIndex,DEVICE_INFO pDevInfo,byte[] pFunctionStr);

	/**
	  * @brief  �����û�������
	  * @param  DevIndex �豸������
	  * @retval �û������ݲ���״̬
	  */
	boolean USB_EraseUserData(int DevIndex);

	/**
	  * @brief  ���û�����д���û��Զ������ݣ�д������֮ǰ��Ҫ���ò������������ݲ���
	  * @param  DevIndex �豸������
	  * @param  OffsetAddr ����д��ƫ�Ƶ�ַ����ʼ��ַΪ0x00���û���������Ϊ0x10000�ֽڣ�Ҳ����64KBye
	  * @param  pWriteData �û����ݻ������׵�ַ
	  * @param  DataLen ��д��������ֽ���
	  * @retval д���û��Զ�������״̬
	  */
	boolean USB_WriteUserData(int DevIndex,int OffsetAddr,byte[] pWriteData,int DataLen);

	/**
	  * @brief  ���û��Զ�����������������
	  * @param  DevIndex �豸������
	  * @param  OffsetAddr ����д��ƫ�Ƶ�ַ����ʼ��ַΪ0x00���û���������Ϊ0x10000�ֽڣ�Ҳ����64KBye
	  * @param  pReadData �û����ݻ������׵�ַ
	  * @param  DataLen �������������ֽ���
	  * @retval �����û��Զ������ݵ�״̬
	  */
	boolean USB_ReadUserData(int DevIndex,int OffsetAddr,byte[] pReadData,int DataLen);
}
