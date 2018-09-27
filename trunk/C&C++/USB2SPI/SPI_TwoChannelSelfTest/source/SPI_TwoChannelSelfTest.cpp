     /*
  ******************************************************************************
  * @file     : SPI_TwoChannelSelfTest.cpp
  * @Copyright: usbxyz 
  * @Revision : ver 1.0
  * @Date     : 2014/12/19 9:33
  * @brief    : SPI����ͨ���Խӣ�һ������Ϊ����һ������Ϊ�ӣ�ʵ�������շ�
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
/*
Ӳ������˵����ͬһ��������������SPIͨ���Խӣ�
P13(SPI1_CS0)	<-->	P4(SPI2_CS0)
P12(SPI1_SCK)	<-->	P5(SPI2_SCK)
P11(SPI1_MISO)	<-->	P6(SPI2_MISO)
P10(SPI1_MOSI)	<-->	P7(SPI2_MOSI)
*/

//������
int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    SPI_CONFIG SPIConfig;
    int DevHandles[10];
    int SPIMasterIndex = SPI1_CS0;
	int SPISlaveIndex = SPI2_CS0;
    bool state;
    int ret;
    unsigned char WriteBuffer[1024];
    unsigned char ReadBuffer[1024];
    //ɨ������豸
    ret = USB_ScanDevice(DevHandles);
    if(ret <= 0){
        printf("No device connected!\n");
        return 0;
    }
    //���豸
    state = USB_OpenDevice(DevHandles[0]);
    if(!state){
        printf("Open device error!\n");
        return 0;
    }
    char FunctionStr[512]={0};
    //��ȡ�̼���Ϣ
    state = DEV_GetDeviceInfo(DevHandles[0],&DevInfo,FunctionStr);
    if(!state){
        printf("Get device infomation error!\n");
        return 0;
    }else{
	    printf("Firmware Name:%s\n",DevInfo.FirmwareName);
        printf("Firmware Build Date:%s\n",DevInfo.BuildDate);
        printf("Firmware Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("Hardware Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
	    printf("Firmware Functions:%s\n",FunctionStr);
        printf("Firmware Serial Number:%08X%08X%08X\n",DevInfo.SerialNumber[0],DevInfo.SerialNumber[1],DevInfo.SerialNumber[2]);
    }
	//��ʼ��SPI����ͨ��
    SPIConfig.Mode = SPI_MODE_HARD_HDX;
    SPIConfig.ClockSpeedHz = 25000000;
    SPIConfig.CPHA = 1;
    SPIConfig.CPOL = 1;
    SPIConfig.LSBFirst = SPI_MSB;
    SPIConfig.Master = SPI_MASTER;
    SPIConfig.SelPolarity = SPI_SEL_LOW;
    ret = SPI_Init(DevHandles[0],SPIMasterIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Initialize device error!\n");
        return 0;
    }
	//��ʼ��SPI�ӻ�ͨ��
	SPIConfig.Master = SPI_SLAVE;
	ret = SPI_Init(DevHandles[0],SPISlaveIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Initialize device error!\n");
        return 0;
    }
	//�����ӻ�������������,�ص���������ΪNULL��ͨ������SPI_SlaveGetBytes��������ȡ�������е�����
	ret = SPI_SlaveContinueRead(DevHandles[0],SPISlaveIndex,NULL);
    if(ret != SPI_SUCCESS){
        printf("Start continue read error!\n");
        return 0;
    }
	//�����������ݣ��ӻ��������ݲ���
	for(int TestNum = 0;TestNum<10;TestNum++){
		//������������
		for(int i=0;i<sizeof(WriteBuffer);i++){
			WriteBuffer[i] = rand();
		}
		ret = SPI_WriteBytes(DevHandles[0],SPIMasterIndex,WriteBuffer,sizeof(WriteBuffer));
		if(ret != SPI_SUCCESS){
			printf("Master write data error!\n");
			return 0;
		}
		//��ȡ�ӻ����ݽ��ջ������е�����
		ret = SPI_SlaveGetBytes(DevHandles[0],SPISlaveIndex,ReadBuffer,100);
		if(ret != sizeof(WriteBuffer)){
			printf("Master send data num not equal to slave read data num\n");
		}else{
			int ErrorDataNum = 0;
			for(int i=0;i<sizeof(WriteBuffer);i++){
				if(WriteBuffer[i] != ReadBuffer[i]){
					ErrorDataNum++;
				}
			}
			printf("Error data num[%d] = %d\n",TestNum,ErrorDataNum);
		}
	}
	//ֹͣ�ӻ�����������ģʽ
	ret = SPI_SlaveContinueWriteReadStop(DevHandles[0],SPISlaveIndex);
    if(ret != SPI_SUCCESS){
        printf("Slave stop continue read data error!\n");
        return 0;
    }
	//�ӻ��������ݣ�������ȡ���ݲ���
	for(int TestNum = 0;TestNum<10;TestNum++){
		//�ӻ�����ģʽд����
		for(int i=0;i<sizeof(WriteBuffer);i++){
			WriteBuffer[i] = rand();
		}
		//����ڶ��ε��øú�������ʵ���޸Ļ������е����ݣ�������һ�ζ�ȡ���ݣ��ӻ����صĵ�0�͵�1�ֽڿ��ܻ����������һ�ε����ݣ���������һ�ζ���ͻ�ָ�����
		ret = SPI_SlaveContinueWrite(DevHandles[0],SPISlaveIndex,WriteBuffer,sizeof(WriteBuffer));
		if(ret != SPI_SUCCESS){
			printf("Slave continue write data error!\n");
			return 0;
		}
		//������һ�ζ�ȡ���ݣ���һ�ζ�ȡ���ݴӻ����صĵ�0����1�ֽ����ݿ��ܻ��Ǵ�ģ�������һ�λ������е����ݣ�
		ret = SPI_ReadBytes(DevHandles[0],SPIMasterIndex,ReadBuffer,sizeof(WriteBuffer));
		if(ret != SPI_SUCCESS){
			printf("Master read data error\n");
		}else{
			int ErrorDataNum = 0;
			for(int i=0;i<sizeof(WriteBuffer);i++){
				if(WriteBuffer[i] != ReadBuffer[i]){
					ErrorDataNum++;
				}
			}
			printf("Error data num[%d][0] = %d\n",TestNum,ErrorDataNum);
		}
		//�����ڶ��ζ�ȡ���ݣ����ص��ǻ������е����ݣ��������������������ε��ö��������
		ret = SPI_ReadBytes(DevHandles[0],SPIMasterIndex,ReadBuffer,sizeof(WriteBuffer));
		if(ret != SPI_SUCCESS){
			printf("Master read data error\n");
		}else{
			int ErrorDataNum = 0;
			for(int i=0;i<sizeof(WriteBuffer);i++){
				if(WriteBuffer[i] != ReadBuffer[i]){
					ErrorDataNum++;
				}
			}
			printf("Error data num[%d][1] = %d\n",TestNum,ErrorDataNum);
		}
	}
}
