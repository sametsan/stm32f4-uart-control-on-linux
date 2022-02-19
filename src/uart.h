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



// UART ayarlar�n�  yapar
// Arg�man : Yok
// D�n�� de�eri : Yok
void UART_Setup();

// UART �zerinden gelen komutlar ile config de�erlerini al�r
// Arg�man :
//			@conf : UART_Led_Config ti�inde bir yap� i�aret�isi al�r.
// D�n�� de�eri : Yok
void UART_GetCommand(UART_Led_Config *conf);


// UART �zerinden veri g�nderme i�lemi yapar
// Arg�man :
//			@string : char tipinde i�aret�i al�r.
// D�n�� de�eri : Yok
void UART_Tx(char *string);


#endif /* UART_H_ */
