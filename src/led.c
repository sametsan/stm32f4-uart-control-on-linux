
#include "led.h"

static uint32_t timer=0;

void LED_Setup(LED *led,uint16_t pin){
	led->pin = pin;
	led->time = timer;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

int LED_GetState(LED *led){
	return led->state;
}

uint32_t LED_GetStateTime(LED *led){
	return timer-led->state_start_time;
}

void LED_ResetTimer(LED *led){
	led->time=timer;
}

void LED_Set(LED *led){
	GPIO_SetBits(GPIOD,led->pin);
	led->state_start_time = timer;
	 led->state=1;
}

void LED_Reset(LED *led){
	GPIO_ResetBits(GPIOD,led->pin);
	led->state_start_time = timer;
	 led->state=0;
}

void SysTick_Handler(void) {
  timer++;
}
