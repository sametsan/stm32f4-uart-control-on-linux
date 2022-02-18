

#ifndef LED_H_
#define LED_H_

#include "stm32f4xx_gpio.h"
#include "stdint.h"

typedef struct{
	int state;
	uint32_t time;
	uint32_t state_start_time;
	uint16_t pin;
}LED;

// LED ayarlarını yapar
// Argüman :
//			@led : LED tipinde yapı işaretçisini alır.
//			@pin : GPIO Pin değerlerinden birini alır
// Dönüş değeri : Yok
void LED_Setup(LED *led,uint16_t pin);

// LED durumunu döndürür
// Argüman :
//			@led : LED tipinde yapı işaretçisini alır.
// Dönüş değeri : 0 veya 1 olarak led o anki durumunu döner
int LED_GetState(LED *led);

// LED o anki durumuna ge�tikten sonra ge�en s�reyi döner
// Argüman :
//			@led : LED tipinde yapı işaretçisini alır.
// Dönüş değeri : uint32_t tipinde bir sayı döner
uint32_t LED_GetStateTime(LED *led);

// LED zamanlayıcısını sıfırlar
// Argüman :
//			@led : LED tipinde yapı işaretçisini alır.
// Dönüş değeri : Yok
void LED_ResetTimer(LED *led);

// LED'i set eder
// Argüman :
//			@led : LED tipinde yapı işaretçisini alır.
// Dönüş değeri : Yok
void LED_Set(LED *led);

// LED'i reset eder
// Argüman :
//			@led : LED tipinde yapı işaretçisini alır.
// Dönüş değeri : Yok
void LED_Reset(LED *led);

void SysTick_Handler(void);



#endif /* LED_H_ */
