#ifndef __ON_OFF_GPIO_H
#define __ON_OFF_GPIO_H
#include "stm32f10x.h"

int Config_GPIO(GPIO_TypeDef* gpio_x,uint16_t gpio_pin);
void ON_GPIO(GPIO_TypeDef* gpio_x,uint16_t gpio_pin);
void OFF_GPIO(GPIO_TypeDef* gpio_x,uint16_t gpio_pin);

#endif
