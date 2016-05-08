/*
 * RTOS_Private.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ahmed
 */

#ifndef RTOS_PRIVATE_H_
#define RTOS_PRIVATE_H_


/*Comment!:  counter = (Task Period) / (Tick Time)  */
	struct RTOS
	{
	  void (*RTOS_VoidPtr)(void);
	  volatile u8 RTOS_u8NumberOfTicks;
	  volatile u8 RTOS_u8Periodicity;
	}TCB[RTOS_u8NumberOfTask];

//	void (*PtrToTaskOnTask)(void);
//	void (*PtrToTaskOffTask)(void);
#define RTOS_u8ReachRequiredOverFlowNumber  	1

#endif /* RTOS_PRIVATE_H_ */
