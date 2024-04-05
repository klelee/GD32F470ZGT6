#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "gd32f4xx.h"
#include "systick.h"

#define LOG_USART USART0
#define LOG_USART_RCU RCU_USART0

#define LOG_USART_TX_RCU RCU_GPIOA
#define LOG_USART_TX_GPIO_PORT GPIOA
#define LOG_USART_TX_GPIO_PIN GPIO_PIN_9
#define LOG_USART_TX_AF GPIO_AF_7

#define LOG_USART_RX_RCU RCU_GPIOA
#define LOG_USART_RX_GPIO_PORT GPIOA
#define LOG_USART_RX_GPIO_PIN GPIO_PIN_10
#define LOG_USART_RX_AF GPIO_AF_7

void usart_init(void);
void usart0_init(uint32_t band_rate);
void usart_send_data(uint32_t usart_periph, uint8_t ucch);
void usart_send_string(uint32_t usart_periph, uint8_t *ucstr);

#endif  /* BSP_USART_H */
