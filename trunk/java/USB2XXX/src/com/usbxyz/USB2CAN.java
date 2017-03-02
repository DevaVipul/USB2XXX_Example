package com.usbxyz;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

public interface USB2CAN extends Library {
	USB2CAN INSTANCE  = (USB2CAN)Native.loadLibrary("USB2XXX",USB2CAN.class); 
	
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
