#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Motor2.h"
#include "PWM.h"
#include "Serial.h"
#include "string.h"
#include <stdlib.h>
#include <ctype.h>

      /*转台PA2脉冲，PA3方向*/
	  /*传送带，PA6脉冲，PA5方向*/
	  /*脉冲：PA6转台，PA1传送带*/
	  //频率=72000000/（ARR*PSC），周期=1/频率，电机转一圈时间=1600*周期=PSC/450,ARR为100
	  
int main(void)
{
	/*模块初始化*/
	Motor2_Init();		//转台步进电机初始化；计数周期，即ARR的值100，改变预分频器，即PSC的值来改变速度
	PWM_TIM2_CH2_Init(100,288);//PSC=450*转速,初始速度
	
	Motor3_Init();      //传送带步进电机初始化
	PWM_TIM3_CH1_Init(100,2250);//PSC=450*转速，初始速度
	Serial_Init();		//串口初始化
	
	while (1)
	{
	if (Serial_RxFlag == 1)		//如果接收到数据包
	{
			/*将收到的数据包与预设的指令对比，以此决定将要执行的操作*/
		    
			if (strcmp(Serial_RxPacket, "ztz") == 0)			//如果收到ztz指令
			{
				Motor2_Start_U();										//转台正
				Serial_SendString("ztz_OK\r\n");				//串口回传一个字符串ztz_OK
			}
			if (strcmp(Serial_RxPacket, "ztf") == 0)	//如果收到ztf指令
			{
				Motor2_Start_D();										//转台反
				Serial_SendString("ztf_OK\r\n");			//串口回传一个字符串ztf_OK
			}
			if (strcmp(Serial_RxPacket, "ztt") == 0)	//如果收到ztt指令
			{
				Motor2_Stop();										//转台停
				Serial_SendString("ztt_OK\r\n");			//串口回传一个字符串ztf_OK
			}
			//调速
		    // Serial_SendNumber(20,2);
			
			
			
			//传送带
			if (strcmp(Serial_RxPacket, "csdz") == 0)			//如果收到csdz指令
			{
				Motor3_Start_U();										//传送带正
				Serial_SendString("csdz_OK\r\n");				//串口回传一个字符串csdz_OK

			}
			if (strcmp(Serial_RxPacket, "csdf") == 0)	//如果收到csdf指令
			{
				Motor3_Start_D();										//传送带反
				Serial_SendString("csdf_OK\r\n");			//串口回传一个字符串csdf_OK
			}
			if (strcmp(Serial_RxPacket, "csdt") == 0)	//如果收到csdt指令
			{
				Motor3_Stop();										//传送带停
				Serial_SendString("csdt_OK\r\n");			//串口回传一个字符串csdt_OK
			}
			
			//转台调速
			if (strncmp(Serial_RxPacket, "zt", 2) == 0 && isdigit((unsigned char)Serial_RxPacket[2]))
            {
                int speed = atoi(&Serial_RxPacket[2]); // 获取数字
                if (speed > 99) speed = 99;
                uint16_t psc = (-6*(speed+1))+904;
                Motor2_SetSpeed(psc);
                Serial_SendString("zt_speed_OK\r\n");
			}
			//传送带调速
			if (strncmp(Serial_RxPacket, "csd", 3) == 0 && isdigit((unsigned char)Serial_RxPacket[3]))
            {
                int speed = atoi(&Serial_RxPacket[3]);
                if (speed > 99) speed = 99;
                uint16_t psc = (-13.5*(speed+1)+2250);
                Motor3_SetSpeed(psc);
                Serial_SendString("csd_speed_OK\r\n");
            }
	         
			
			Serial_RxFlag = 0;			//处理完成后，需要将接收数据包标志位清零，否则将无法接收后续数据包
		}
	}
}
	

