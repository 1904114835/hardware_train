#include <string.h>
#include <stm32f10x.h>
#include "input.h"

#define USART1_REC_LEN 5

extern u8 USART1_RX_BUF[USART1_REC_LEN];
extern u8 USART1_RX_LEN;
extern u8 temp[USART1_REC_LEN];


void uart1_init(u32 bound);
void USART1_IRQHandler(void);

static char *itoa(int value, char *string, int radix);
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

