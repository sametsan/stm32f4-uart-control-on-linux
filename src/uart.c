/*
 * uart.c
 *
 *  Created on: 13 Ara 2021
 *      Author: Samet
 */

#include "uart.h"

#define COMMAND_MAX_SIZE 1024

static	char data[COMMAND_MAX_SIZE];
static	int size;
static	int is_empty;
static 	int echo=1;

void UART_Setup(){

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

}

void UART4_IRQHandler(void)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_14);
    /* RXNE handler */
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
    	if(size >= COMMAND_MAX_SIZE)
    		size =0;

    	uint16_t c = USART_ReceiveData(UART4);
    	char e = (char) (c & 0xFF);

    	if(echo==1)
    		USART_SendData(UART4,c);

    	if(e != '\r' && e!='\n'){
			data[size]=c;
			size++;
    	}else
    		is_empty=0;
    }
    GPIO_ResetBits(GPIOD, GPIO_Pin_14);

}

void UART_Tx(char *s){
	USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
}


void UART_GetCommand(UART_Led_Config *conf){

	if(is_empty == 1)
		return 0;

	char temp[32]={0};

	memcpy(temp,data,size);

	sscanf(temp,"ledon=%d",&conf->on_time);

	sscanf(temp,"ledoff=%d",&conf->off_time);

	if(!strncmp(temp,"start",5))
		echo=1;

	if(!strncmp(temp,"stop",4))
		echo=0;

	memset(data,0,COMMAND_MAX_SIZE);
	size=0;
	is_empty=1;
}
