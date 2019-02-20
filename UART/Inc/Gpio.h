#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>

typedef enum{
	GPIO_Pin_Reset = 0,
	GPIO_Pin_Set,
}GPIOPinState;

typedef enum {
	GPIO_INPUT = 0,
	GPIO_OUTPUT,
	GPIO_ALT_FUNC,
	GPIO_ANALOG,
}GPIOMode;

//GPIO output driver type is at bit 2
typedef enum {
	GPIO_PUSH_PULL = 0,
	GPIO_OPEN_DRAIN = 1 << 2,
}GPIODriverType;

//GPIO output speed is at bit 3 and 4
typedef enum {
	GPIO_LOW_SPEED = 0,
	GPIO_MED_SPEED = 1 << 3,
	GPIO_HI_SPEED = 2 << 3,
	GPIO_VERY_HI_SPEED = 3 << 3,
}GPIOOutSpeed;

//GPIO pull type is at bit 5 and 6
typedef enum {
	GPIO_NO_PULL = 0,
	GPIO_PULL_UP = 1 << 5,
	GPIO_PULL_DOWN = 2 << 5,
}GPIOPullType;

typedef enum{
	GpioPin0  = 0x0001,
	GpioPin1  = 0x0002,
	GpioPin2  = 0x0004,
	GpioPin3  = 0x0008,
	GpioPin4  = 0x0010,
	GpioPin5  = 0x0020,
	GpioPin6  = 0x0040,
	GpioPin7  = 0x0080,
	GpioPin8  = 0x0100,
	GpioPin9  = 0x0200,
	GpioPin10 = 0x0400,
	GpioPin11 = 0x0800,
	GpioPin12 = 0x1000,
	GpioPin13 = 0x2000,
	GpioPin14 = 0x4000,
	GpioPin15 = 0x8000,
}GpioPin;

typedef volatile uint32_t IoRegister ;

typedef struct GpioRegs GpioRegs;
struct GpioRegs {
	IoRegister mode;
	IoRegister driverType;
	IoRegister outSpeed;
	IoRegister pullType;
	IoRegister inData;
	IoRegister outData;
	IoRegister outBits;
	IoRegister pinLock;
	IoRegister altFuncLow;
	IoRegister altFuncHi;
	};

//GPIO alternate function at bit 7
#define AF_0		0
#define AF_1		1
#define AF_2		2
#define AF_3		3
#define AF_4		4
#define AF_5		5
#define AF_6		6
#define AF_7		7
#define AF_8		8
#define AF_9		9
#define AF_10		10
#define AF_11		11
#define AF_12		12
#define AF_13		13
#define AF_14		14
#define AF_15		15


#define GpioA  ((GpioRegs *)0x40020000)
#define GpioB  ((GpioRegs *)0x40020400)
#define GpioC  ((GpioRegs *)0x40020800)
#define GpioD  ((GpioRegs *)0x40020C00)
#define GpioE  ((GpioRegs *)0x40021000)
#define GpioF  ((GpioRegs *)0x40021400)
#define GpioG  ((GpioRegs *)0x40021800)
#define GpioH  ((GpioRegs *)0x40021C00)
#define GpioI  ((GpioRegs *)0x40022000)
#define GpioJ  ((GpioRegs *)0x40022400)
#define GpioK  ((GpioRegs *)0x40022800)

//function header
void configureGPIO_Pin(GpioRegs *port, GpioPin pins, int configuration);
void configureAltFunction(GpioRegs *port, GpioPin pin, int altFuncVal);
void gpioWritePins(GpioRegs *port, GpioPin pins, int state);
void gpioTogglePins(GpioRegs *port, GpioPin pins);
uint32_t gpioReadPins(GpioRegs *port, GpioPin pins);

#endif /* __GPIO_H__ */
