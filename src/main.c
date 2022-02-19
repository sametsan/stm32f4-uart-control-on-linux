#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "uart.h"
#include "led.h"


int main(void) {

	UART_Led_Config uart_led_config={500,500};
	LED led;

	SysTick_Config(SystemCoreClock / 1000);
	SystemInit();
	UART_Setup();
	LED_Setup(&led,GPIO_Pin_13);


  while (1) {

	  UART_GetCommand(&uart_led_config);

	  if(LED_GetStateTime(&led) > uart_led_config.on_time && LED_GetState(&led))
		  LED_Reset(&led);

	  if(LED_GetStateTime(&led) > uart_led_config.off_time && !LED_GetState(&led))
		  LED_Set(&led);
  }

  return 0;
}