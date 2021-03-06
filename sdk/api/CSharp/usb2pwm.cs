﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace USB2XXX
{
    class USB2PWM
    {
        //定义函数返回错误代码
        public const Int32 PWM_SUCCESS = (0);   //函数执行成功
        public const Int32 PWM_ERR_NOT_SUPPORT = (-1);  //适配器不支持该函数
        public const Int32 PWM_ERR_USB_WRITE_FAIL = (-2);  //USB写数据失败
        public const Int32 PWM_ERR_USB_READ_FAIL = (-3);  //USB读数据失败
        public const Int32 PWM_ERR_CMD_FAIL = (-4);  //命令执行失败
        //定义初始化PWM的数据类型
        public struct PWM_CONFIG
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public UInt16[] Prescaler;  //预分频器
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public UInt16[] Precision;  //占空比调节精度
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public UInt16[] Pulse;      //占空比，实际占空比=(Pulse/Precision)*100%
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public Byte[] Polarity;    //波形极性
            public Byte ChannelMask;    //通道号
        }
        //函数定义
        [DllImport("USB2XXX.dll")]
        public static extern Int32 PWM_Init(Int32 DevHandle, ref PWM_CONFIG pConfig);
        [DllImport("USB2XXX.dll")]
        public static extern Int32 PWM_Start(Int32 DevHandle,Byte ChannelMask,Int32 RunTimeUs);
        [DllImport("USB2XXX.dll")]
        public static extern Int32 PWM_SetPulse(Int32 DevHandle,Byte ChannelMask,UInt16[] pPulse);
        [DllImport("USB2XXX.dll")]
        public static extern Int32 PWM_SetFrequency(Int32 DevHandle,Byte ChannelMask,UInt16[] pPrescaler,UInt16[] pPrecision);
        [DllImport("USB2XXX.dll")]
        public static extern Int32 PWM_Stop(Int32 DevHandle,Byte ChannelMask);
    }
}
