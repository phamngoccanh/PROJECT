#include "stm32f10x.h"
#include "timer.h"
void config_timer(void)
{
	//config rcc
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //BẠT CLOCK CHO TIM2 LÀ APB1

	//config TIM2 BASE
	TIM_TimeBaseInitTypeDef TIME_BASE_STRUCT;
	TIME_BASE_STRUCT .TIM_Prescaler=7999;
	TIME_BASE_STRUCT.TIM_Period=9999;
	TIME_BASE_STRUCT. TIM_CounterMode=TIM_CounterMode_Up;
	TIME_BASE_STRUCT.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM2,&TIME_BASE_STRUCT);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update , ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	NVIC_InitTypeDef NVIC_STRUCT;
	NVIC_STRUCT.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_STRUCT.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_STRUCT.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_STRUCT);





}

void config_watchdog_IWDG(void)
{
	IWDG->KR=0x5555; //bat che do ghi de len IWDG_PR và IWDG_RLR
	IWDG->PR=200; //THANH GHI LUU PRESSSCALE
	IWDG->RLR=312;//THANH GHI READ LOAD REGISTER
	IWDG->KR=0xAAAA; //TAT GHI DE ,NAP LAI GIA TRI CHO THANH RESET REGISTER
}
