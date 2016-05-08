/*
 * RTOS_Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ahmed
 */

#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_

extern void RTOS_VoidInit(void);
extern void RTOS_VoidISRTimer(void );
extern u8 RTOS_VoidSchedular(void );
extern u8 RTOS_voidCreateTask(void (*Copy_voidTaskPtr)(void), u8 Copy_u8Periodicity,u8 Copy_u8FirstDelay);



#endif /* RTOS_INTERFACE_H_ */
