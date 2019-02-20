#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>
#include "Common.h"


typedef struct GeneralTimerRegs GeneralTimerRegs;//tim2 to tim5

struct GeneralTimerRegs{
	TimerRegister Cr1;				// 0x00	control register 1
	TimerRegister Cr2;				// 0x04	control register 2
	TimerRegister SlaveMode;		// 0x08	slave mode control register
	TimerRegister DMAInterruptEn;	// 0x0C	DMA/Interrupt enable register
	TimerRegister Status;			// 0x10	status register
	TimerRegister EventGeneration;	// 0x14	event generation register
	TimerRegister Ccmr1;			// 0x18	capture/compare mode register 1
	TimerRegister Ccmr2;			// 0x1C	capture/compare mode register 2
	TimerRegister Ccer;				// 0x20	capture/compare enable register
	TimerRegister Counter;			// 0x24	counter
	TimerRegister Prescaler;		// 0x28	prescaler
	TimerRegister Arr;				// 0x2C	auto-reload register
	TimerRegister Reserved0;		// 0x30	reserved
	TimerRegister Ccr1;				// 0x34	capture/compare register 1
	TimerRegister Ccr2;				// 0x38	capture/compare register 2
	TimerRegister Ccr3;				// 0x3C	capture/compare register 3
	TimerRegister Ccr4;				// 0x40	capture/compare register 4
	TimerRegister Dcr;				// 0x48	DMA control register
	TimerRegister Dmar;				// 0x4C	DMA address for full transfer
	TimerRegister Or;				// 0x50	option register
};


typedef enum
{
  TIM_STATE_RESET      ,       	//= 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  TIM_STATE_READY      ,       	//= 0x01U,    /*!< Peripheral Initialized and ready for use    */
  TIM_STATE_BUSY       ,      	//= 0x02U,    /*!< An internal process is ongoing              */
  TIM_STATE_TIMEOUT    ,       	//= 0x03U,    /*!< Timeout state                               */
  TIM_STATE_ERROR      ,       	//= 0x04U     /*!< Reception process is ongoing                */
}TIM_State_TypeDef;


typedef enum
{
  Ok       = 0x00U,
  Error    = 0x01U,
  Busy     = 0x02U,
  Timeout  = 0x03U
}Status_TypeDef;


typedef struct Timer_Handle_TypeDef Timer_Handle_TypeDef;

struct Timer_Handle_TypeDef{
	GeneralTimerRegs *instance;
	volatile TIM_State_TypeDef state;
};

Timer_Handle_TypeDef tim2;

/*----------timer address---------*/
#define timer1 ((GeneralTimerRegs *)0x40010000)
#define timer2 ((GeneralTimerRegs *)0x40000000)
#define timer3 ((GeneralTimerRegs *)0x40000400)
#define timer4 ((GeneralTimerRegs *)0x40000800)
#define timer5 ((GeneralTimerRegs *)0x40000C00)
#define timer6 ((GeneralTimerRegs *)0x40001000)
#define timer7 ((GeneralTimerRegs *)0x40001400)
#define timer8 ((GeneralTimerRegs *)0x40010400)
#define timer9 ((GeneralTimerRegs *)0x40014000)
#define timer10 ((GeneralTimerRegs *)0x40014400)
#define timer11 ((GeneralTimerRegs *)0x40014800)
#define timer12 ((GeneralTimerRegs *)0x40001800)
#define timer13 ((GeneralTimerRegs *)0x40001C00)
#define timer14 ((GeneralTimerRegs *)0x40002000)

/*----------channel---------*/
#define timerChannel_1                    	0x00000000
#define timerChannel_2                      0x00000004
#define timerChannel_3                      0x00000008
#define timerChannel_4                      0x0000000C
#define timerChannel_All                    0x00000018

/*-------channelState-------*/
#define timer_Ccx_ENABLE                   0x00000001U
#define timer_Ccx_DISABLE                  0x00000000U
#define timer_CcxN_ENABLE                  0x00000004U
#define timer_CcxN_DISABLE                 0x00000000U

#define timer_CEN		1

//ERG
#define timer_UG		1

//CCER
#define OC_NORMAL_POLARITY 	0
#define OC_INVRESE_POLARITY	1

//timer Macros
#define timer_SET_COUNTER(tim, value)			(tim)->Counter = (value)
#define timer_SET_OC_VALUE(tim,ch,value)		*(&((tim)->Ccr1) + (ch) -1) = (value)
#define timer_SET_OC_POLARITY(tim,ch,polarity)									\
			do{																	\
				(tim)->Ccer &= ~(2 << (((ch) - 1) *4)); 						\
				(tim)->Ccer |= polarity << (2 << (((((ch) - 1) *4)) + 1));		\
			}while(0);

#define timer_CAPTURE_COMPARE_ENABLE(tim,ch)	(tim)->Ccer |= 1 << (((ch) - 1) *4);
#define timer_CAPTURE_COMPARE_DISABLE(tim,ch)	(tim)->Ccer &= ~(1 << (((ch) - 1) *4));

#define timer_DMA_Enable(tim,bit)												\
		do{																		\
			(tim)->DMAInterruptEn &= ~bit;										\
			(tim)->DMAInterruptEn |= bit;										\
			}while(0)

//SR
//clear ER register of Timer, whichFlag should be one of the following
//	timer_UIF		update interrupt flag
//	timer_CC1F		capture/compare 1 interrupt flag
//	timer_CC2F		capture/compare 2 interrupt flag
//	timer_CC3F		capture/compare 3 interrupt flag
//	timer_CC4F		capture/compare 4 interrupt flag
//	timer_TIF		trigger interrupt flag
//	timer_CC1OF		capture/compare 1 overcapture flag
//	timer_CC2OF		capture/compare 2 overcapture flag
//	timer_CC3OF		capture/compare 3 overcapture flag
//	timer_CC4OF		capture/compare 4 overcapture flag

//SR
#define	timer_UIF		1
#define	timer_CC1IF		(1 << 1)
#define	timer_CC2IF		(1 << 2)
#define	timer_CC3IF		(1 << 3)
#define	timer_CC4IF		(1 << 4)
#define	timer_TIF		(1 << 6)
#define	timer_CC1OF		(1 << 9)
#define	timer_CC2OF		(1 << 10)
#define	timer_CC3OF		(1 << 11)
#define	timer_CC4OF		(1 << 12)


//DIER
#define	timer_UIE		1
#define	timer_CC1IE		(1 << 1)
#define	timer_CC2IE		(1 << 2)
#define	timer_CC3IE		(1 << 3)
#define	timer_CC4IE		(1 << 4)
#define	timer_TIE		(1 << 6)
#define	timer_UDE		(1 << 8)
#define	timer_CC1DE		(1 << 9)
#define	timer_CC2DE		(1 << 10)
#define	timer_CC3DE		(1 << 11)
#define	timer_CC4DE		(1 << 12)
#define timer_TDE		(1 << 14)

//CCMR
//Compare Mode (bit 6:4)
#define OC_FROZEN				(0 << 4)
#define OC_ACTIV_ON_MATCH		(1 << 4)
#define OC_INACTIV_ON_MATCH		(2 << 4)
#define OC_TOGGLE				(3 << 4)
#define OC_FORCE_INACTIV		(4 << 4)
#define OC_FORCE_ACTIV			(5 << 4)
#define OC_PWM1					(6 << 4)
#define OC_PWM2					(7 << 4)
//bit 3
#define OC_PRELOAD_EN			(1 << 3)
//compare capture 1/3 selection bit 1:0
#define CC_SELECT_OC			0
#define CC_SELECT_IC_DIRECT		1
#define CC_SELECT_IC_INDIRECT	2
#define CC_SELECT_IC_TRC		3




#define timer_CLEAR_FLAG(tim,whichFlag)	(tim)->Status = ~(whichFlag)
#define timer_GET_FLAG(tim,whichFlag)	(tim)->Status & whichFlag

#define timer_COUNTER_ENABLE(tim)		(tim)->Cr1 |= timer_CEN
#define timer_COUNTER_DISABLE(tim)		(tim)->Cr1 &= ~timer_CEN

#define timer_ENABLE_INTERRUPT(tim,flag)		(tim)->DMAInterruptEn |= flag
#define timer_DISABLE_INTERRUPT(tim,flag)		(tim)->DMAInterruptEn &= ~flag

#define timer_UPDATE_GEN				(tim)->EventGeneration |= timer_UG


//function header
void timer2Init(Timer_Handle_TypeDef *timer);
Status_TypeDef Timer_Base_Start(Timer_Handle_TypeDef *timer);
void timerOcSetMode(GeneralTimerRegs *timer, int channel, int mode);
void timerInItOutputCompare(GeneralTimerRegs *timer, int channel, int mode, int outPolarity, int compareValue);




#endif /* __TIMER_H__ */