/*
 * RTOS_Prog.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ahmed
 */
#include "delay.h"
#include "RTOS_Config.h"
#include "RTOS_Private.h"
#include "Timer_Interface.h"
#include "RTOS_Interface.h"
/********************************/
volatile static u8 RTOS_u8TasksNumber=0;
/****************************************************/
extern void RTOS_VoidInit(void)
{
	/*Comment!: Set Call Back OverFlow Timer0  */
	Timer_voidOverFlowInt0(RTOS_VoidISRTimer);
	/*Comment!: Set Propertiese Of Timer Module  */
	Timer_VoidInit();
	/*Comment!: EnableGlobal Interrupt  */
	ExtInt_EnableGlobalInt();
	/*Comment!: Call Schedual  */
	RTOS_VoidSchedular();

	return;
}
/****************************************************/
extern u8 RTOS_voidCreateTask(void (*Copy_voidTaskPtr)(void), u8 Copy_u8Periodicity,u8 Copy_u8FirstDelay)
{
	u8 Local_u8Status;
	/*comment:Here must be < */
	if(RTOS_u8TasksNumber < RTOS_u8NumberOfTask)
	{
		/*Comment!: add  Function that Ptr Ponit to  */
		TCB[RTOS_u8TasksNumber].RTOS_VoidPtr = Copy_voidTaskPtr;
		/*Comment!: add  Function Perodicity  */
		TCB[RTOS_u8TasksNumber].RTOS_u8Periodicity = Copy_u8Periodicity;
		/*Comment!: add  First Delay(Intialization) that fucntion will start in Milesec */
		TCB[RTOS_u8TasksNumber].RTOS_u8NumberOfTicks = Copy_u8FirstDelay;

		/*Comment!: Increment  Function Number  */
		RTOS_u8TasksNumber++;
		/*Comment!: No error  */
		Local_u8Status=Ok;
	}
	else
	{
		/*Comment!: error  */
		Local_u8Status=Error;
	}
	return Local_u8Status;
}
/****************************************************/
extern u8 RTOS_VoidSchedular(void )
{
	u8 Local_u8Status=0;
	/*comment:Here must be <= */
	if( RTOS_u8TasksNumber <= RTOS_u8NumberOfTask)
		{
			u8 Local_u8Counter;
			/*Comment!: check all Task Ticks ==1
			 * if tick of any task ==1 call it is function
			 * Number of ticks +1 at first it is mean when tick's task ==1
			 * u will call it
			 *  */
			for(Local_u8Counter=0;Local_u8Counter < RTOS_u8NumberOfTask;Local_u8Counter++)
			{
				if(TCB[Local_u8Counter].RTOS_u8NumberOfTicks==1)
				{
					(TCB[Local_u8Counter].RTOS_VoidPtr)();
				}
				else;
			}
			Local_u8Status = Ok;
		}
		else {
			/*Comment!: error  */
			Local_u8Status = Error;
		}
		return Local_u8Status;
}
/****************************************************/
extern void RTOS_VoidISRTimer(void )
{
//	u8 Local_u8Status;
	/*comment:Here must be <= */
	if(RTOS_u8TasksNumber <= RTOS_u8NumberOfTask)
	{
		u8 Local_u8Counter;
		/*Comment!: check all Task Ticks ==0
		 * if tick of any task ==0 Relead ticks with periodicty to wait to be 1 to call it again
		 *  */
//		if(Timer_u8NumberOfOverFlowInMileSec(RTOS_u8TickTimeMileSec)==RTOS_u8ReachRequiredOverFlowNumber)
		{
			for(Local_u8Counter=0;Local_u8Counter < RTOS_u8NumberOfTask;Local_u8Counter++)
			{
				TCB[Local_u8Counter].RTOS_u8NumberOfTicks--;
				if(TCB[Local_u8Counter].RTOS_u8NumberOfTicks==0)
				{
					TCB[Local_u8Counter].RTOS_u8NumberOfTicks=TCB[Local_u8Counter].RTOS_u8Periodicity;
				}
				else;
			}
			RTOS_VoidSchedular();
		}
//		else;

	}
	else;
	return;
//	else
//	{
//		/*Comment!: error  */
//		Local_u8Status = Error;
//	}
//	return Local_u8Status;
}
