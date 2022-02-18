#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"


void Delay(__IO uint32_t nCount)
{
    while (nCount--);
}


int main(void)
{

	GPIO_InitTypeDef GPIOD_InitDef;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIOD_InitDef.GPIO_Pin = GPIO_Pin_All;
	GPIOD_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIOD_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIOD_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOD_InitDef.GPIO_Speed = GPIO_Speed_2MHz;

	//Initialize pins
	GPIO_Init(GPIOD, &GPIOD_InitDef);


	//volatile int i;
	while (1)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_All);
		Delay(1000);
	}
}
