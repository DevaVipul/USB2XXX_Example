package com.usbxyz;
import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;  
import com.sun.jna.Native;
import com.sun.jna.Structure;


public interface USB2XXX  extends Library{
	USB2XXX INSTANCE  = (USB2XXX)Native.loadLibrary("USB2XXX",USB2XXX.class); 
	
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

    
    //����SPIͨ��
    public static int SPI1        = (0x00);
    public static int SPI1_CS0    = (0x00);
    public static int SPI1_CS1    = (0x10);
    public static int SPI1_CS2    = (0x20);
    public static int SPI1_CS3    = (0x30);
    public static int SPI1_CS4    = (0x40);

    public static int SPI2        = (0x01);
    public static int SPI2_CS0    = (0x01);
    public static int SPI2_CS1    = (0x11);
    public static int SPI2_CS2    = (0x21);
    public static int SPI2_CS3    = (0x31);
    public static int SPI2_CS4    = (0x41);
    //���幤��ģʽ
    public static int SPI_MODE_HARD_FDX       = 0; //Ӳ�����ƣ�ȫ˫��ģʽ��
    public static int SPI_MODE_HARD_HDX       = 1; //Ӳ�����ƣ���˫��ģʽ��
    public static int SPI_MODE_SOFT_HDX       = 2; //������ƣ���˫��ģʽ��
    public static int SPI_MODE_SOFT_ONE_WIRE  = 3; //������ģʽ�����������������ΪMOSI
    //�������ӻ�ģʽ
    public static int SPI_MASTER      = 1; //����
    public static int SPI_SLAVE       = 0; //�ӻ�
    //����������λ��ʽ
    public static int SPI_MSB         = 0; //��λ��ǰ
    public static int SPI_LSB         = 1; //��λ��ǰ
    //����Ƭѡ�������
    public static int SPI_SEL_LOW     = 0; //Ƭѡ����͵�ƽ
    public static int SPI_SEL_HIGH    = 1; //Ƭѡ����ߵ�ƽ
    //����EVENT����,ע��EVENT���Ų�Ҫ��SPIͨ�����ų�ͻ
    public static int SPI_EVENT_P0    = (1<<0);
    public static int SPI_EVENT_P1    = (1<<1);
    public static int SPI_EVENT_P2    = (1<<2);
    public static int SPI_EVENT_P3    = (1<<3);
    public static int SPI_EVENT_P4    = (1<<4);
    public static int SPI_EVENT_P5    = (1<<5);
    public static int SPI_EVENT_P6    = (1<<6);
    public static int SPI_EVENT_P7    = (1<<7);
    public static int SPI_EVENT_P8    = (1<<8);
    public static int SPI_EVENT_P9    = (1<<9);
    public static int SPI_EVENT_P10    = (1<<10);
    public static int SPI_EVENT_P11    = (1<<11);
    public static int SPI_EVENT_P12    = (1<<12);
    public static int SPI_EVENT_P13    = (1<<13);
    public static int SPI_EVENT_P14    = (1<<14);
    public static int SPI_EVENT_P15    = (1<<15);

    //�����¼�����
    public static int EVENT_TYPE_LOW      = 0x00;
    public static int EVENT_TYPE_HIGH     = 0x11;
    public static int EVENT_TYPE_RISING   = 0x01;
    public static int EVENT_TYPE_FALLING  = 0x10;
    
    //���庯�����ش������
    public static int SPI_SUCCESS             = (0);   //����ִ�гɹ�
    public static int SPI_ERR_NOT_SUPPORT     = (-1);  //��������֧�ָú���
    public static int SPI_ERR_USB_WRITE_FAIL  = (-2);  //USBд����ʧ��
    public static int SPI_ERR_USB_READ_FAIL   = (-3);  //USB������ʧ��
    public static int SPI_ERR_CMD_FAIL        = (-4);  //����ִ��ʧ��
    public static int SPI_ERR_PARAMETER       = (-5);  //��������
    //����ӻ�ģʽ��������ȡ���ݵĻص�����
    public interface SPI_GET_DATA_HANDLE{
        int SPI_GetDataHandle(int DevIndex,int SPIIndex,byte[] pData,int DataNum);//�������ݻص�����
    }
    
    //�����ʼ��SPI����������
	public class SPI_CONFIG  extends Structure{
		
	    public static class ByReference extends SPI_CONFIG implements Structure.ByReference {}  
	    public static class ByValue extends SPI_CONFIG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"Mode","Master","CPOL","CPHA","LSBFirst","SelPolarity","ClockSpeedHz"});
		}
        public byte   Mode;            //SPI���Ʒ�ʽ:0-Ӳ�����ƣ�ȫ˫��ģʽ��,1-Ӳ�����ƣ���˫��ģʽ����2-������ƣ���˫��ģʽ��,3-������ģʽ�����������������ΪMOSI
        public byte   Master;          //����ѡ�����:0-�ӻ���1-����
        public byte   CPOL;            //ʱ�Ӽ��Կ���:0-SCK����ʱΪ�͵�ƽ��1-SCK����ʱΪ�ߵ�ƽ
        public byte   CPHA;            //ʱ����λ����:0-��һ��SCKʱ�Ӳ�����1-�ڶ���SCKʱ�Ӳ���
        public byte   LSBFirst;        //������λ��ʽ:0-MSB��ǰ��1-LSB��ǰ
        public byte   SelPolarity;     //Ƭѡ�źż���:0-�͵�ƽѡ�У�1-�ߵ�ƽѡ��
        public int ClockSpeedHz;       //SPIʱ��Ƶ��:��λΪHZ��Ӳ��ģʽ�����50000000����С390625��Ƶ�ʰ�2�ı����ı�
    }

    //����SPI Flash�������ò�����������
	public class SPI_FLASH_CONFIG  extends Structure{
		
	    public static class ByReference extends SPI_FLASH_CONFIG implements Structure.ByReference {}  
	    public static class ByValue extends SPI_FLASH_CONFIG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(
					new String[]{"CMD_WriteEnable","CMD_WriteDisable","CMD_WritePage","WritePageAddressBytes","CMD_EraseSector",
							"EraseSectorAddressBytes","CMD_EraseBulk","CMD_EraseChip","CMD_ReadID","CMD_ReadData","ReadDataAddressBytes",
							"CMD_ReadFast","ReadFastAddressBytes","CMD_ReadStatus","CMD_WriteStatus","ID","ID_Length","PageSize","NumPages","SectorSize"});
		}
        public byte CMD_WriteEnable;          //ʹ��д����
        public byte CMD_WriteDisable;         //��ֹд����
        public byte CMD_WritePage;            //д��������
        public byte WritePageAddressBytes;    //д����ʱ�ĵ�ַ��ȣ���λΪ�ֽ�
        public byte CMD_EraseSector;          //������������
        public byte EraseSectorAddressBytes;  //���������ĵ�ַ��ȣ���λΪ�ֽ�
        public byte CMD_EraseBulk;            //���������
        public byte CMD_EraseChip;            //��Ƭ��������
        public byte CMD_ReadID;               //��оƬID����
        public byte CMD_ReadData;             //����������
        public byte ReadDataAddressBytes;     //������ʱ�ĵ�ַ��ȣ���λΪ�ֽ�
        public byte CMD_ReadFast;             //����ģʽ����������
        public byte ReadFastAddressBytes;     //���ٶ�����ʱ�ĵ�ַ��ȣ���λΪ�ֽ�
        public byte CMD_ReadStatus;           //��ȡ״̬�Ĵ�������
        public byte CMD_WriteStatus;          //д״̬�Ĵ�������
        public byte[] ID = new byte[16];      //оƬID�洢����
        public byte ID_Length;                //ID���ȣ���λΪ�ֽ�
        public int PageSize;                  //ҳ��С����λΪ�ֽ�
        public int NumPages;                  //оƬ�ܵ�ҳ��
        public int SectorSize;                //������С����λΪ�ֽ�
    }
	//USB2SPI��غ���
	/**
	  * @brief  SPI��ʼ�����ú���
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pConfig SPI��ʼ�����ýṹ��ָ��
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_Init(int DevIndex,int SPIIndex, SPI_CONFIG pConfig);

	/**
	  * @brief  SPI��������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData ���ݷ��ͻ������׵�ַ
	  * @param  WriteLen ���ݷ����ֽ���
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_WriteBytes(int DevIndex,int SPIIndex,byte[] pWriteData,int WriteLen);

	/**
	  * @brief  SPI�첽��ʽ�������ݣ���������֮�󲻻�ȴ����ݷ�����ϣ��÷�ʽ���ԼӴ����ݷ�������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData ���ݷ��ͻ������׵�ַ
	  * @param  WriteLen ���ݷ����ֽ���
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_WriteBytesAsync(int DevIndex,int SPIIndex,byte[] pWriteData,int WriteLen);

	/**
	  * @brief  SPI��������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pReadData ���ݽ��ջ������׵�ַ
	  * @param  ReadLen ���������ֽ���
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_ReadBytes(int DevIndex,int SPIIndex,byte[] pReadData,int ReadLen);

	/**
	  * @brief  SPI���ͽ������ݣ�ȫ˫��ģʽ�·��ͺͽ���ͬʱ���У���˫��ģʽ�·��ͺͽ��շֿ����У�������������Ƭѡһֱ��Ч
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData �������ݻ������׵�ַ
	  * @param  WriteLen ���������ֽ���
	  * @param  pReadData ���ݽ��ջ������׵�ַ
	  * @param  ReadLen ���������ֽ���
	  * @param  IntervalTime ��˫��ģʽ�£��������ݺͽ�������֮���ʱ��������λΪ΢��
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_WriteReadBytes(int DevIndex,int SPIIndex,byte[] pWriteData,int WriteLen,byte[] pReadData,int ReadLen,int IntervalTimeUs);

	/**
	  * @brief  �ȵ���Ч�¼���SPI��������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData ���ݷ��ͻ������׵�ַ
	  * @param  WriteLen ���ݷ����ֽ���
	  * @param  EventPin �ȴ��¼���GPIO����
	  * @param  EventType �¼����ͣ�0x00-�͵�ƽ��0x11-�ߵ�ƽ��0x10-�½��أ�0x01������
	  * @param  TimeOutOfMs �ȴ��¼���ʱʱ�䣬��λΪ����
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_WriteBytesOfEvent(int DevIndex,int SPIIndex,byte[] pWriteData,int WriteLen,int EventPin,byte EventType,int TimeOutOfMs);


	/**
	  * @brief  �ȵ���Ч�¼���SPI��������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pReadData ���ݽ��ջ������׵�ַ
	  * @param  ReadLen ���������ֽ���
	  * @param  EventPin �ȴ��¼���GPIO����
	  * @param  EventType �¼����ͣ�0x00-�͵�ƽ��0x11-�ߵ�ƽ��0x10-�½��أ�0x01������
	  * @param  TimeOutOfMs �ȴ��¼���ʱʱ�䣬��λΪ����
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_ReadBytesOfEvent(int DevIndex,int SPIIndex,byte[] pReadData,int ReadLen,int EventPin,byte EventType,int TimeOutOfMs);

	/**
	  * @brief  �ȵ���Ч�¼���SPI���ͽ������ݣ�ȫ˫��ģʽ�·��ͺͽ���ͬʱ���У���˫��ģʽ�·��ͺͽ��շֿ����У�������������Ƭѡһֱ��Ч
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData �������ݻ������׵�ַ
	  * @param  WriteLen ���������ֽ���
	  * @param  pReadData ���ݽ��ջ������׵�ַ
	  * @param  ReadLen ���������ֽ���
	  * @param  IntervalTime ��˫��ģʽ�£��������ݺͽ�������֮���ʱ��������λΪ΢��
	  * @param  EventPin �ȴ��¼���GPIO����
	  * @param  EventType �¼����ͣ�0x00-�͵�ƽ��0x11-�ߵ�ƽ��0x10-�½��أ�0x01������
	  * @param  TimeOutOfMs �ȴ��¼���ʱʱ�䣬��λΪ����
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_WriteReadBytesOfEvent(int DevIndex,int SPIIndex,byte[] pWriteData,int WriteLen,byte[] pReadData,int ReadLen,int IntervalTimeUs,int EventPin,byte EventType,int TimeOutOfMs);


	/**
	  * @brief  ������ģʽд���ݣ��ú������Է�������bit������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteBitStr �����������ַ������磺"100110011"
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_WriteBits(int DevIndex,int SPIIndex,byte[] pWriteBitStr);

	/**
	  * @brief  ������ģʽ�����ݣ��ú������Զ�ȡ����bit������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pReadBitStr ��ȡ���Ķ����������ַ������磺"100110011"
	  * @param  ReadBitsNum ��ȡ���ݵĶ�����bit��
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_ReadBits(int DevIndex,int SPIIndex,byte[] pReadBitStr,int ReadBitsNum);

	/**
	  * @brief  ������ģʽд�����ݣ��ú�������д��ȡ����bit������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteBitStr д�����������ַ������磺"100110011"
	  * @param  pReadBitStr ��ȡ���Ķ����������ַ������磺"100110011"
	  * @param  ReadBitsNum ��ȡ���ݵĶ�����bit��
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_WriteReadBits(int DevIndex,int SPIIndex,byte[] pWriteBitStr,byte[] pReadBitStr,int ReadBitsNum);

	/**
	  * @brief  SPI�ӻ�ģʽ�½�����д�����ݷ��ͻ��������ȴ�������ʱ���ź��ٽ����ݷ��ͳ�ȥ
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData �������ݻ������׵�ַ
	  * @param  WriteLen ���������ֽ���
	  * @param  TimeOutMs �ȴ����ݷ�����ϳ�ʱʱ�䣬��С�ڻ��ߵ���0�򲻻�ȴ����ݷ�����ϣ�������������
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_SlaveWriteBytes(int DevIndex,int SPIIndex,byte[] pWriteData,int WriteLen,int TimeOutMs);

	/**
	  * @brief  SPI�ӻ�ģʽ�»�ȡ�������ݻ�����������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pReadData ���ݽ��ջ������׵�ַ
	  * @param  pReadLen ���յ��������ֽ���
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_SlaveReadBytes(int DevIndex,int SPIIndex,byte[] pReadData,int TimeOutMs);

	/**
	  * @brief  SPI�ӻ�ģʽ��������ȡ����,SPI�ڴӻ�ģʽ�½��յ�����֮��ͨ���ص�������������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pSlaveReadDataHandle �ӻ�ģʽ�½��յ����ݺ�Ļص�����
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_SlaveContinueRead(int DevIndex,int SPIIndex,SPI_GET_DATA_HANDLE pSlaveReadDataHandle);

	/**
	  * @brief  SPI�ӻ�ģʽ�»�ȡ�������ݻ�����������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pReadData ���ݽ��ջ������׵�ַ
	  * @param  BufferSize ���ݻ�������С
	  * @retval ��ȡ���������ֽ���
	  */
	int  SPI_SlaveGetBytes(int DevIndex,int SPIIndex,byte[] pReadData,int BufferSize);
	/**
	  * @brief  ֹͣSPI�ӻ�ģʽ��������ȡ����
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_SlaveContinueReadStop(int DevIndex,int SPIIndex);
	/**
	  * @brief  ��дSPI-Flash��ʼ������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  ClockSpeed SPIʱ���ź�Ƶ�ʣ���λΪHz,���Ϊ50MHz�����γɱ��ݼ�
	  * @param  pConfig SPI-Flash��ز���
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_FlashInit(int DevIndex,int SPIIndex,int ClockSpeed, SPI_FLASH_CONFIG pConfig);

	/**
	  * @brief  ��ȡSPI-FlashоƬ��ID��
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pID оƬID�Ŵ洢�׵�ַ���䳤����SPI_FLASH_CONFIG�е�ID_Length����
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_FlashReadID(int DevIndex,int SPIIndex,byte[] pID);

	/**
	  * @brief  ����SPI-Flash����������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  StartSector ��ʼ�����ţ�ע���������ţ����Ǿ����������ַ
	  * @param  NumSector ��Ҫ������������
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_FlashEraseSector(int DevIndex,int SPIIndex,int StartSector,int NumSector);

	/**
	  * @brief  ����SPI-Flash����оƬ������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_FlashEraseChip(int DevIndex,int SPIIndex);


	/**
	  * @brief  ��SPI-Flashд����
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  StartAddr д������ʼ��ַ
	  * @param  pWriteData д���ݻ������׵�ַ
	  * @param  WriteLen д�����ֽ���
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_FlashWrite(int DevIndex,int SPIIndex,int StartAddr,byte[] pWriteData,int WriteLen);

	/**
	  * @brief  ��SPI-Flash������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  StartAddr д������ʼ��ַ
	  * @param  pReadData �����ݻ������׵�ַ
	  * @param  ReadLen �������ֽ���
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_FlashRead(int DevIndex,int SPIIndex,int StartAddr,byte[] pReadData,int ReadLen);

	/**
	  * @brief  ��SPI-Flash������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  StartAddr д������ʼ��ַ
	  * @param  pReadData �����ݻ������׵�ַ
	  * @param  ReadLen �������ֽ���
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_FlashReadFast(int DevIndex,int SPIIndex,int StartAddr,byte[] pReadData,int ReadLen);

	/**
	  * @brief  Blockģʽд����
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData д������ʼ��ַ
	  * @param  BlockSize ÿ��д�����ֽ���
	  * @param  BlockNum д�����ܴ���
	  * @param  IntervalTime ÿ��д����֮���ʱ��������λΪ΢��
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_BlockWriteBytes(int DevIndex,int SPIIndex,byte[] pWriteData,int BlockSize,int BlockNum,int IntervalTimeUs);

	/**
	  * @brief  Blockģʽ������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pReadData �����ݻ������׵�ַ
	  * @param  BlockSize ÿ�ζ������ֽ���
	  * @param  BlockNum �������ܴ���
	  * @param  IntervalTime ÿ��д����֮���ʱ��������λΪ΢��
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_BlockReadBytes(int DevIndex,int SPIIndex,byte[] pReadData,int BlockSize,int BlockNum,int IntervalTimeUs);

	/**
	  * @brief  Blockģʽд������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData д������ʼ��ַ
	  * @param  WriteBlockSize ÿ�ζ������ֽ���
	  * @param  pReadData �����ݻ������׵�ַ
	  * @param  ReadBlockSize ÿ�ζ������ֽ���
	  * @param  BlockNum �������ܴ���
	  * @param  IntervalTime ÿ��д����֮���ʱ��������λΪ΢��
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_BlockWriteReadBytes(int DevIndex,int SPIIndex,byte[] pWriteData,int WriteBlockSize,byte[] pReadData,int ReadBlockSize,int BlockNum,int IntervalTimeUs);

	/**
	  * @brief  Blockģʽд����
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData д������ʼ��ַ
	  * @param  BlockSize ÿ��д�����ֽ���
	  * @param  BlockNum д�����ܴ���
	  * @param  EventPin �ȴ��¼���GPIO����
	  * @param  EventType �¼����ͣ�0x00-�͵�ƽ��0x11-�ߵ�ƽ��0x10-�½��أ�0x01������
	  * @param  TimeOutOfMs �ȴ��¼���ʱʱ�䣬��λΪ����
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_BlockWriteBytesOfEvent(int DevIndex,int SPIIndex,byte[] pWriteData,int BlockSize,int BlockNum,int EventPin,byte EventType,int TimeOutOfMs);

	/**
	  * @brief  Blockģʽ������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pReadData �����ݻ������׵�ַ
	  * @param  BlockSize ÿ�ζ������ֽ���
	  * @param  BlockNum �������ܴ���
	  * @param  EventPin �ȴ��¼���GPIO����
	  * @param  EventType �¼����ͣ�0x00-�͵�ƽ��0x11-�ߵ�ƽ��0x10-�½��أ�0x01������
	  * @param  TimeOutOfMs �ȴ��¼���ʱʱ�䣬��λΪ����
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_BlockReadBytesOfEvent(int DevIndex,int SPIIndex,byte[] pReadData,int BlockSize,int BlockNum,int EventPin,byte EventType,int TimeOutOfMs);

	/**
	  * @brief  Blockģʽд������
	  * @param  DevIndex �豸������
	  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
	  * @param  pWriteData д������ʼ��ַ
	  * @param  WriteBlockSize ÿ�ζ������ֽ���
	  * @param  pReadData �����ݻ������׵�ַ
	  * @param  ReadBlockSize ÿ�ζ������ֽ���
	  * @param  BlockNum �������ܴ���
	  * @param  EventPin �ȴ��¼���GPIO����
	  * @param  EventType �¼����ͣ�0x00-�͵�ƽ��0x11-�ߵ�ƽ��0x10-�½��أ�0x01������
	  * @param  TimeOutOfMs �ȴ��¼���ʱʱ�䣬��λΪ����
	  * @retval ����ִ��״̬��С��0����ִ�г���
	  */
	int  SPI_BlockWriteReadBytesOfEvent(int DevIndex,int SPIIndex,byte[] pWriteData,int WriteBlockSize,byte[] pReadData,int ReadBlockSize,int BlockNum,int EventPin,byte EventType,int TimeOutOfMs);

	
    //0.�������ش�����붨��
    public static int   CAN_SUCCESS             =(0);   //����ִ�гɹ�
    public static int   CAN_ERR_NOT_SUPPORT     =(-1);  //��������֧�ָú���
    public static int   CAN_ERR_USB_WRITE_FAIL  =(-2);  //USBд����ʧ��
    public static int   CAN_ERR_USB_READ_FAIL   =(-3);  //USB������ʧ��
    public static int   CAN_ERR_CMD_FAIL        =(-4);  //����ִ��ʧ��
    public static int   CAN_BL_ERR_CONFIG		=(-20); //�����豸����
    public static int	CAN_BL_ERR_SEND			=(-21); //�������ݳ���
    public static int	CAN_BL_ERR_TIME_OUT		=(-22); //��ʱ����
    public static int	CAN_BL_ERR_CMD			=(-23); //ִ������ʧ��

    public static int   CAN_BL_BOOT   =  0x55555555;
    public static int   CAN_BL_APP    =  0xAAAAAAAA;
    //1.CAN��Ϣ֡���������Ͷ���
	public class CAN_MSG  extends Structure{
		
	    public static class ByReference extends CAN_MSG implements Structure.ByReference {}  
	    public static class ByValue extends CAN_MSG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"ID","TimeStamp","RemoteFlag","ExternFlag","DataLen","Data"});
		}

        public int  ID;			//����ID��
        public int  TimeStamp;	//���յ���Ϣ֡ʱ��ʱ���ʶ����CAN ��������ʼ����ʼ��ʱ��
        public byte RemoteFlag;	//�Ƿ���Զ��֡
        public byte	ExternFlag;	//�Ƿ�����չ֡
        public byte	DataLen;	//���ݳ���(<=8)����Data �ĳ��ȡ�
        public byte[]	Data = new byte[8];	//���ĵ����ݡ�
    }

    //2.��ʼ��CAN���������Ͷ���
	public class CAN_INIT_CONFIG  extends Structure{
		
	    public static class ByReference extends CAN_INIT_CONFIG implements Structure.ByReference {}  
	    public static class ByValue extends CAN_INIT_CONFIG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"CAN_BRP","CAN_SJW","CAN_BS1","CAN_BS2","CAN_Mode","CAN_ABOM","CAN_NART","CAN_RFLM","CAN_TXFP"});
		}
        //CAN������ = 100MHz/(CAN_BRP)/(CAN_SJW+CAN_BS1+CAN_BS2)
        public int	CAN_BRP;	//ȡֵ��Χ1~1024
        public byte	CAN_SJW;	//ȡֵ��Χ1~4
        public byte	CAN_BS1;	//ȡֵ��Χ1~16
        public byte	CAN_BS2;	//ȡֵ��Χ1~8
        public byte	CAN_Mode;	//CAN����ģʽ��0-����ģʽ��1-����ģʽ��2-��Ĭģʽ��3-��Ĭ����ģʽ
        public byte	CAN_ABOM;	//�Զ����߹���0-��ֹ��1-ʹ��
        public byte	CAN_NART;	//�����ط�����0-ʹ�ܱ����ش���1-��ֹ�����ش�
        public byte	CAN_RFLM;	//FIFO��������0-�±��ĸ��Ǿɱ��ģ�1-�����±���
        public byte	CAN_TXFP;	//�������ȼ�����0-��ʶ��������1-��������˳�����
    }


    //3.CAN �˲��������������Ͷ���
	public class CAN_FILTER_CONFIG  extends Structure{
		
	    public static class ByReference extends CAN_FILTER_CONFIG implements Structure.ByReference {}  
	    public static class ByValue extends CAN_FILTER_CONFIG implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"Enable","FilterIndex","FilterMode","ExtFrame","ID_Std_Ext","ID_IDE","ID_RTR","MASK_Std_Ext","MASK_IDE","MASK_RTR"});
		}
        public byte	Enable;			//ʹ�ܸù�������1-ʹ�ܣ�0-��ֹ
        public byte	FilterIndex;	//�����������ţ�ȡֵ��ΧΪ0��13
        public byte	FilterMode;		//������ģʽ��0-����λģʽ��1-��ʶ���б�ģʽ
        public byte	ExtFrame;		//���˵�֡���ͱ�־��Ϊ1 ����Ҫ���˵�Ϊ��չ֡��Ϊ0 ����Ҫ���˵�Ϊ��׼֡��
        public int	ID_Std_Ext;		//������ID
        public int	ID_IDE;			//������IDE
        public int	ID_RTR;			//������RTR
        public int	MASK_Std_Ext;	//������ID������ֻ���ڹ�����ģʽΪ����λģʽʱ����
        public int	MASK_IDE;		//������IDE������ֻ���ڹ�����ģʽΪ����λģʽʱ����
        public int	MASK_RTR;		//������RTR������ֻ���ڹ�����ģʽΪ����λģʽʱ����
    }
    //4.CAN����״̬�������Ͷ���
	public class CAN_STATUS  extends Structure{
	    public static class ByReference extends CAN_STATUS implements Structure.ByReference {}  
	    public static class ByValue extends CAN_STATUS implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"TSR","ESR","RECounter","TECounter","LECode"});
		}
        public int     TSR;
        public int     ESR;
        public byte    RECounter;	//CAN ���������մ���Ĵ�����
        public byte    TECounter;	//CAN ���������ʹ���Ĵ�����
        public byte    LECode;     //���Ĵ������
    }
    //5.����CAN Bootloader�����б�
	public class CBL_CMD_LIST  extends Structure{
	    public static class ByReference extends CBL_CMD_LIST implements Structure.ByReference {}  
	    public static class ByValue extends CBL_CMD_LIST implements Structure.ByValue {}  
	  
		@Override
		protected List getFieldOrder() {
			// TODO Auto-generated method stub
			return Arrays.asList(new String[]{"Erase","WriteInfo","Write","Check","SetBaudRate","Excute","CmdSuccess","CmdFaild"});
		}
        //Bootloader�������
        public byte   Erase;            //����APP������������
        public byte   WriteInfo;        //���ö��ֽ�д������ز�����д��ʼ��ַ����������
        public byte   Write;            //�Զ��ֽ���ʽд����
        public byte   Check;            //���ڵ��Ƿ����ߣ�ͬʱ���ع̼���Ϣ
        public byte   SetBaudRate;    //���ýڵ㲨����
        public byte   Excute;            //ִ�й̼�
        //�ڵ㷵��״̬
        public byte   CmdSuccess;        //����ִ�гɹ�
        public byte   CmdFaild;        //����ִ��ʧ��
    }
	//USB2CAN��������
	int  CAN_Init(int DevIndex, byte CANIndex, CAN_INIT_CONFIG pCanConfig);
	int  CAN_Filter_Init(int DevIndex, byte CANIndex, CAN_FILTER_CONFIG pFilterConfig);
	int  CAN_SendMsg(int DevIndex, byte CANIndex, CAN_MSG pCanSendMsg,int SendMsgNum);
	int  CAN_GetMsg(int DevIndex, byte CANIndex, CAN_MSG pCanGetMsg);
	int  CAN_GetStatus(int DevIndex, byte CANIndex, CAN_STATUS pCANStatus);

	int  CAN_BL_Init(int DevIndex,int CANIndex,CAN_INIT_CONFIG pInitConfig,CBL_CMD_LIST pCmdList);
	int  CAN_BL_NodeCheck(int DevIndex,int CANIndex,short NodeAddr,int[] pVersion,int[] pType,int TimeOut);
	int  CAN_BL_Erase(int DevIndex,int CANIndex,short NodeAddr,int FlashSize,int TimeOut);
	int  CAN_BL_Write(int DevIndex,int CANIndex,short NodeAddr,int AddrOffset,byte[] pData,int DataNum,int TimeOut);
	int  CAN_BL_Excute(int DevIndex,int CANIndex,short NodeAddr,int Type);
	int  CAN_BL_SetNewBaudRate(int DevIndex,int CANIndex,short NodeAddr,CAN_INIT_CONFIG pInitConfig,int NewBaudRate,int TimeOut);

}
