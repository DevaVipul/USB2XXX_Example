/**
  ******************************************************************************
  * @file    usb2nand.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   usb2nand��غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxyz.com">http://www.usbxyz.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __USB2NAND_H_
#define __USB2NAND_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

//����NAND�ĵ�ַ
typedef struct _NAND_ADDRESS
{
  unsigned short Block;     //���ַ
  unsigned short Page;      //ҳ��ַ
  unsigned short Column;    //��ÿ��Page�е�ƫ�Ƶ�ַ
}NAND_ADDRESS,*PNAND_ADDRESS;

//����NAND�洢����֯��ʽ
typedef struct _NAND_MEMORY_INFO
{
  unsigned int LUNPerChip;        //LUN number(LUN)��оƬ�ϵ�LUN��
  unsigned int PlanePerLUN;       //Plane number(Plane)��ÿ��LUN�ϵ�Plane��
  unsigned int BlockPerPlane;     //Plane size(Block),ÿ��Plane�ϵ�Block��
  unsigned int PagePerBlock;      //Block size(Page)��ÿ��Block�ϵ�Page��
  unsigned int BytesPerPage;      //Page size(Byte),ÿ��Page�ϵ��ֽ���
  unsigned int SpareAreaSize;     //Spare area size(Byte)��ÿ��Page��Spare Area�ֽ���
}NAND_MEMORY_INFO,*PNAND_MEMORY_INFO;

//����NAND Flash�������ò�����������
typedef struct _NAND_FLASH_CONFIG{
    unsigned char CMD_WritePage[2];
    unsigned char CMD_EraseBlock[2];
    unsigned char CMD_Reset;
    unsigned char CMD_ReadID;
    unsigned char CMD_ReadIDAddr;
    unsigned char CMD_ReadPage[2];
    unsigned char CMD_ReadStatus;
    unsigned char ID[16];
    unsigned char ID_Length;
}NAND_FLASH_CONFIG,*PNAND_FLASH_CONFIG;

//����NAND����ʱ�����
typedef struct _NAND_TIMING_COMFIG{
  uint32_t FSMC_SetupTime;
  uint32_t FSMC_WaitSetupTime;
  uint32_t FSMC_HoldSetupTime;
  uint32_t FSMC_HiZSetupTime;
}NAND_TIMING_COMFIG,*PNAND_TIMING_COMFIG;
/* NAND memory status */
#define NAND_STATUS_VALID_ADDRESS         ((uint32_t)0x00000100)
#define NAND_STATUS_INVALID_ADDRESS       ((uint32_t)0x00000200)
#define NAND_STATUS_TIMEOUT_ERROR         ((uint32_t)0x00000400)
#define NAND_STATUS_BUSY                  ((uint32_t)0x00000000)
#define NAND_STATUS_ERROR                 ((uint32_t)0x00000001)
#define NAND_STATUS_READY                 ((uint32_t)0x00000040)

//���庯�����ش������
#define NAND_SUCCESS             (0)   //����ִ�гɹ�
#define NAND_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define NAND_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define NAND_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define NAND_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��

#ifdef __cplusplus
extern "C"
{
#endif
/**
  * @brief  ��ʼ������NAND�ӿڣ��ú����������
  * @param  DevHandle �豸������
  * @param  ChipIndex NANDоƬƬѡ�ţ�ȡֵ0����1
  * @param  PageSize NAND Flashÿҳ�ֽ������������������ֽ���
  * @param  pTimeConfig ��NAND���ж�д������ʱ�����
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI NAND_Init(int DevHandle,int ChipIndex,PNAND_TIMING_COMFIG pTimeConfig);

/**
  * @brief  ��ʼ������NAND�ӿڣ��ú����������
  * @param  DevHandle �豸������
  * @param  ChipIndex NANDоƬƬѡ�ţ�ȡֵ0����1
  * @param  pNandConfig ����NAND Flash��ز�������
  * @param  pNandMemInfo ����NAND Flash���������Ϣ
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI NAND_SetChipInfo(int DevHandle,int ChipIndex,PNAND_FLASH_CONFIG pNandConfig,PNAND_MEMORY_INFO pNandMemInfo);

/**
  * @brief  ��ȡNAND FlashоƬID��Ϣ
  * @param  DevHandle �豸������
  * @param  ChipIndex NANDоƬƬѡ�ţ�ȡֵ0����1
  * @param  pNandID оƬID�洢�������׵�ַ
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI NAND_ReadID(int DevHandle,int ChipIndex,unsigned char IDAddr,unsigned char *pID,unsigned char IDLen);

/**
  * @brief  ��NAND Flashд�����ݣ����鰴����ҳд��Ȼ���ٽ��ú������ص�ECCд�뱸�������Ա��Ժ��ȡ��ʱ�򽫶������ݵ�ECC��д��ECC���Աȣ�ʵ�ֶ����ݵ�У��
  * @param  DevHandle �豸������
  * @param  ChipIndex NANDоƬƬѡ�ţ�ȡֵ0����1
  * @param  pStartAddr д���ݵ�ַ
  * @param  pWriteData ��д��NAND FlashоƬ�����ݻ������׵�ַ
  * @param  NumByteToWrite ��д��NAND FlashоƬ�������ֽ���
  * @param  pECC д��NAND�����ݼ������ECCֵ��ÿҳ���ݻ�����һ��ECC����д����Nҳ���ݣ���ô�᷵��N��ECC����
  * @param  TimeOutMs �ȴ�д��������ϵĳ�ʱ��������λΪ���룬�ò���Ӧ������������д��Flash��ʱ��
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
//int WINAPI NAND_WritePage(int DevHandle,int ChipIndex,PNAND_ADDRESS pStartAddr,unsigned char *pWriteData, int NumByteToWrite,unsigned int *pECC,int TimeOutMs);
int WINAPI NAND_WritePage(int DevHandle,int ChipIndex,unsigned char *pCmds,unsigned char CmdsLen,unsigned char *pAddrs,unsigned char AddrLen,unsigned char *pWriteData,int NumByteToWrite,int TimeOutMs);
/**
  * @brief  ��NAND Flash�������ݣ����鰴����ҳ���������ݵ�ʱ��᷵��ÿҳ��ECCֵ�����Ժͱ�������ECCֵ����У��Ա�
  * @param  DevHandle �豸������
  * @param  ChipIndex NANDоƬƬѡ�ţ�ȡֵ0����1
  * @param  pStartAddr �����ݵ�ַ
  * @param  pReadData �洢�������ݵĻ������׵�ַ
  * @param  NumByteToRead �������������ֽ���
  * @param  pECC ����NAND�����ݼ������ECCֵ��ÿҳ���ݻ�����һ��ECC����������Nҳ���ݣ���ô�᷵��N��ECC����
  * @param  TimeOutMs �ȴ�����������ϵĳ�ʱ��������λΪ���룬�ò���Ӧ�����������ݶ���Flash��ʱ��
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
//int WINAPI NAND_ReadPage (int DevHandle,int ChipIndex, PNAND_ADDRESS pStartAddr,unsigned char *pReadData, int NumByteToRead,unsigned int *pECC,int TimeOutMs);
int WINAPI NAND_ReadPage (int DevHandle,int ChipIndex, unsigned char *pCmds,unsigned char CmdsLen,unsigned char *pAddrs,unsigned char AddrLen,unsigned char *pReadData, int NumByteToRead,int TimeOutMs);
/**
  * @brief  ��NAND Flash������д�����ݣ�����д��ÿҳ��ECCֵ���Լ������־���ݣ��ú������ֻ�ܲ���һҳ�ı�����
  * @param  DevHandle �豸������
  * @param  ChipIndex NANDоƬƬѡ�ţ�ȡֵ0����1
  * @param  pStartAddr д���ݵ�ַ
  * @param  pWriteSpareAreaData ��д�뱸���������ݻ������׵�ַ
  * @param  NumByteToWrite ��д�뱸�����������ֽ���
  * @param  TimeOutMs д�뱸�������ݳ�ʱ��������λΪ����
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI NAND_WriteSpareArea(int DevHandle,int ChipIndex, PNAND_ADDRESS pStartAddr,unsigned char *pWriteSpareAreaData, int NumByteToWrite,int TimeOutMs);

/**
  * @brief  ��NAND Flash�������������ݣ�����ÿҳ��ECCֵ�������־ֵ���ú������ֻ�ܲ���һҳ�ı�����
  * @param  DevHandle �豸������
  * @param  ChipIndex NANDоƬƬѡ�ţ�ȡֵ0����1
  * @param  pStartAddr �����ݵ�ַ
  * @param  pReadSpareAreaData �������������ݴ洢�������׵�ַ
  * @param  NumByteToRead ���������ֽ���
  * @param  TimeOutMs �����������ݳ�ʱ��������λΪ����
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int WINAPI NAND_ReadSpareArea(int DevHandle,int ChipIndex, PNAND_ADDRESS pStartAddr,unsigned char *pReadSpareAreaData, int NumByteToRead,int TimeOutMs);

/**
  * @brief  �������NAND Flash���ݣ��������������ݱ��0xFF
  * @param  DevHandle �豸������
  * @param  ChipIndex NANDоƬƬѡ�ţ�ȡֵ0����1
  * @param  pStartAddr ��������ʼ��ַ
  * @param  NumBlockToErase ׼�������Ŀ���
  * @param  TimeOutMs �������ݳ�ʱ��������λΪ����
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
//int WINAPI NAND_EraseBlock(int DevHandle,int ChipIndex,PNAND_ADDRESS pStartAddr,int NumBlockToErase,int TimeOutMs);
int WINAPI NAND_EraseBlock(int DevHandle,int ChipIndex,unsigned char *pCmds,unsigned char CmdsLen,unsigned char *pAddrs,unsigned char AddrLen,int TimeOutMs);


int WINAPI NAND_SendCmd(int DevHandle,int ChipIndex,unsigned char *pCmds,unsigned char CmdsLen, unsigned char CEPolarity);
int WINAPI NAND_SendAddr(int DevHandle,int ChipIndex,unsigned char *pAddrs,unsigned char AddrsLen, unsigned char CEPolarity);
int WINAPI NAND_WriteData(int DevHandle,int ChipIndex,unsigned char *pWriteData,unsigned int WriteDataLen, unsigned char CEPolarity);
int WINAPI NAND_ReadData(int DevHandle,int ChipIndex,unsigned char *pReadData,unsigned int ReadDataLen, unsigned char CEPolarity);
int WINAPI NAND_WaitReady(int DevHandle,int ChipIndex,unsigned int WaitTimeoutUs);

#ifdef __cplusplus
}
#endif

#endif
