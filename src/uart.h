/*
 * uart.h
 *
 *  Created on: 13 Ara 2021
 *      Author: Samet
 */

#ifndef UART_H_
#define UART_H_
#include <stdio.h>
#include <string.h>

#include "stm32f4xx_usart.h"



typedef struct {
	int on_time;
	int off_time;
}UART_Led_Config;



// UART ayarlarýný  yapar
// Argüman : Yok
// Dönüþ deðeri : Yok
void UART_Setup();

// UART üzerinden gelen komutlar ile config deðerlerini alýr
// Argüman :
//			@conf : UART_Led_Config tiðinde bir yapý iþaretçisi alýr.
// Dönüþ deðeri : Yok
void UART_GetCommand(UART_Led_Config *conf);


// UART üzerinden veri gönderme iþlemi yapar
// Argüman :
//			@string : char tipinde iþaretçi alýr.
// Dönüþ deðeri : Yok
void UART_Tx(char *string);


#endif /* UART_H_ */
