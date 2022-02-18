#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "led.h"
#include "system_stm32f4xx.h"


void Delay(__IO uint32_t nCount)
{
    while (nCount--);
}


int main(void)
{
	LED led;

	SysTick_Config(SystemCoreClock / 1000);
	SystemInit();


	LED_Setup(&led,GPIO_Pin_13);
	

	//volatile int i;
	while (1)
	{

	  if(LED_GetState(&led))
		  LED_Reset(&led);

	  if(!LED_GetState(&led))
		  LED_Set(&led);

		Delay(1000);
	}
}
