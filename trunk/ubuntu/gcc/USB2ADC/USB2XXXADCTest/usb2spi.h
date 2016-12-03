/**
  ******************************************************************************
  * @file    usb2spi.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   usb2spi��غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxyz.com">http://www.usbxyz.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __USB2SPI_H_
#define __USB2SPI_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif
//����SPIͨ��
#define SPI1        (0x00)
#define SPI1_CS0    (0x00)
#define SPI1_CS1    (0x10)
#define SPI1_CS2    (0x20)
#define SPI1_CS3    (0x30)
#define SPI1_CS4    (0x40)

#define SPI2        (0x01)
#define SPI2_CS0    (0x01)
#define SPI2_CS1    (0x11)
#define SPI2_CS2    (0x21)
#define SPI2_CS3    (0x31)
#define SPI2_CS4    (0x41)
//���幤��ģʽ
#define SPI_MODE_HARD_FDX       0 //Ӳ�����ƣ�ȫ˫��ģʽ��
#define SPI_MODE_HARD_HDX       1 //Ӳ�����ƣ���˫��ģʽ��
#define SPI_MODE_SOFT_HDX       2 //������ƣ���˫��ģʽ��
#define SPI_MODE_SOFT_ONE_WIRE  3 //������ģʽ�����������������ΪMOSI
//�������ӻ�ģʽ
#define SPI_MASTER      1 //����
#define SPI_SLAVE       0 //�ӻ�
//����������λ��ʽ
#define SPI_MSB         0 //��λ��ǰ
#define SPI_LSB         1 //��λ��ǰ
//����Ƭѡ�������
#define SPI_SEL_LOW     0 //Ƭѡ����͵�ƽ
#define SPI_SEL_HIGH    1 //Ƭѡ����ߵ�ƽ

//����ӻ�ģʽ��������ȡ���ݵĻص�����
typedef  int (WINAPI SPI_GET_DATA_HANDLE)(int DevIndex,int SPIIndex,unsigned char *pData,int DataNum);//�������ݻص�����

//�����ʼ��SPI����������
typedef struct _SPI_CONFIG{
    char   Mode;            //SPI���Ʒ�ʽ:0-Ӳ�����ƣ�ȫ˫��ģʽ��,1-Ӳ�����ƣ���˫��ģʽ����2-������ƣ���˫��ģʽ��,3-������ģʽ�����������������ΪMOSI
    char   Master;          //����ѡ�����:0-�ӻ���1-����
    char   CPOL;            //ʱ�Ӽ��Կ���:0-SCK����ʱΪ�͵�ƽ��1-SCK����ʱΪ�ߵ�ƽ
    char   CPHA;            //ʱ����λ����:0-��һ��SCKʱ�Ӳ�����1-�ڶ���SCKʱ�Ӳ���
    char   LSBFirst;        //������λ��ʽ:0-MSB��ǰ��1-LSB��ǰ
    char   SelPolarity;     //Ƭѡ�źż���:0-�͵�ƽѡ�У�1-�ߵ�ƽѡ��
    unsigned int ClockSpeedHz;    //SPIʱ��Ƶ��:��λΪHZ��Ӳ��ģʽ�����50000000����С390625��Ƶ�ʰ�2�ı����ı�
}SPI_CONFIG,*PSPI_CONFIG;

//����SPI Flash�������ò�����������
typedef struct _SPI_FLASH_CONFIG{
    unsigned char CMD_WriteEnable;          //ʹ��д����
    unsigned char CMD_WriteDisable;         //��ֹд����
    unsigned char CMD_WritePage;            //д��������
    unsigned char WritePageAddressBytes;    //д����ʱ�ĵ�ַ��ȣ���λΪ�ֽ�
    unsigned char CMD_EraseSector;          //������������
    unsigned char EraseSectorAddressBytes;  //���������ĵ�ַ��ȣ���λΪ�ֽ�
    unsigned char CMD_EraseBulk;            //���������
    unsigned char CMD_EraseChip;            //��Ƭ��������
    unsigned char CMD_ReadID;               //��оƬID����
    unsigned char CMD_ReadData;             //����������
    unsigned char ReadDataAddressBytes;     //������ʱ�ĵ�ַ��ȣ���λΪ�ֽ�
    unsigned char CMD_ReadFast;             //����ģʽ����������
    unsigned char ReadFastAddressBytes;     //���ٶ�����ʱ�ĵ�ַ��ȣ���λΪ�ֽ�
    unsigned char CMD_ReadStatus;           //��ȡ״̬�Ĵ�������
    unsigned char CMD_WriteStatus;          //д״̬�Ĵ�������
    unsigned char ID[16];                   //оƬID�洢����
    unsigned char ID_Length;                //ID���ȣ���λΪ�ֽ�
    int PageSize;                           //ҳ��С����λΪ�ֽ�
    int NumPages;                           //оƬ�ܵ�ҳ��
    int SectorSize;                         //������С����λΪ�ֽ�
}SPI_FLASH_CONFIG,*PSPI_FLASH_CONFIG;

//���庯�����ش������
#define SPI_SUCCESS             (0)   //����ִ�гɹ�
#define SPI_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define SPI_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define SPI_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define SPI_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��
#define SPI_ERR_PARAMETER       (-5)  //��������
#ifdef __cplusplus
extern "C"
{
#endif
/**
  * @brief  SPI��ʼ�����ú���
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pConfig SPI��ʼ�����ýṹ��ָ��
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_Init(int DevIndex,int SPIIndex, PSPI_CONFIG pConfig);

/**
  * @brief  SPI��������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pWriteData ���ݷ��ͻ������׵�ַ
  * @param  WriteLen ���ݷ����ֽ���
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_WriteBytes(int DevIndex,int SPIIndex,unsigned char *pWriteData,int WriteLen);

/**
  * @brief  SPI�첽��ʽ�������ݣ���������֮�󲻻�ȴ����ݷ�����ϣ��÷�ʽ���ԼӴ����ݷ�������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pWriteData ���ݷ��ͻ������׵�ַ
  * @param  WriteLen ���ݷ����ֽ���
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_AsyncWriteBytes(int DevIndex,int SPIIndex,unsigned char *pWriteData,int WriteLen);

/**
  * @brief  SPI��������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pReadData ���ݽ��ջ������׵�ַ
  * @param  ReadLen ���������ֽ���
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_ReadBytes(int DevIndex,int SPIIndex,unsigned char *pReadData,int ReadLen);

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
int WINAPI SPI_WriteReadBytes(int DevIndex,int SPIIndex,unsigned char *pWriteData,int WriteLen,unsigned char *pReadData,int ReadLen,int IntervalTimeUs);

/**
  * @brief  ������ģʽд���ݣ��ú������Է�������bit������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pWriteBitStr �����������ַ������磺"100110011"
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_WriteBits(int DevIndex,int SPIIndex,char *pWriteBitStr);

/**
  * @brief  ������ģʽ�����ݣ��ú������Զ�ȡ����bit������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pReadBitStr ��ȡ���Ķ����������ַ������磺"100110011"
  * @param  ReadBitsNum ��ȡ���ݵĶ�����bit��
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_ReadBits(int DevIndex,int SPIIndex,char *pReadBitStr,int ReadBitsNum);

/**
  * @brief  ������ģʽд�����ݣ��ú�������д��ȡ����bit������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pWriteBitStr д�����������ַ������磺"100110011"
  * @param  pReadBitStr ��ȡ���Ķ����������ַ������磺"100110011"
  * @param  ReadBitsNum ��ȡ���ݵĶ�����bit��
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_WriteReadBits(int DevIndex,int SPIIndex,char *pWriteBitStr,char *pReadBitStr,int ReadBitsNum);

/**
  * @brief  SPI�ӻ�ģʽ�½�����д�����ݷ��ͻ��������ȴ�������ʱ���ź��ٽ����ݷ��ͳ�ȥ
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pWriteData �������ݻ������׵�ַ
  * @param  WriteLen ���������ֽ���
  * @param  TimeOutMs �ȴ����ݷ�����ϳ�ʱʱ�䣬��С�ڻ��ߵ���0�򲻻�ȴ����ݷ�����ϣ�������������
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_SlaveWriteBytes(int DevIndex,int SPIIndex,unsigned char *pWriteData,int WriteLen,int TimeOutMs);

/**
  * @brief  SPI�ӻ�ģʽ�»�ȡ�������ݻ�����������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pReadData ���ݽ��ջ������׵�ַ
  * @param  pReadLen ���յ��������ֽ���
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_SlaveReadBytes(int DevIndex,int SPIIndex,unsigned char *pReadData,int TimeOutMs);

/**
  * @brief  SPI�ӻ�ģʽ��������ȡ����,SPI�ڴӻ�ģʽ�½��յ�����֮��ͨ���ص�������������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pSlaveReadDataHandle �ӻ�ģʽ�½��յ����ݺ�Ļص�����
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_SlaveContinueRead(int DevIndex,int SPIIndex,SPI_GET_DATA_HANDLE *pSlaveReadDataHandle);

/**
  * @brief  SPI�ӻ�ģʽ�»�ȡ�������ݻ�����������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pReadData ���ݽ��ջ������׵�ַ
  * @param  BufferSize ���ݻ�������С
  * @retval ��ȡ���������ֽ���
  */
int WINAPI SPI_SlaveGetBytes(int DevIndex,int SPIIndex,unsigned char *pReadData,int BufferSize);
/**
  * @brief  ֹͣSPI�ӻ�ģʽ��������ȡ����
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_SlaveContinueReadStop(int DevIndex,int SPIIndex);
/**
  * @brief  ��дSPI-Flash��ʼ������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  ClockSpeed SPIʱ���ź�Ƶ�ʣ���λΪHz,���Ϊ50MHz�����γɱ��ݼ�
  * @param  pConfig SPI-Flash��ز���
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_FlashInit(int DevIndex,int SPIIndex,int ClockSpeed, PSPI_FLASH_CONFIG pConfig);

/**
  * @brief  ��ȡSPI-FlashоƬ��ID��
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  pID оƬID�Ŵ洢�׵�ַ���䳤����SPI_FLASH_CONFIG�е�ID_Length����
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_FlashReadID(int DevIndex,int SPIIndex,unsigned char *pID);

/**
  * @brief  ����SPI-Flash����������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  StartSector ��ʼ�����ţ�ע���������ţ����Ǿ����������ַ
  * @param  NumSector ��Ҫ������������
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_FlashEraseSector(int DevIndex,int SPIIndex,int StartSector,int NumSector);

/**
  * @brief  ����SPI-Flash����оƬ������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_FlashEraseChip(int DevIndex,int SPIIndex);


/**
  * @brief  ��SPI-Flashд����
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  StartAddr д������ʼ��ַ
  * @param  pWriteData д���ݻ������׵�ַ
  * @param  WriteLen д�����ֽ���
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_FlashWrite(int DevIndex,int SPIIndex,int StartAddr,unsigned char *pWriteData,int WriteLen);

/**
  * @brief  ��SPI-Flash������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  StartAddr д������ʼ��ַ
  * @param  pReadData �����ݻ������׵�ַ
  * @param  ReadLen �������ֽ���
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_FlashRead(int DevIndex,int SPIIndex,int StartAddr,unsigned char *pReadData,int ReadLen);

/**
  * @brief  ��SPI-Flash������
  * @param  DevIndex �豸������
  * @param  SPIIndex SPIͨ���ţ�ȡֵ0����1
  * @param  StartAddr д������ʼ��ַ
  * @param  pReadData �����ݻ������׵�ַ
  * @param  ReadLen �������ֽ���
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI SPI_FlashReadFast(int DevIndex,int SPIIndex,int StartAddr,unsigned char *pReadData,int ReadLen);

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
int WINAPI SPI_BlockWriteBytes(int DevIndex,int SPIIndex,unsigned char *pWriteData,int BlockSize,int BlockNum,int IntervalTimeUs);

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
int WINAPI SPI_BlockReadBytes(int DevIndex,int SPIIndex,unsigned char *pReadData,int BlockSize,int BlockNum,int IntervalTimeUs);

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
int WINAPI SPI_BlockWriteReadBytes(int DevIndex,int SPIIndex,unsigned char *pWriteData,int WriteBlockSize,unsigned char *pReadData,int ReadBlockSize,int BlockNum,int IntervalTimeUs);

#ifdef __cplusplus
}
#endif

#endif

