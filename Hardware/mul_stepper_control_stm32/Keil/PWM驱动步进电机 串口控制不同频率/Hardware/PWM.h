#ifndef __PWM_H
#define __PWM_H

void PWM_TIM2_CH2_Init(uint16_t arr, uint16_t psc);
void PWM_TIM3_CH1_Init(uint16_t arr, uint16_t psc);
void PWM_SetCompare3(uint16_t Compare);

void PWM_SetCompare1(uint16_t Compare);
#endif
