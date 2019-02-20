#include <stdio.h>
#include <stdint.h>
#include "Common.h"
#include "NVIC.h"


void nvicEnableInterrupt(int interruptNumber)
{
	int n,bit;

	n = interruptNumber/32;
	bit = interruptNumber%32;

	nvic->ISER[n] = 1 << bit;
}

void nvicDisableInterrupt(int interruptNumber)
{
	int n,bit;

	n = interruptNumber/32;
	bit = interruptNumber%32;

	nvic->ICER[n] = 1 << bit;
}

void nvicEnablePendingInterrupt(int interruptNumber)
{
	int n,bit;

	n = interruptNumber/32;
	bit = interruptNumber%32;

	nvic->ISPR[n] = 1 << bit;
}

void nvicDisablePendingInterrupt(int interruptNumber)
{
	int n,bit;

	n = interruptNumber/32;
	bit = interruptNumber%32;

	nvic->ICPR[n] = 1 << bit;
}

/*
int nvicIsInterruptActive(int interruptNumber)
{

}

void nvicPriorityInterrupt(int interruptNumber,int priority)
{


}
*/
