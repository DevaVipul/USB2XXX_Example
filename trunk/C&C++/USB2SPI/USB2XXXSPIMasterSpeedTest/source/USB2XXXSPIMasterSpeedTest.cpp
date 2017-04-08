// USB2XXXSPIMasterSpeedTest.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "usb_device.h"
#include "usb2spi.h"


int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    SPI_CONFIG SPIConfig;
    int DevHandle[10];
    int SPIIndex = 0;
    const int PackSize = 20*1024;
    const int PackNum = 1000;
    bool state;
    int ret;
    unsigned char WriteBuffer[PackSize];
    unsigned char ReadBuffer[PackSize];
    //ɨ������豸
    ret = USB_ScanDevice(DevHandle);
    if(ret <= 0){
        printf("No device connected!\n");
        getchar();
        return 0;
    }
    //���豸
    state = USB_OpenDevice(DevHandle[0]);
    if(!state){
        printf("Open device error!\n");
        getchar();
        return 0;
    }
    //��ȡ�̼���Ϣ
    char FuncStr[256]={0};
    state = DEV_GetDeviceInfo(DevHandle[0],&DevInfo,FuncStr);
    if(!state){
        printf("Get device infomation error!\n");
        getchar();
        return 0;
    }else{
	    printf("Firmware Name:%s\n",DevInfo.FirmwareName);
        printf("Firmware Build Date:%s\n",DevInfo.BuildDate);
        printf("Firmware Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("Hardware Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
	    printf("Firmware Functions:%s\n",FuncStr);
    }

    //����SPI������ز���
    SPIConfig.Mode = 0;
    SPIConfig.ClockSpeedHz = 50000000;
    SPIConfig.CPHA = 0;
    SPIConfig.CPOL = 0;
    SPIConfig.LSBFirst = 0;
    SPIConfig.Master = 1;
    SPIConfig.SelPolarity = 0;
    ret = SPI_Init(DevHandle[0],SPIIndex,&SPIConfig);
    if(ret != SPI_SUCCESS){
        printf("Initialize device error!\n");
        getchar();
        return 0;
    }
    printf("��ʼ����...\n");
    printf("���䷽ʽ��������������\n");
    printf("����ģʽ��ͬ��ģʽ\n");
    printf("SPIʱ��Ƶ�ʣ�%d Hz\n",SPIConfig.ClockSpeedHz);
    //��ȡ��ʼʱ��,��Ҫ���ڲ��Է����ٶ�
    LARGE_INTEGER litmp;
    LONGLONG StartTime,EndTime;
    double dfFreq;
    QueryPerformanceFrequency(&litmp);// Get the performance counter frequency, in n/s
    dfFreq = (double)litmp.QuadPart;
    QueryPerformanceCounter(&litmp);  // Get the current value of the performance counter
    StartTime = litmp.QuadPart;       // Start time
    for(int i=0;i<PackNum;i++){
        ret = SPI_WriteBytes(DevHandle[0],SPIIndex,WriteBuffer,PackSize);
        if(ret != SPI_SUCCESS){
            printf("SPI write data error!\n");
            getchar();
            return 0;
        }
    }
	//��ȡ����ʱ�䲢��ӡ�����ʱ���ٶ�
    QueryPerformanceCounter(&litmp);// Get the current value of the performance counter
    EndTime = litmp.QuadPart; // Stop time
	// Print the write data speed information
	printf("-----------------------www.usbxyz.com-----------------------\n");
	printf("���������ֽ���: %.3f MBytes\n",PackSize*PackNum/(1024*1024.0));
	printf("������������ʱ��: %f s\n",(EndTime-StartTime)/dfFreq);
	printf("���������ٶ�: %.3f MByte/s\n",PackSize*PackNum/((EndTime-StartTime)/dfFreq)/(1024*1024));
	printf("-----------------------www.usbxyz.com-----------------------\n");

    printf("\n��ʼ����...\n");
    printf("���䷽ʽ��������������\n");
    printf("����ģʽ���첽ģʽ\n");
    printf("SPIʱ��Ƶ�ʣ�%d Hz\n",SPIConfig.ClockSpeedHz);
    QueryPerformanceFrequency(&litmp);// Get the performance counter frequency, in n/s
    dfFreq = (double)litmp.QuadPart;
    QueryPerformanceCounter(&litmp);  // Get the current value of the performance counter
    StartTime = litmp.QuadPart;       // Start time
    for(int i=0;i<PackNum;i++){
        ret = SPI_WriteBytesAsync(DevHandle[0],SPIIndex,WriteBuffer,PackSize);
        if(ret != SPI_SUCCESS){
            printf("SPI write data error!\n");
            getchar();
            return 0;
        }
    }
	//��ȡ����ʱ�䲢��ӡ�����ʱ���ٶ�
    QueryPerformanceCounter(&litmp);// Get the current value of the performance counter
    EndTime = litmp.QuadPart; // Stop time
	// Print the write data speed information
	printf("-----------------------www.usbxyz.com-----------------------\n");
	printf("���������ֽ���: %.3f MBytes\n",PackSize*PackNum/(1024*1024.0));
	printf("������������ʱ��: %f s\n",(EndTime-StartTime)/dfFreq);
	printf("���������ٶ�: %.3f MByte/s\n",PackSize*PackNum/((EndTime-StartTime)/dfFreq)/(1024*1024));
	printf("-----------------------www.usbxyz.com-----------------------\n");

    printf("\n��ʼ����...\n");
    printf("���䷽ʽ��������ȡ����\n");
    printf("����ģʽ��ͬ��ģʽ\n");
    printf("SPIʱ��Ƶ�ʣ�%d Hz\n",SPIConfig.ClockSpeedHz);
    QueryPerformanceFrequency(&litmp);// Get the performance counter frequency, in n/s
    dfFreq = (double)litmp.QuadPart;
    QueryPerformanceCounter(&litmp);  // Get the current value of the performance counter
    StartTime = litmp.QuadPart;       // Start time
    for(int i=0;i<PackNum;i++){
        ret = SPI_ReadBytes(DevHandle[0],SPIIndex,ReadBuffer,PackSize);
        if(ret != SPI_SUCCESS){
            printf("SPI read data error!\n");
            getchar();
            return 0;
        }
    }
	//��ȡ����ʱ�䲢��ӡ�����ʱ���ٶ�
    QueryPerformanceCounter(&litmp);// Get the current value of the performance counter
    EndTime = litmp.QuadPart; // Stop time
	// Print the write data speed information
	printf("-----------------------www.usbxyz.com-----------------------\n");
	printf("��ȡ�����ֽ���: %.3f MBytes\n",PackSize*PackNum/(1024*1024.0));
	printf("��ȡ��������ʱ��: %f s\n",(EndTime-StartTime)/dfFreq);
	printf("��ȡ�����ٶ�: %.3f MByte/s\n",PackSize*PackNum/((EndTime-StartTime)/dfFreq)/(1024*1024));
	printf("-----------------------www.usbxyz.com-----------------------\n");
    printf("�ٶȲ�����ϣ�\n");
    getchar();
	return 0;
}

