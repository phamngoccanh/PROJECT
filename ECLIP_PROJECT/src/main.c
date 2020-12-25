

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "interrupt_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "timer.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"
int delayms=0;
void delay_ms(int ms);
uint16_t data_receive[20];
uint8_t cout=0;
int
main(int argc, char* argv[])
{
  config();
  config_timer();
  config_watchdog_IWDG();
  IWDG->KR=0XAAAA;
  IWDG->KR=0XCCCC;
  SysTick_Config(SystemCoreClock/1000); //
  while (1)
    {
     delay_ms(1000);
     IWDG->KR=0XAAAA;
    }
}
void EXTI15_10_IRQHandler(void)
{
 if(EXTI_GetITStatus(EXTI_Line15)==SET)
    {
	  EXTI_ClearITPendingBit(EXTI_Line15);
	  //CODE KHI NGAT XAY RA
	}
}

void SysTick_Handler(void)
{
 if(delayms!=0) delayms--;
}

void delay_ms(int ms)
{
	delayms=ms;
	while(!delayms){}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
		//NGAT TIMER
	}
}


void USART1_IRQHandler(void)
{
 if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET)
    {
	 if(cout<20)
	  {
		 data_receive[cout]=USART_ReceiveData(USART1);
		 if(data_receive[cout]==13)//ky tu enter
		 {
			 //if(strstr(data_receive,"BAT")!=""){}
			 cout=0;
			 for(int i=0;i<20;i++) data_receive[i]=0;
		 }
		 else  cout++;

	  }
	 if (cout==20)
	 {
		 cout=0;
		 for(int i=0;i<20;i++) data_receive[i]=0;
	 }

	}
}
#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
