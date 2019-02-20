#include "Timer.h"
#include "Gpio.h"

int togglenum=0;

void timer2Init(Timer_Handle_TypeDef *timer)
{
	timer->instance = timer2;
}

//void ccxChannelConfigure(Timer_Handle_TypeDef *timer, uint32_t channel, uint32_t channelState)


Status_TypeDef Timer_Base_Start(Timer_Handle_TypeDef *timer)
{
	timer->state = TIM_STATE_BUSY;
	timer->instance->Cr1 |= 0x0001;
	timer->state = TIM_STATE_READY;

	return Ok;
}
/*
Status_TypeDef Timer_OC_Start(Timer_Handle_TypeDef *timer, uint32_t channel)
{


}
*/
/**
 * Set the timer output cmpare channel to the specified mode
 *
 * Input:
 * 	mode	is the mode of the output compare. thy can be anyone below
 * 			OC_Frozen
 * 			OC_Activ_On_Match
 *
 */
void timerInItOutputCompare(GeneralTimerRegs *timer, int channel, int mode, int outPolarity, int compareValue)
{

	timerOcSetMode(timer,channel,mode);
	timer_SET_OC_VALUE(timer,channel,compareValue);
	timer_SET_OC_POLARITY(timer,channel,outPolarity);
}

void timerOcSetMode(GeneralTimerRegs *timer, int channel, int mode)
{
	int numOfShifts = 0;
	TimerRegister *ccmr = &(timer->Ccmr1);

	if(((channel -1) & 1) == 1){
		numOfShifts = 8;
	}

	if(channel > 2){
		ccmr++;
	}

	*ccmr = mode << (numOfShifts);
}

void TIM2_IRQHandler(void){

	if(timer_GET_FLAG(timer2,timer_UIF)){
		gpioTogglePins(GpioG,GpioPin13);
		togglenum++;
		timer_CLEAR_FLAG(timer2,timer_UIF);
		 if(togglenum>8){
		  timer_DISABLE_INTERRUPT(timer2,timer_UIE);
		  timer_COUNTER_DISABLE(timer2);
		  togglenum = 0;
		 }
	}
}
