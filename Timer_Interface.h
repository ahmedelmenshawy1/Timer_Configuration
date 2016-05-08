/*
 * Timer_Interace.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ahmed
 */
#ifndef TIMER_INTERFAC_H_
#define TIMER_INTERFAC_H_


extern void Timer_VoidInit(void);
extern void Timer_voidOverFlowInt0(void (*Local_ptr)(void));
extern u16 Timer_u16Count1mile(void);
extern void Timer_u16ResetTotalTime(void);
extern void Timer_u16ResetCounter(void);
extern void ExtInt_EnableGlobalInt(void);
extern void ExtInt_DisableGlobalInt(void);
extern u8 Timer_u16GetTCNT0(void);
extern void Timer_u8TakeTime(const u16 Copy_u16RequiredTimeMileSec);
extern u8 Timer_u8NumberOfOverFlowInMileSec(u16  Counter);

#endif /* TIMER_INTERFAC_H_ */


