package com.usbxyz;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

public interface USB2IIC extends Library {
	USB2IIC INSTANCE  = (USB2IIC)Native.loadLibrary("USB2XXX",USB2IIC.class); 
	
	public class IIC_CONFIG  extends Structure{
		
	    public static class ByReference extends IIC_CONFIG implements Structure.ByReference {}  
	    public static class ByValue extends IIC_CONFIG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"ClockSpeedHz", "OwnAddr", "Master", "AddrBits", "EnablePu"});
		}
	    
		public int    ClockSpeedHz; //IICʱ��Ƶ��:��λΪHz
		public short  OwnAddr;      //USB2XXXΪ�ӻ�ʱ�Լ��ĵ�ַ
		public byte   Master;       //����ѡ�����:0-�ӻ���1-����
		public byte   AddrBits;     //�ӻ���ַģʽ��7-7bitģʽ��10-10bitģʽ
		public byte   EnablePu;     //ʹ������оƬ�ڲ��������裬����ʹ�ܣ���I2C�����ϱ������������
	}
    //���庯�����ش������
    public static int IIC_SUCCESS             = (0);   //����ִ�гɹ�
    public static int IIC_ERR_NOT_SUPPORT     = (-1) ; //��������֧�ָú���
    public static int IIC_ERR_USB_WRITE_FAIL  = (-2);  //USBд����ʧ��
    public static int IIC_ERR_USB_READ_FAIL   = (-3);  //USB������ʧ��
    public static int IIC_ERR_CMD_FAIL        = (-4);  //����ִ��ʧ��
    public static int IIC_ERR_PARA_ERROR      = (-5);  //�����������
    //����IIC�������ش������
    public static int IIC_ERROR_SUCCESS     = 0;  //�����ɹ�
    public static int IIC_ERROR_CHANNEL     = 1;   //��ͨ����֧�ָú���
    public static int IIC_ERROR_BUSY        = 2;   //����æ
    public static int IIC_ERROR_START_FAILD = 3;   //��������ʧ��
    public static int IIC_ERROR_TIMEOUT     = 4;   //��ʱ
    public static int IIC_ERROR_NACK        = 5;   //�ӻ���Ӧ��
    //USB2IIC��غ�������
    int IIC_Init(int DevIndex,int IICIndex, IIC_CONFIG pConfig);
    int IIC_GetSlaveAddr(int DevIndex,int IICIndex,short[] pSlaveAddr);
    int IIC_WriteBytes(int DevIndex,int IICIndex,short SlaveAddr,byte[] pWriteData,int WriteLen,int TimeOutMs);
    int IIC_ReadBytes(int DevIndex,int IICIndex,short SlaveAddr,byte[] pReadData,int ReadLen,int TimeOutMs);
    int IIC_WriteReadBytes(int DevIndex,int IICIndex,short SlaveAddr,byte[] pWriteData,int WriteLen,byte[] pReadData,int ReadLen,int TimeOutMs);
    int IIC_SlaveWriteBytes(int DevIndex,int IICIndex,byte[] pWriteData,int WriteLen,int TimeOutMs);
    int IIC_SlaveReadBytes(int DevIndex,int IICIndex,byte[] pReadData,int TimeOutMs);
    int IIC_SlaveWriteRemain(int DevIndex,int IICIndex);

    int IIC_WriteBytesOfEvent(int DevIndex,int IICIndex,short SlaveAddr,byte[] pWriteData,int WriteLen,int EventPin,byte EventType,int TimeOutOfEventMs);
    int IIC_ReadBytesOfEvent(int DevIndex,int IICIndex,short SlaveAddr,byte[] pReadData,int ReadLen,int EventPin,byte EventType,int TimeOutOfEventMs);
    int IIC_WriteReadBytesOfEvent(int DevIndex,int IICIndex,short SlaveAddr,byte[] pWriteData,int WriteLen,byte[] pReadData,int ReadLen,int EventPin,byte EventType,int TimeOutOfEventMs);

    int SMBUS_Init(int DevIndex,int IICIndex,int ClockSpeedHz,byte EnablePu);
    int SMBUS_QuickCommand(int DevIndex,int IICIndex,short SlaveAddr,byte WriteReadFlag);
    int SMBUS_WriteByte(int DevIndex,int IICIndex,short SlaveAddr,byte Data,byte WithPEC);
    int SMBUS_ReadByte(int DevIndex,int IICIndex,short SlaveAddr,byte[] pData,byte WithPEC);
    int SMBUS_WriteByteProtocol(int DevIndex,int IICIndex,short SlaveAddr,byte CommandCode, byte Data,byte WithPEC);
    int SMBUS_WriteWordProtocol(int DevIndex,int IICIndex,short SlaveAddr,byte CommandCode, short Data,byte WithPEC);
    int SMBUS_ReadByteProtocol(int DevIndex,int IICIndex,short SlaveAddr,byte CommandCode, byte[] pData,byte WithPEC);
    int SMBUS_ReadWordProtocol(int DevIndex,int IICIndex,short SlaveAddr,byte CommandCode, short[] pData,byte WithPEC);
    int SMBUS_ProcessCall(int DevIndex,int IICIndex,short SlaveAddr,byte CommandCode, short WriteData, short[] pReadData,byte WithPEC);
    int SMBUS_BlockWrite(int DevIndex,int IICIndex,short SlaveAddr,byte CommandCode, byte[] pWriteData,int WriteCount,byte WithPEC);
    int SMBUS_BlockRead(int DevIndex,int IICIndex,short SlaveAddr,byte CommandCode, byte[] pReadData,int[] pReadCount,byte WithPEC);
    int SMBUS_BlockProcessCall(int DevIndex,int IICIndex,short SlaveAddr,byte CommandCode, byte[] pWriteData,int WriteCount,byte[] pReadData,int[] pReadCount,byte WithPEC);

}
