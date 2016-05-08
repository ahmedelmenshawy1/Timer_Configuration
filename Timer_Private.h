/*
 * Timer_Private.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ahmed
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#include "Timer_Config.h"

#define ISR(vector)  															\
	void vector(void)	__attribute__((signal,used,externally_visible));		\
	void vector(void)

void (*ptr_OverFlow)(void);

#define 	TCCR0_u8Address		(0x53)
#define 	TCNT0_u8Address		(0x52)
#define 	OCR0_u8Address		(0x5C)
#define 	TIMSK_u8Address		(0x59)
#define 	TIFR_u8Address		(0x58)



#define  TCCR0 	(*(volatile u8 *) TCCR0_u8Address	 )
#define  TCNT0 	(*(volatile u8 *) TCNT0_u8Address	 )
#define  OCR0_	(*(volatile u8 *) OCR0_u8Address	 )
#define  TIMSK	(*(volatile u8 *) TIMSK_u8Address	 )
#define  TIFR	(*(volatile u8 *) TIFR_u8Address	 )



/*
CS02 CS01 CS00 	Description
0 	  0 	0 	No clock source (Timer/Counter stopped).
0  	  0 	1 	clk/(No prescaling)
0 	  1 	0 	clk/8 (From prescaler)
0     1 	1 	clk/64 (From prescaler)
1 	  0 	0 	clk/256 (From prescaler)
1 	  0 	1   clk/1024 (From prescaler)
1 	  1 	0 	External clock source on T0 pin. Clock on falling edge.
1 	  1 	1 	External clock source on T0 pin. Clock on rising edge.
*/

#define CS02_2	2
#define CS01_1	1
#define CS00_0	0

#define TOIE0  0

#define Timer_u8EnableOverFlowInterrpt      	(1<<TOIE0)
#define Timer_u8DisableOverFlowInterrpt   		(0<<TOIE0)


#define 	Timer_u8NoClockSource				(0<<CS02_2 | 0<<CS01_1 | 0<<CS00_0)
#define 	Timer_u8NoPrescaler					(0<<CS02_2 | 0<<CS01_1 | 1<<CS00_0)
#define 	Timer_u8Factor8						(0<<CS02_2 | 1<<CS01_1 | 0<<CS00_0)
#define 	Timer_u8Factor64					(0<<CS02_2 | 1<<CS01_1 | 1<<CS00_0)
#define 	Timer_u8Factor256					(1<<CS02_2 | 0<<CS01_1 | 0<<CS00_0)
#define 	Timer_u8Factor1024					(1<<CS02_2 | 0<<CS01_1 | 1<<CS00_0)
#define 	Timer_u8ExternalClockFallingEdge	(1<<CS02_2 | 1<<CS01_1 | 0<<CS00_0)
#define 	Timer_u8ExternalClockRisingEdge		(1<<CS02_2 | 1<<CS01_1 | 1<<CS00_0)

#if Timer_u8Prescalir==Timer_u8NoPrescaler||Timer_u8Prescalir==Timer_u8ExternalClockFallingEdge||Timer_u8Prescalir==Timer_u8ExternalClockRisingEdge
#define Timer_u8PrescalierNumber	1.0
#elif	Timer_u8Prescalir==Timer_u8Factor8
#undef 	Timer_u8PrescalierNumber
#define Timer_u8PrescalierNumber	8.0
#elif	Timer_u8Prescalir==Timer_u8Factor64
#undef 	Timer_u8PrescalierNumber
#define Timer_u8PrescalierNumber	64.0
#elif	Timer_u8Prescalir==Timer_u8Factor256
#undef	Timer_u8PrescalierNumber
#define Timer_u8PrescalierNumber	256.0
#elif	Timer_u8Prescalir==Timer_u8Factor1024
#undef 	Timer_u8PrescalierNumber
#define Timer_u8PrescalierNumber	1024.0
#else
#error u must choose Prescaler
#endif

//cpu is constant
#define Timer_u64CPU	  4000000
//Timer is constant
#define Timer_u8Timein1mile 		.001
#define Timer_u8MaxTimerZeroTick 	256
#define Timer_u8MaxTimerTick 		255
#define Timer_u8OneTimerTick 		1
#define Timer_u8ConvertToMile 		1000

//#define		ggggg					(1/(Timer_u64CPU/Timer_u8PrescalierNumber))
//#define		Timer_u16TimerCounter	((Timer_u8RequiredTimeBySecond)/ggggg)-1
#define		Timer_u16TimerCounter			(((Timer_u64CPU*Timer_u8Timein1mile)/Timer_u8PrescalierNumber))

#define		Timer_f32TimeOverFlowTimer0		(((Timer_u8MaxTimerZeroTick*Timer_u8PrescalierNumber)/(Timer_u64CPU))*Timer_u8ConvertToMile)

#define		Timer_f32OneTickTimer0			(((Timer_u8OneTimerTick*Timer_u8PrescalierNumber)/(Timer_u64CPU))*Timer_u8ConvertToMile)

#define Timer_u8ReachRequiredOverFlowNumber  	1
#define Timer_u8NotYetReachToOverFlowNumber  	0
/*
 *
			 Timer_u64CPU*Timer_u8Timein1mile(Required)
TimerCount=______________________________________________
				(Timer_u8PrescalierNumber)

*/


/*
	to calculate what is the time of 1  ?

			 Timer_u64CPU*Timer_u8Timein1mile(Required)
	1	=_______________________________________________
				(Timer_u8PrescalierNumber)

*/
/*
example
50 ms--16 MHz --say 256 Prescaler
maximum delay of  4.096 ms in 8 bit timer
50ms(Required) ÷ 4.096 ms = 12.207
Thus, in simple terms, by the time the timer has overflown 12 times,12(times)*4.096= 49.152 ms would have passed. After that,
when the timer undergoes 13th iteration, it would achieve a delay of 50 ms. Thus, in the 13th iteration,
we need a delay of 50(Required) – 49.152 = 0.848 ms. At a frequency of 62.5 kHz (prescaler = 256), each tick takes 0.016 ms.
Thus to achieve a delay of 0.848 ms,it would require 0.848/.016(one tick)= 53 ticks. Thus,in the 13th iteration,
we only allow the timer to count up to 53, and then reset it. All this can be achieved in the ISR
*/



#endif /* TIMER_PRIVATE_H_ */
