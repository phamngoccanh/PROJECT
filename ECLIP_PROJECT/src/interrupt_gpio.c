#include "stm32f10x.h"
#include "interrupt_gpio.h"
#include "stm32f10x_exti.h"
void config_clock()
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}
void config_GPIO_INTERRUPT()
{
GPIO_InitTypeDef GPIO_STRUCT;
GPIO_STRUCT.GPIO_Mode=GPIO_Mode_IPU;
GPIO_STRUCT.GPIO_Pin=GPIO_Pin_15;
GPIO_STRUCT.GPIO_Speed=GPIO_Speed_50MHz;
//Khởi động cấu hình
GPIO_Init(GPIOA, &GPIO_STRUCT);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);
}

void config_exti()
{
EXTI_InitTypeDef EXTI_STRUCT;
EXTI_STRUCT.EXTI_Line=EXTI_Line15;
EXTI_STRUCT.EXTI_Mode=EXTI_Mode_Interrupt;
EXTI_STRUCT.EXTI_Trigger=EXTI_Trigger_Falling;
EXTI_STRUCT.EXTI_LineCmd=ENABLE;
EXTI_Init(&EXTI_STRUCT);
}
void config_NVCI_GPIO()
{
NVIC_InitTypeDef NVIC_STRUCT;
NVIC_STRUCT.NVIC_IRQChannel=EXTI15_10_IRQn;

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//SỬ DÙNG CÁC MỨC ƯU TIÊN Ở GROUP 2 (0-3;0-3)
NVIC_STRUCT.NVIC_IRQChannelPreemptionPriority=1;
NVIC_STRUCT.NVIC_IRQChannelSubPriority=1;
NVIC_STRUCT.NVIC_IRQChannelCmd=ENABLE;
////Khởi động cấu hình
NVIC_Init(&NVIC_STRUCT);
}
void config()
{

	config_clock();
	config_GPIO_INTERRUPT();
	config_exti();
	config_NVCI_GPIO();
}


