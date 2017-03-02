package com.usbxyz;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

public interface USB2SPI extends Library {
	USB2SPI INSTANCE  = (USB2SPI)Native.loadLibrary("USB2XXX",USB2SPI.class); 
	
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

	
}
