#include "ON_OFF_GPIO.h"
#include "stm32f10x.h"


int Config_GPIO(GPIO_TypeDef* gpio_x,uint16_t gpio_pin)
{
	if(gpio_x==GPIOA)      {RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);}
	 else if(gpio_x==GPIOB) {RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);}
	  else if(gpio_x==GPIOC) {RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);}
 	   else if(gpio_x==GPIOD) {RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);}
     	else if(gpio_x==GPIOE) {RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);}
	     else return 0;

	GPIO_InitTypeDef GPIO_STRUCT;
	GPIO_STRUCT.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_STRUCT.GPIO_Pin=gpio_pin;
	GPIO_STRUCT.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(gpio_x, &GPIO_STRUCT);

    return 1;
}

void ON_GPIO(GPIO_TypeDef* gpio_x,uint16_t gpio_pin)
{
 GPIO_SetBits(gpio_x, gpio_pin);
}

void OFF_GPIO(GPIO_TypeDef* gpio_x,uint16_t gpio_pin)
{
 GPIO_ResetBits(gpio_x, gpio_pin);
}
