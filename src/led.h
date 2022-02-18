

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

// LED ayarlar�n� yapar
// Arg�man :
//			@led : LED tipinde yap� i�aret�isini al�r.
//			@pin : GPIO Pin de�erlerinden birini al�r
// D�n�� de�eri : Yok
void LED_Setup(LED *led,uint16_t pin);

// LED durumunu d�nd�r�r
// Arg�man :
//			@led : LED tipinde yap� i�aret�isini al�r.
// D�n�� de�eri : 0 veya 1 olarak led o anki durumunu d�ner
int LED_GetState(LED *led);

// LED o anki durumuna ge�tikten sonra ge�en s�reyi d�ner
// Arg�man :
//			@led : LED tipinde yap� i�aret�isini al�r.
// D�n�� de�eri : uint32_t tipinde bir say� d�ner
uint32_t LED_GetStateTime(LED *led);

// LED zamanlay�c�s�n� s�f�rlar
// Arg�man :
//			@led : LED tipinde yap� i�aret�isini al�r.
// D�n�� de�eri : Yok
void LED_ResetTimer(LED *led);

// LED'i set eder
// Arg�man :
//			@led : LED tipinde yap� i�aret�isini al�r.
// D�n�� de�eri : Yok
void LED_Set(LED *led);

// LED'i reset eder
// Arg�man :
//			@led : LED tipinde yap� i�aret�isini al�r.
// D�n�� de�eri : Yok
void LED_Reset(LED *led);

void SysTick_Handler(void);



#endif /* LED_H_ */
