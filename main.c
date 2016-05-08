/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ahmed
 */

#include "Types.h"
#include "DIO_interface.h"
#include "Timer_Interface.h"
#include "RTOS_Interface.h"
#include "DIO_Private.h"
#include "Timer_Private.h"
#include "delay.h"

extern void RTOS_TurnOnTask(void);
extern void RTOS_TurnOffTask(void);

#define RTOS_u8PeriodictyChooseT1	2
#define RTOS_u8FisrtDelayChooseT1	0
#define RTOS_u8PeriodictyChooseT2	2
#define RTOS_u8FisrtDelayChooseT2	1
void Toggle(void);
volatile u16 Counter=0;

int main (void)
{
	DIO_VoidInit();

	//RTOS_voidCreateTask(RTOS_TurnOnTask,RTOS_u8PeriodictyChooseT1,RTOS_u8FisrtDelayChooseT1+1);
	//RTOS_voidCreateTask(RTOS_TurnOffTask,RTOS_u8PeriodictyChooseT2,RTOS_u8FisrtDelayChooseT2+1);

	Timer_VoidInit();
	//RTOS_VoidInit();
	PORTA=0x00;
	Timer_voidOverFlowInt0(Toggle);
	Timer_u8TakeTime(1);

	ExtInt_EnableGlobalInt();

	while(1)
	{

//		if(Counter>=1)
//		{
//				if(TCNT0>=240)
//				{
//				PORTA=!PORTA;
//				Counter=0;
//				TCNT0=0;
//				}
//		}
//				if(Counter>=9)
//				{
//						if(TCNT0>=196)
//						{
//						PORTA=!PORTA;
//						Counter=0;
//						TCNT0=0;
//						}
//				}

		if(Timer_u8NumberOfOverFlowInMileSec(Counter) ==1 )
		{
			PORTA = !PORTA;
			Counter=0;
		}
	}
	return 0;
}

/********************************/
extern void RTOS_TurnOnTask(void)
{
	//DIO_u8WritePinVal(1,1);
	PORTA=0X01;
}
/********************************/
extern void RTOS_TurnOffTask(void)
{
	//DIO_u8WritePinVal(1,0);
	PORTA=0X00;
}
/********************************/
void Toggle(void)
{
//	PORTC=++Counter;
	Counter++;
//	if (Timer_u16NumberOfOverFlowInMileSec(5) == 1)	//245us
//			{
//				PORTA = !PORTA;
//			}
}
