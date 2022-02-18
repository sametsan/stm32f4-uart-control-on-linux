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
	

// UART INIT


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);//Tx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);//Rx

	GPIO_InitTypeDef GPIO_InitStructure ={
		.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1,
		.GPIO_Mode = GPIO_Mode_AF,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_UP,
		.GPIO_Speed = GPIO_Speed_50MHz
	};
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;       // we want to configure the UART5 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the UART5 interrupts
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;      // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         // the UART5 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStructure);


	USART_InitTypeDef Uart ={
		.USART_BaudRate=115200,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
		.USART_WordLength = USART_WordLength_8b,
		.USART_StopBits = USART_StopBits_1,
		.USART_Parity = USART_Parity_No,
		.USART_HardwareFlowControl= USART_HardwareFlowControl_None
	};

	USART_Init(UART4,&Uart);

	USART_Cmd(UART4, ENABLE);

	

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


void UART4_IRQHandler(void)
{
    /* RXNE handler */
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {

    	uint16_t c = USART_ReceiveData(UART4);

    	USART_SendData(UART4,c);

    }

}