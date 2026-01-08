#ifndef __MOTOR2_H__
#define __MOTOR2_H__

void Motor2_Init(void);
void Motor2_Start_U(void);
void Motor2_Start_D(void);
void Motor2_Stop(void);

void Motor3_Init(void);
void Motor3_Start_U(void);
void Motor3_Start_D(void);
void Motor3_Stop(void);

void Motor2_SetSpeed(uint16_t psc);
void Motor3_SetSpeed(uint16_t psc);

#endif
