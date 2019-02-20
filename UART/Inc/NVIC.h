#ifndef __NVIC_H__
#define __NVIC_H__

#include <stdint.h>
#include "Common.h"

typedef struct NVICRegs NVICRegs;
struct NVICRegs{
	IoRegister ISER[3];
	IoRegister Reserved0[29];
	IoRegister ICER[3];
	IoRegister Reserved1[29];
	IoRegister ISPR[3];
	IoRegister Reserved2[29];
	IoRegister ICPR[3];
	IoRegister Reserved3[29];
	IoRegister IABR[3];
	IoRegister Reserved4[61];
	IoRegister IPR[21];
	IoRegister Reserved5[677];
	IoRegister STIR;
};

#define nvic		((NVICRegs *)0xE000E100)


void nvicEnableInterrupt(int interruptNumber);
void nvicDisableInterrupt(int interruptNumber);
void nvicEnablePendingInterrupt(int interruptNumber);
void nvicDisablePendingInterrupt(int interruptNumber);
int nvicIsInterruptActive(int interruptNumber);
void nvicPriorityInterrupt(int interruptNumber,int priority);

#endif /* __NVIC_H__ */
