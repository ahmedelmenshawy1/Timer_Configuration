/*
 * Timer_Config.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ahmed
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*Comment Choose your Prescaler*/
/*Range: Timer_u8ADPSPrescalerBits : Timer_u8Factor(2-4-8-16-32-64-128)*/
//Timer_u8(NoClockSource-NoPrescaler-Factor8-Factor64-Factor256-Factor1024-ExternalClockFallingEdge-ExternalClockRisingEdge)
#define Timer_u8Prescalir   Timer_u8Factor8
/**************4MHZ**************/
/*overflow(1024)=65.536ms*/
/*overflow(256)=16.384ms*/
/*overflow(8)=.512ms*/
/*overflow(8)=.002 ms*/
/*overflow(64)=4.096 ms*/
/*OneTick(64)=.016 ms*/
/*overflow(256)=16.512 ms*/
/*OneTick(256)=.064 ms*/
/**************************************/
/*Comment :Choose enable or disable Interrupt */
/*Range: Timer_u8EnableOverFlowInterrpt or Timer_u8DisableOverFlowInterrpt */
#define Timer_u8Interrupt	Timer_u8EnableOverFlowInterrpt

#endif /*TIMER_CONFIG_H_*/
