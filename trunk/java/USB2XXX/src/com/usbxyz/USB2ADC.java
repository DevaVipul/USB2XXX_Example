package com.usbxyz;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface USB2ADC extends Library {
	USB2ADC INSTANCE  = (USB2ADC)Native.loadLibrary("USB2XXX",USB2ADC.class); 
	
    //���庯�����ش������
    public static int ADC_SUCCESS             = (0);   //����ִ�гɹ�
    public static int ADC_ERR_NOT_SUPPORT     = (-1);  //��������֧�ָú���
    public static int ADC_ERR_USB_WRITE_FAIL  = (-2);  //USBд����ʧ��
    public static int ADC_ERR_USB_READ_FAIL   = (-3);  //USB������ʧ��
    public static int ADC_ERR_CMD_FAIL        = (-4);  //����ִ��ʧ��
    public static int ADC_ERR_CH_NO_INIT      = (-5);  //��ͨ��δ��ʼ��
    //���������ɼ�����ģʽ�µĻص�����
    public interface ADC_GET_DATA_HANDLE {
        void ReceiveCallback(int DevHandle,short[] pData,int DataNum);
    }
    
    /**
     * @brief  ��ʼ������ADC
     * @param  DevHandle �豸���
     * @param  Channel ��Ҫ���õ�ADCͨ����ÿ��bitΪ��Ӧһ��ͨ����Ϊ1ʱ����Ҫ���ø�ͨ�������λ����ͨ��0
     * @param  SampleRateHz ADC�����ʣ���ͨ�����2.5MHz����λΪHz
     * @retval ����ִ��״̬��С��0����ִ�г���
     */
   int  ADC_Init(int DevHandle,char Channel,int SampleRateHz);
   /**
     * @brief  ����������ADCת��ֵ
     * @param  DevHandle �豸���
     * @param  pData ���ݴ洢�������׵�ַ
     * @param  DataNum ��ȡת������������ÿ������֮���ʱ����Ϊ��ʼ������ʱ��Ĳ���Ƶ�ʾ���
     * @retval ����ִ��״̬��С��0����ִ�г���
     */
   int  ADC_Read(int DevHandle,short[] pData,int DataNum);
   /**
     * @brief  ����ADC����ת��ģʽ
     * @param  DevHandle �豸���
     * @param  Channel ��Ҫ���õ�ADCͨ����ÿ��bitΪ��Ӧһ��ͨ����Ϊ1ʱ����Ҫ���ø�ͨ�������λ����ͨ��0
     * @param  SampleRateHz ADC�����ʣ���ͨ�����2.5MHz����λΪHz
     * @param  FrameSize ��������ʱÿ�δ������ݸ���SampleRateHz*1000/FrameSize��ô��ڻ��ߵ���20
     * @retval ����ִ��״̬��С��0����ִ�г���
     */
   int  ADC_StartContinueRead(int DevHandle,char Channel,int SampleRateHz,int FrameSize,ADC_GET_DATA_HANDLE pGetDataHandle);
   /**
     * @brief  ֹͣADC����ת��ģʽ
     * @param  DevHandle �豸���
     * @retval ����ִ��״̬��С��0����ִ�г���
     */
   int  ADC_StopContinueRead(int DevHandle);
   /**
     * @brief  ��ȡADC����ת��ģʽ�´洢�����ݻ������е�����ֵ
     * @param  DevHandle �豸���
     * @param  pDataBuffer ���ݴ洢�������׵�ַ
     * @param  BufferSize ���ݴ洢���������£�ע�ⵥλΪ�����ͣ������ֽڣ���������СΪ10240�������ȡ��������
     * @retval �ɹ���ȡ��������������λΪ�����ͣ�
     */
   int  ADC_GetData(int DevHandle,short[] pDataBuffer,int BufferSize);

}
