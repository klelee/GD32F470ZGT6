#include "bsp_usart.h"
#include "stdio.h"

void usart0_init(uint32_t baudrate)
{
    rcu_periph_clock_enable(LOG_USART_RCU);
    rcu_periph_clock_enable(LOG_USART_TX_RCU);
    rcu_periph_clock_enable(LOG_USART_RX_RCU);
    
    gpio_af_set(LOG_USART_TX_GPIO_PORT, LOG_USART_TX_AF, LOG_USART_TX_GPIO_PIN);
    gpio_af_set(LOG_USART_RX_GPIO_PORT, LOG_USART_RX_AF, LOG_USART_RX_GPIO_PIN);

    gpio_mode_set(LOG_USART_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, LOG_USART_TX_GPIO_PIN);
    gpio_mode_set(LOG_USART_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, LOG_USART_RX_GPIO_PIN);

    gpio_output_options_set(LOG_USART_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOG_USART_TX_GPIO_PIN);
    gpio_output_options_set(LOG_USART_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOG_USART_RX_GPIO_PIN);

    usart_deinit(LOG_USART);
    usart_baudrate_set(LOG_USART, baudrate);
    usart_parity_config(LOG_USART, USART_PM_NONE);
    usart_word_length_set(LOG_USART, USART_WL_8BIT);
    usart_stop_bit_set(LOG_USART, USART_STB_1BIT);
    usart_transmit_config(LOG_USART, USART_TRANSMIT_ENABLE);
    usart_enable(LOG_USART);
}

void usart_send_data(uint32_t usart_periph, uint8_t ucch)
{
	usart_data_transmit(usart_periph, (uint8_t)ucch);
	while(RESET == usart_flag_get(usart_periph, USART_FLAG_TBE));
}

void usart_send_string(uint32_t usart_periph, uint8_t *ucstr)
{
	while(ucstr && *ucstr) {
	  usart_send_data(usart_periph, *ucstr++);
	}
}

int fputc(int ch, FILE *f)
{
     usart_send_data(LOG_USART, ch);
     return ch;
}

void usart_init()
{
	usart0_init(115200U);
}
