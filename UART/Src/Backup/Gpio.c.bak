#include <stdio.h>
#include <stdint.h>
#include "Gpio.h"


uint8_t bitPostion[] = {
		-1,		//0000 undefined
		 0,		//0001
		 1,		//0010
		-2,		//0011 undefined
		 2,		//0100
		-2,		//0101 undefined
		-2,		//0110 undefined
		-2,		//0111 undefined
		 3,		//1000
		-2,		//1001 undefined
		-2,		//1010 undefined
		-2,		//1011 undefined
		-2,		//1100 undefined
		-2,		//1101 undefined
		-2,		//1110 undefined
		-2,		//1111 undefined
};


void configureGPIO_Pin(GpioRegs *port, GpioPin pins, int configuration)
{
	uint32_t tempMode, tempDriverType, tempOutSpeed,tempPullType;
	uint16_t pinValue;
	uint16_t pinMask = 0x0001;

	tempMode = configuration & 0x03;
	tempDriverType = (configuration & 0x04) >> 2;
	tempOutSpeed = (configuration & 0x18) >> 3;
	tempPullType = (configuration & 0xC0) >> 5;


	for(int i=0; i<16 ; i++)
	{
		pinValue = pinMask & pins;

		if(pinValue)
		{
			port->mode &= ~(3 << (i * 2));
			port->mode |= tempMode << (i * 2);

			port->driverType &= ~(1 << (i * 2));
			port->driverType |= tempDriverType << i;

			port->outSpeed &= ~(3 << (i * 2));
			port->outSpeed |= tempOutSpeed << (i * 2);

			port->pullType &= ~(3 << (i * 2));
			port->pullType |= tempPullType << (i * 2);
		}

		pinMask = pinMask << 1;

	}


}


void configureAltFunction(GpioRegs *port, GpioPin pin, int altFuncVal){

	IoRegister *afr = &(port->altFuncLow);
	uint16_t pinMask = 0x0001;
	uint16_t pinValue=0;
	int pinCount=0;

	while(pinValue == 0){
		pinValue = pin & pinMask;
		pinMask = pinMask << 1;
		pinCount++;
	}

	if(pinCount>7){
		afr++;
		pinCount -= 8;
	}

	*afr = altFuncVal << (4 * (pinCount -1));

}

void gpioWritePins(GpioRegs *port, GpioPin pins, int state)
{
		if(state == 1){
			port->outBits = pins;
		}
		else
		{
			port->outBits = pins << 16;
		}
}

void gpioTogglePins(GpioRegs *port, GpioPin pins)
{
	port->outData = (port->outData) ^ pins;
}

uint32_t gpioReadPins(GpioRegs *port, GpioPin pins)
{
	if(! ( (port->inData) & pins))
	{
		return GPIO_Pin_Reset;
	}
	else
	{
		return GPIO_Pin_Set;
	}

}
