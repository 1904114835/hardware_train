#include "usart.h"
#include "time.h"
#include "usart2.h"
#include "usart3.h"
#include "input.h"
#include "key.h"

u8 USART1_RX_BUF[USART1_REC_LEN];
u8 USART1_RX_LEN;

u8 USART2_RX_BUF[USART2_REC_LEN];
u8 USART2_RX_LEN;
u8 temp[USART1_REC_LEN];

u8 USART3_RX_BUF[USART3_REC_LEN];
u8 USART3_RX_LEN;
u8 temp2[USART3_REC_LEN];
