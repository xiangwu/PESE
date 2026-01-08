#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
#include <stdlib.h>
#include "Serial.h"
#include <ctype.h>


//PA2脉冲，PA3方向，转台
void Motor2_Init(void)
{   	
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	

    GPIO_InitTypeDef GPIO_InitStructure;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			
    GPIO_Init(GPIOA,&GPIO_InitStructure);
 
    GPIO_SetBits(GPIOA,GPIO_Pin_3);
    PWM_TIM2_CH2_Init(100,288);		
}

//PA6脉冲，PA5方向，传送带
void Motor3_Init(void)
{   	
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	

    GPIO_InitTypeDef GPIO_InitStructure;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			
    GPIO_Init(GPIOA,&GPIO_InitStructure);
 
    GPIO_SetBits(GPIOA,GPIO_Pin_5);
    PWM_TIM3_CH1_Init(100,288);
}
 
//转台
void Motor2_Start_U(void)
{
	    TIM_Cmd(TIM2, ENABLE);
	    GPIO_SetBits(GPIOA, GPIO_Pin_3);
        PWM_SetCompare3(50);	
}

void Motor2_Start_D(void)
{
	    TIM_Cmd(TIM2, ENABLE);
	    GPIO_ResetBits(GPIOA, GPIO_Pin_3);
        PWM_SetCompare3(50);
}

void Motor2_Stop(void)
{
	//PWM_SetCompare3(0);
	TIM_Cmd(TIM2, DISABLE);
}

//传从带
void Motor3_Start_U(void)
{
	    TIM_Cmd(TIM3, ENABLE);
	    GPIO_SetBits(GPIOA, GPIO_Pin_5);
        PWM_SetCompare1(50);	
}

void Motor3_Start_D(void)
{
	    TIM_Cmd(TIM3, ENABLE);
	    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        PWM_SetCompare1(50);
}

void Motor3_Stop(void)
{
	//PWM_SetCompare1(0);
	TIM_Cmd(TIM3, DISABLE);
}

////转台
//void Serial_SpeedControl(void)
//{
//    if (isdigit(Serial_RxPacket[0]))
//    {
//        int speed = atoi(Serial_RxPacket);
//        if (speed >= 0 && speed <= 99)
//        {
//            uint16_t newPSC = (-6*(speed+1))+904;
//            TIM_PrescalerConfig(TIM2, newPSC, TIM_PSCReloadMode_Update);

//            char reply[30];
//            sprintf(reply, "Speed:%d_OK\r\n", speed);
//            Serial_SendString(reply);
//        }
//        else
//        {
//            Serial_SendString("ERR:Range(0-99)\r\n");
//        }
//    }
//}

////传送带
//void Serial_SpeedControl2(void)
//{
//    if (isdigit(Serial_RxPacket[0]))
//    {
//        int speed = atoi(Serial_RxPacket);
//        if (speed >= 0 && speed <= 99)
//        {
//            uint16_t newPSC = (speed == 0) ? 65535 : 45000 / speed;
//            TIM_PrescalerConfig(TIM3, newPSC, TIM_PSCReloadMode_Update);

//            char reply[30];
//            sprintf(reply, "Speed:%d_OK\r\n", speed);
//            Serial_SendString(reply);
//        }
//        else
//        {
//            Serial_SendString("ERR:Range(0-99)\r\n");
//        }
//    }
//}

void Motor2_SetSpeed(uint16_t psc)
{
    TIM_PrescalerConfig(TIM2, psc, TIM_PSCReloadMode_Update);
}

void Motor3_SetSpeed(uint16_t psc)
{
    TIM_PrescalerConfig(TIM3, psc, TIM_PSCReloadMode_Update);
}

