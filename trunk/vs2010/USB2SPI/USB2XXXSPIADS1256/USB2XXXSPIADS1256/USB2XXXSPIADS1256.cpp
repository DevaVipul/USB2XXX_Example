  /*
  ******************************************************************************
  * @file     : USB2XXXSPIADS1256.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : USB2XXX SPI M95128 test demo
  ******************************************************************************
  * @attention
  *
  * Copyright 2009-2014, usbxyz.com
  * http://www.usbxyz.com/
  * All Rights Reserved
  * 
  ******************************************************************************
  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "usb_device.h"
#include "usb2spi.h"
#include "usb2gpio.h"
/*
Ӳ������˵��
USB2XXX     ADS1256
--------------------
P0          DRDY
P1          RESET
P4          CS
P5          SCLK
P6          DOUT
P7          DIN
*/
//����ģʽ����
#define SINGLE_ENDED_MODE   1//����ģʽ����Ϊ1�����ģʽ����Ϊ0
#define GET_DATA_TO_FILE    0
// define commands 
#define ADS1256_CMD_WAKEUP   0x00 
#define ADS1256_CMD_RDATA    0x01 
#define ADS1256_CMD_RDATAC   0x03 
#define ADS1256_CMD_SDATAC   0x0f 
#define ADS1256_CMD_RREG     0x10 
#define ADS1256_CMD_WREG     0x50 
#define ADS1256_CMD_SELFCAL  0xf0 
#define ADS1256_CMD_SELFOCAL 0xf1 
#define ADS1256_CMD_SELFGCAL 0xf2 
#define ADS1256_CMD_SYSOCAL  0xf3 
#define ADS1256_CMD_SYSGCAL  0xf4 
#define ADS1256_CMD_SYNC     0xfc 
#define ADS1256_CMD_STANDBY  0xfd 
#define ADS1256_CMD_REST    0xfe 
 
// define the ADS1256 register values 
#define ADS1256_STATUS       0x00   
#define ADS1256_MUX          0x01   
#define ADS1256_ADCON        0x02   
#define ADS1256_DRATE        0x03   
#define ADS1256_IO           0x04   
#define ADS1256_OFC0         0x05   
#define ADS1256_OFC1         0x06   
#define ADS1256_OFC2         0x07   
#define ADS1256_FSC0         0x08   
#define ADS1256_FSC1         0x09   
#define ADS1256_FSC2         0x0A 
 
 
// define multiplexer codes 
#define ADS1256_MUXP_AIN0   0x00 
#define ADS1256_MUXP_AIN1   0x10 
#define ADS1256_MUXP_AIN2   0x20 
#define ADS1256_MUXP_AIN3   0x30 
#define ADS1256_MUXP_AIN4   0x40 
#define ADS1256_MUXP_AIN5   0x50 
#define ADS1256_MUXP_AIN6   0x60 
#define ADS1256_MUXP_AIN7   0x70 
#define ADS1256_MUXP_AINCOM 0x80 
 
#define ADS1256_MUXN_AIN0   0x00 
#define ADS1256_MUXN_AIN1   0x01 
#define ADS1256_MUXN_AIN2   0x02 
#define ADS1256_MUXN_AIN3   0x03 
#define ADS1256_MUXN_AIN4   0x04 
#define ADS1256_MUXN_AIN5   0x05 
#define ADS1256_MUXN_AIN6   0x06 
#define ADS1256_MUXN_AIN7   0x07 
#define ADS1256_MUXN_AINCOM 0x08   
 
 
// define gain codes 
#define ADS1256_GAIN_1      0x00 
#define ADS1256_GAIN_2      0x01 
#define ADS1256_GAIN_4      0x02 
#define ADS1256_GAIN_8      0x03 
#define ADS1256_GAIN_16     0x04 
#define ADS1256_GAIN_32     0x05 
#define ADS1256_GAIN_64     0x06 
//#define ADS1256_GAIN_64     0x07 
 
//define drate codes 
#define ADS1256_DRATE_30000SPS   0xF0 
#define ADS1256_DRATE_15000SPS   0xE0 
#define ADS1256_DRATE_7500SPS   0xD0 
#define ADS1256_DRATE_3750SPS   0xC0 
#define ADS1256_DRATE_2000SPS   0xB0 
#define ADS1256_DRATE_1000SPS   0xA1 
#define ADS1256_DRATE_500SPS    0x92 
#define ADS1256_DRATE_100SPS    0x82 
#define ADS1256_DRATE_60SPS     0x72 
#define ADS1256_DRATE_50SPS     0x63 
#define ADS1256_DRATE_30SPS     0x53 
#define ADS1256_DRATE_25SPS     0x43 
#define ADS1256_DRATE_15SPS     0x33 
#define ADS1256_DRATE_10SPS     0x23 
#define ADS1256_DRATE_5SPS      0x13 
#define ADS1256_DRATE_2_5SPS    0x03


//������
int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    unsigned char WriteBuffer[1024]={0};
    unsigned char ReadBuffer[20480];
    int DevIndex = 0;
    int ResetPinMask,DrdyPinMask;
    int ADS1256Index = SPI1_CS0;
    bool state;
    int ret,k=0;
    //ɨ������豸
    ret = USB_ScanDevice(NULL);
    if(ret <= 0){
        printf("No device connected!\n");
        return 0;
    }
    //���豸
    state = USB_OpenDevice(DevIndex);
    if(!state){
        printf("Open device error!\n");
        return 0;
    }
    //��ȡ�̼���Ϣ
    char FuncStr[128]={0};
    state = USB_GetDeviceInfo(DevIndex,&DevInfo,FuncStr);
    if(!state){
        printf("Get device infomation error!\n");
        return 0;
    }else{
        printf("Firmware Name:%s\n",DevInfo.FirmwareName);
        printf("Firmware Build Date:%s\n",DevInfo.BuildDate);
        printf("Firmware Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("Hardware Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
        printf("Firmware Functions:%s\n",FuncStr);
    }
    //����RESET���ź�DRADY����
    if (ADS1256Index == 0)
    {
        ResetPinMask = 1 << 9;
        DrdyPinMask = 1 << 8;
    }
    else
    {
        ResetPinMask = 1 << 1;
        DrdyPinMask = 1 << 0;
    }
    ret = GPIO_SetOutput(DevIndex, ResetPinMask, 1);
    if (ret != GPIO_SUCCESS)
    {
        printf("Initialize gpio error!\r\n");
        return 0;
    }
    //����SPI������ز���
    SPI_CONFIG SPIConfig;
    SPIConfig.Mode = SPI_MODE_HARD_HDX;//��оƬ֧�ֵ�ʱ��Ƶ�ʽϵͣ�����ʹ�����ģʽ
    SPIConfig.ClockSpeedHz = 1562500;
    SPIConfig.CPHA = 1;
    SPIConfig.CPOL = 0;
    SPIConfig.LSBFirst = SPI_MSB;
    SPIConfig.Master = SPI_MASTER;
    SPIConfig.SelPolarity = SPI_SEL_LOW;
    ret = SPI_Init(DevIndex,ADS1256Index,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Initialize device error!\r\n");
        return 0;
    }
    //RESET������������帴λADS1256
    GPIO_Write(DevIndex, ResetPinMask, 0); //����͵�ƽ
    Sleep(10);
    GPIO_Write(DevIndex, ResetPinMask, ResetPinMask);  //����ߵ�ƽ
    //׼�����üĴ�������
    WriteBuffer[0] = 0x50;//ADS1256_CMD_WREG
    WriteBuffer[1] = 0x04;
    WriteBuffer[2] = 0x04;
    WriteBuffer[3] = 0x08;//����AIN0Ϊ����ģʽ
    WriteBuffer[4] = 0;   //PGA
    WriteBuffer[5] = 0xA1;//1000SPS
    WriteBuffer[6] = 0xFF;
    ret = SPI_WriteBytesOfEvent(DevIndex, ADS1256Index, WriteBuffer, 7, DrdyPinMask, 0x00, 1000);
    if (ret != SPI_SUCCESS)
    {
        printf("SPI Event Write Data Error!\r\n");
        return 0;
    }
    //׼�������üĴ������ݣ���֤��������д���Ƿ�ɹ�
    WriteBuffer[0] = 0x10;//ADS1256_CMD_RREG;
    WriteBuffer[1] = 4;
    ret = SPI_WriteReadBytesOfEvent(DevIndex, ADS1256Index, WriteBuffer, 2, ReadBuffer,5,10,DrdyPinMask, 0x10, 1000);
    if (ret != SPI_SUCCESS)
    {
        printf("SPI Event Write&Read Data Error!\r\n");
        return 0;
    }
    //�ж�д�����üĴ�����ֵ�Ͷ����Ĵ�����ֵ�Ƿ�һ��
    if ((WriteBuffer[3] != ReadBuffer[1]) || (WriteBuffer[4] != ReadBuffer[2]) || (WriteBuffer[5] != ReadBuffer[3]))
    {
        printf("Config ADS1256 Error!\r\n");
        return 0;
    }
    //���������ɼ��������������ֻ�ʺ������ɼ�һ��ͨ�������
    WriteBuffer[0] = 0xFC;//ADS1256_CMD_SYNC
    WriteBuffer[1] = 0x00;//ADS1256_CMD_WAKEUP
    WriteBuffer[2] = 0x03;//ADS1256_CMD_RDATAC
    ret = SPI_WriteReadBytesOfEvent(DevIndex, ADS1256Index, WriteBuffer, 3, ReadBuffer, 3, 10, DrdyPinMask, 0x10, 1000);
    if (ret != SPI_SUCCESS)
    {
        printf("SPI Event Write&Read Data Error!\r\n");
        return 0;
    }
    printf("Continuous Get ADC Data!\r\n");
    //���DRADY�����½���֮���������
    int ReadDataNum = 512;
    ret = SPI_BlockReadBytesOfEvent(DevIndex, ADS1256Index, ReadBuffer, 3, ReadDataNum, DrdyPinMask, 0x10, 100);
    if (ret != SPI_SUCCESS)
    {
        printf("SPI Event BlockRead Data Error!");
        return 0;
    }
#if !GET_DATA_TO_FILE
    //�����ص�����ת��Ϊʵ�ʵĵ�ѹֵ
    for (int i = 0; i < ReadDataNum; i++)
    {
        int ADCDataTemp = (ReadBuffer[i * 3 + 0] << 16) | (ReadBuffer[i * 3 + 1] << 8) | ReadBuffer[i * 3 + 2];
        if ((ADCDataTemp & 0x800000) != 0x00)
        {
            ADCDataTemp = (0xFF000000 | ADCDataTemp);
        }
        double Volutage = (ADCDataTemp * 0.59604644775390625)/1000000;
        printf("ADC[%d] = %f V   %08X\r\n", i, Volutage,ADCDataTemp);
    }
#else
    //������д���ļ�
    FILE *fp;
    if((fp=fopen("ADCData.csv","wb"))==NULL){
        printf("Cannot open file!");
        return 0;
    }
    for (int i = 0; i < ReadDataNum; i++)
    {
        int ADCDataTemp = (ReadBuffer[i * 3 + 0] << 16) | (ReadBuffer[i * 3 + 1] << 8) | ReadBuffer[i * 3 + 2];
        if ((ADCDataTemp & 0x800000) != 0x00)
        {
            ADCDataTemp = (0xFF000000 | ADCDataTemp);
        }
        double Volutage = (ADCDataTemp * 0.59604644775390625)/1000000;
        fprintf(fp,"ADC[%d] = %f V\n", i, Volutage);
    }
    fclose(fp);
#endif
    //����ֹͣ����������������
    WriteBuffer[0] = 0x0F;//ADS1256_CMD_SDATAC
    ret = SPI_WriteBytesOfEvent(DevIndex, ADS1256Index, WriteBuffer, 1, DrdyPinMask, 0x10, 1000);
    if (ret != SPI_SUCCESS)
    {
        printf("SPI Event Write Data Error!\r\n");
        return 0;
    }
    printf("Circulate Get ADC Data!\r\n");
    //ѭ���ɼ�ÿ��ͨ������
    ReadDataNum = 3;
    byte Channel = 0;
    WriteBuffer[0] = 0x50|1;//ADS1256_CMD_WREG
    WriteBuffer[1] = 0x00;
    WriteBuffer[2] = ((Channel << 4) | 0x08);
    WriteBuffer[3] = 0xFC;//ADS1256_CMD_SYNC
    WriteBuffer[4] = 0x00;//ADS1256_CMD_WAKEUP
    WriteBuffer[5] = 0x01;//ADS1256_CMD_RDATA
    for (int i = 0; i < ReadDataNum; i++)
    {
        for (Channel = 0; Channel < 8; Channel++)
        {
            WriteBuffer[2] = ((Channel << 4) | 0x08);
            ret = SPI_WriteReadBytesOfEvent(DevIndex, ADS1256Index, WriteBuffer, 6, ReadBuffer, 3, 10, DrdyPinMask, 0x10, 1000);
            if (ret != SPI_SUCCESS)
            {
                printf("SPI Event Write&Read Data Error!\r\n");
                return 0;
            }
            else
            {
                //������һ�ε�����
                if ((i == 0) && (Channel == 0))
                {
                    continue;
                }
                int ADCDataTemp = (ReadBuffer[0] << 16) | (ReadBuffer[1] << 8) | ReadBuffer[2];
                if ((ADCDataTemp & 0x800000) != 0x00)
                {
                    ADCDataTemp = (0xFF000000 | ADCDataTemp);
                }
                double Volutage = (ADCDataTemp * 0.59604644775390625) / 1000000;
                printf("ADC_CH[%d][%d] = %f V\r\n", i, Channel == 0 ? 7 : Channel - 1, Volutage);
            }
        }
    }
    printf("ADS1256 Test OK\n");
    getchar();
    //�ر��豸
    USB_CloseDevice(DevIndex);
    return 0;
}