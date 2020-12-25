#ifndef __ON_OFF_GPIO_H
#define __ON_OFF_GPIO_H
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
void config_clock();
void config_GPIO_INTERRUPT();
void config_NVCI_GPIO();
void config_exti();
void config();
#endif
