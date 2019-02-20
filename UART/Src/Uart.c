#include <stdio.h>
#include <stdint.h>
#include "Uart.h"
#include "Gpio.h"
#include <string.h>
#include "stm32f4xx_hal.h"
#include "Timer.h"
#include "NVIC.h"

extern int togglenum;
extern char wordsBuffer[];
extern char receiveBuffer[];
int count = 0;
void configureUSARTBaudRate(UartRegs *usart,uint32_t peripheralFreq,uint32_t desiredBR,OversamplingMode oversampling){

	float divider;
	uint8_t fractional;
	uint8_t mantissa;

	divider = (float)peripheralFreq/(8*(2-oversampling)*desiredBR);
	mantissa = (uint8_t)divider;
	fractional = (int)((float)(divider - mantissa)*(8*(2-oversampling)));

	usart->Brr = (mantissa << 4)|fractional;
}


void configureUSART(UartRegs *usart,long long mode,int desiredBR,uint32_t peripheralFreq){

	usart->Cr1 = (uint32_t)(mode & 0xffff);
	usart->Cr2 = (uint32_t)((mode >> 16) & 0xffff);
	usart->Cr3 = (uint32_t)(mode >> 32);

	if(IS_OVERSAMPLING_16(mode))
		configureUSARTBaudRate(usart,peripheralFreq,desiredBR,USART_OVER_16);
	else
		configureUSARTBaudRate(usart,peripheralFreq,desiredBR,USART_OVER_8);
}

void UART5_IRQHandler(void){

	  if(usartIsRXNERegNotEmpty(uart5)){
		  receiveBuffer[count] = (uart5)->Dr;

		  if(usartIsTXRegEmpty(uart5))
			  (uart5)->Dr = receiveBuffer[count];

		  if(receiveBuffer[count] == '\n'){
			  receiveBuffer[count] = '\0';

			  if(!strcmp(receiveBuffer,"TURN ON LED")){
				  gpioWritePins(GpioG,GpioPin13,GPIO_Pin_Set);

			  }
			  else if(!strcmp(receiveBuffer,"TURN OFF LED")){
				  gpioWritePins(GpioG,GpioPin13,GPIO_Pin_Reset);
			  }
			 else if(!strcmp(receiveBuffer,"BLINK LED")){
				  timer2->Arr = 112500;
				  timer2->Prescaler = 49;
				  timer2->Counter = 0;

				  nvicEnableInterrupt(28);
				  timer_ENABLE_INTERRUPT(timer2,timer_UIE);
				  timer_COUNTER_ENABLE(timer2);

			  }
			  count=0;

		  }
		  else
			  count++;

	/*int length= strlen(wordsBuffer);

	  if(usartIsTXRegEmpty(uart5)){
		  (uart5)->Dr = wordsBuffer[count];
	  	  count++;
		  if(count == length){
			  count=0;
		  }
	  }

*/
}
}
