import com.usbxyz.USB2XXX;

public class USB2XXXSPIW25Q32 {
	  /** 
     * Launch the application. 
     */  
    public static void main(String[] args) {   
        int ret;
        int DevIndex = 0;
        boolean state;
        int IICIndex = 0;
        byte[] WriteDataBuffer = new byte[1024];
        byte[] ReadDataBuffer = new byte[1024];
        //ɨ���豸
        ret = USB2XXX.INSTANCE.USB_ScanDevice(null);
        if(ret > 0){
        	System.out.println("Device Num = "+ret);
        }else{
        	System.out.println("No device");
        	return;
        }
        //���豸
        state = USB2XXX.INSTANCE.USB_OpenDevice(DevIndex);
        if(!state){
        	System.out.println("open device error");
        	return;
        }
        //��ȡ�豸��Ϣ
        USB2XXX.DEVICE_INFO DevInfo = new USB2XXX.DEVICE_INFO();
        byte[] funcStr = new byte[128];
        state = USB2XXX.INSTANCE.USB_GetDeviceInfo(DevIndex,DevInfo,funcStr);
        if(!state){
        	System.out.println("get device infomation error");
        	return;
        }else{
            try {
            	System.out.println("Firmware Info:");
            	System.out.println("--Name:" + new String(DevInfo.FirmwareName, "UTF-8"));
            	System.out.println("--Build Date:" + new String(DevInfo.BuildDate, "UTF-8"));
            	System.out.println(String.format("--Firmware Version:v%d.%d.%d", (DevInfo.FirmwareVersion >> 24) & 0xFF, (DevInfo.FirmwareVersion >> 16) & 0xFF, DevInfo.FirmwareVersion & 0xFFFF));
            	System.out.println(String.format("--Hardware Version:v%d.%d.%d", (DevInfo.HardwareVersion >> 24) & 0xFF, (DevInfo.HardwareVersion >> 16) & 0xFF, DevInfo.HardwareVersion & 0xFFFF));
            	System.out.println("--Functions:" + new String(funcStr, "UTF-8"));
            } catch (Exception ep) {
                ep.printStackTrace();
            }
        }
    }
}
