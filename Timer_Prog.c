/*
 * Timer_Prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ahmed
 */

#include "delay.h"
#include "Timer_Private.h"
#include "Timer_Interface.h"
#include "DIO_Private.h"

static u8 Local_u8TCNT0Value = 0;
static u16 Local_u16NumberOfOverFlow =0;
static u16 Local_u16TotalTime=0;
const static f32 Timer_u16TimerCounterVar=Timer_u16TimerCounter;
const static f32 Timer_f32TimeOverFlowTimer0Var=Timer_f32TimeOverFlowTimer0,Timer_f32OneTickTimer0Var=Timer_f32OneTickTimer0;

///***************************************/
extern void Timer_VoidInit(void)
{
	TCCR0|=Timer_u8Prescalir;
	// initialize counter
	TCNT0 = 0;
	TIMSK|=Timer_u8Interrupt;
}

/***************************************/
//OverFlow EXT0
ISR(__vector_11)
{
	ptr_OverFlow();
}
/***************************************/
/*
 * if u want to calculate overflow time u will firstly put your prescaler
 * then calculate max time that will use then devide maximum time over
 * time u want then multiply 1000
 * 50 ms--16 MHz --say 256 Prescaler
 	 maximum delay of  4.096 ms in 8 bit timer
50ms(Required) ÷ 4.096 ms = 12.207
 *
 * */
/*
 * overflow(1024)=65.636ms
 * oneTick(1024)=.256ms
 * */
extern void Timer_voidOverFlowInt0(void (*Local_ptr)(void))
{
	ptr_OverFlow=Local_ptr;
}
/***************************************/

extern u16 Timer_u16Count1mile(void)
{//here will calulate time off what is the time that take by calulate number of
	//Local_u16TotalTime and know how much time it take?
	u16 Local_u16ValueThatReturn=0;
	if(TCNT0 >= (u8)Timer_u16TimerCounterVar+1)//Timer_u16TimerCounter)//1 mile
	{//(u8)(Timer_u16TimerCounter)+1 3mlt u8 +1 3shan hwa ksr w ana msh hinf3 a2arn bksr
		//+1 3shan ygeb elrkm elkber 3la tol y3ny 14.25 lw u8 bs hia5d 14 l2 zwd b2a 3shan tb2a 15
		Local_u16TotalTime++;
		Local_u16ValueThatReturn=Local_u16TotalTime;
		TCNT0=0;
	}
	else;
	return Local_u16ValueThatReturn;
//when prescaler= 8
//	if (tot_overflow >= 1960)  // 500 mile
//			{
//				if (TCNT0 >= 200)
//				{
//					PORTA^=0xff;
//					Timer_u16ResetTotalTime();
//					Timer_u16ResetCounter();
//					tot_overflow=0;
//				}
//			}
}
/***************************************/

extern void Timer_u16ResetTotalTime(void)
{
	Local_u16TotalTime=0;
}
/***************************************/

extern void Timer_u16ResetCounter(void)
{
	TCNT0=0;
}
/***************************************/

extern u8 Timer_u16GetTCNT0(void)
{
	return TCNT0;
}

/***************************************/
extern void ExtInt_EnableGlobalInt(void)
{
	__asm__ __volatile__("sei");
}
/***************************************/
extern void ExtInt_DisableGlobalInt(void)
{
	__asm__ __volatile__("cli");
}
/***************************************/
/*
example
50 ms--16 MHz --say 256 Prescaler
maximum delay of  4.096 ms in 8 bit timer
50ms(Required) ÷ 4.096 ms = 12.207
Thus, in simple terms, by the time the timer has overflown 12 times,12*4.096= 49.152 ms would have passed. After that,
when the timer undergoes 13th iteration, it would achieve a delay of 50 ms. Thus, in the 13th iteration,
we need a delay of 50 – 49.152 = 0.848 ms. At a frequency of 62.5 kHz (prescaler = 256), each tick takes 0.016 ms.
Thus to achieve a delay of 0.848 ms,it would require 0.848/.016= 53 ticks. Thus,in the 13th iteration,
we only allow the timer to count up to 53, and then reset it. All this can be achieved in the ISR
*/
/**************4MHZ**************/
/*overflow(8)=.512ms*/
/*OneTick(8)=.002 ms*/
/*overflow(64)=4.096 ms*/
/*OneTick(64)=.016 ms*/
/*overflow(256)=16.512 ms*/
/*OneTick(256)=.064 ms*/
/*overflow(1024)=65.536ms*/
/*OneTick(1024)=.256ms*/

//extern u8 Timer_Getu8TCNT0Value(void)
//{
//	return Local_u8TCNT0Value;
//}
//extern void Timer_Setu8TCNT0Value(u8 Copy_u8TCNT0Value)
//{
//	 Local_u8TCNT0Value=Copy_u8TCNT0Value;
//}
//extern u16 Timer_Getu16NumberOfOverFlow(void)
//{
//	return Local_u16NumberOfOverFlow;
//}
//extern void Timer_Setu16NumberOfOverFlow(u16 Copy_u16NumberOfOverFlow)
//{
//	Local_u16NumberOfOverFlow=Copy_u16NumberOfOverFlow;
//}



extern void Timer_u8TakeTime(const u16 Copy_u16RequiredTimeMileSec)
{

	if(Local_u16NumberOfOverFlow == 0)
	{
				/*Comment: calculate number of overflow*/
				Local_u16NumberOfOverFlow = (Copy_u16RequiredTimeMileSec / Timer_f32TimeOverFlowTimer0Var);//9.7		//500/65.536=7.629time

				Local_u8TCNT0Value = ((Copy_u16RequiredTimeMileSec- (Local_u16NumberOfOverFlow * (long int) Timer_f32TimeOverFlowTimer0Var))/ Timer_f32OneTickTimer0Var);	//850us

//				PORTD=Local_u8TCNT0Value;
//				Local_u8TCNT0Value=((Timer_u8MaxTimerTick)-(Local_u8TCNT0Value));
	}
	else;
}

extern u8 Timer_u8NumberOfOverFlowInMileSec(u16  Counter)
{
	u8 Local_u8Status;

	/*Comment: if Overflow counter reached exactly number*/
	if (Counter >= Local_u16NumberOfOverFlow)
	{
		if (TCNT0 >= Local_u8TCNT0Value)
		{
			/*Comment:intialzie counter*/
			TCNT0=0;
			/*Comment: reutrn one that counter == number of over flow  */
			Local_u8Status = Timer_u8ReachRequiredOverFlowNumber;
		}
		else;
	}
	else
	{
		Local_u8Status = Timer_u8NotYetReachToOverFlowNumber;
	}
	return Local_u8Status;
}



//extern u8 Timer_u8NumberOfOverFlowInMileSec(const u16 Copy_u16RequiredTimeMileSec,u8  Copy_u16CheckIfComplete)
//{
//	u8 Local_u8Status;
//	static u8 Local_u8TCNT0Value = 0;
//	//static u16 Local_u16CounterOverFlow = 0;
//	//static u16 Local_u16NumberOfOverFlow = 0;
//	Local_u8Status=Timer_u8NotYetReachToOverFlowNumber;
//
//	if(Copy_u16CheckIfComplete==1)
//	{
////	f32 Local_f32WithOutFloatNumber, Local_f32SubtractNumber;
//
////	if (Local_u16CounterOverFlow == 0)		//first time only will enter
//	{
//		/*Comment: calculate number of overflow*/
//		//Local_u16NumberOfOverFlow = (Copy_f32PtrRequiredTimeMileSec/ Timer_f32TimeOverFlowTimer0Var);//9.7		//500/65.536=7.629time
//
//		/*Comment: calculate Number of time in mile without float number   */
////		Local_f32WithOutFloatNumber = (u16)( (Local_u16NumberOfOverFlow))* Timer_f32TimeOverFlowTimer0Var;		//7*65.536=458.752ms
////		/*Comment: calculate number Remain Ticks by subtract*/
////		Local_f32SubtractNumber = Copy_f32PtrRequiredTimeMileSec- Local_f32WithOutFloatNumber;		//500-458.752=41.248
////		/*Comment: calculate Value Of TCNT0*/
////		Local_u8TCNT0Value =  (Local_f32SubtractNumber/ Timer_f32OneTickTimer0Var);		//41.248/.256
//
//		Local_u8TCNT0Value=( (Copy_u16RequiredTimeMileSec-( Local_u16NumberOfOverFlow * ( long int) Timer_f32TimeOverFlowTimer0Var ) )/ Timer_f32OneTickTimer0Var );
//
//		PORTD=Local_u8TCNT0Value;
//	}
////	else;
//	/*Comment: Increment Overflow counter*/
//	//Local_u16CounterOverFlow++;
//	/*Comment: if Overflow counter reached exactly number*/
////	if(Local_u16CounterOverFlow >=  (Local_u16NumberOfOverFlow) )//7
//	{
//		if(Local_u8TCNT0Value==0)/*dh hi5sh fy shrt ely 2ablo w b3dha msh hi5sh hna
//		hilainy 7tit 2imh ll TCNT0 3shan y3ml overflow w ygy hna tany w y2om 2ail ok ana wslt ll2imh overflow */
//		{
////			u8 i;/*to make it accurate on osclliscope for take 7 cycle */
////			for(i=0;i<1;i++){__asm__("NOP");}
//			Local_u8Status=Timer_u8ReachRequiredOverFlowNumber;
////			Local_u16CounterOverFlow=0;
//			//TCNT0=0;
//		}
//		else;
//		TCNT0=((Timer_u8MaxTimerTick)-(Local_u8TCNT0Value));
//
//		Local_u8TCNT0Value=0;
//	}
////	else
////	{
////		Local_u8Status=Timer_u8NotYetReachToOverFlowNumber;
////	}
//	}
//	return Local_u8Status;
//}
//
//
