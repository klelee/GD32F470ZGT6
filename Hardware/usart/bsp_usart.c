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

#if !defined(__MICROLIB)
//不使用微库的话就需要添加下面的函数
#if (__ARMCLIB_VERSION <= 6000000)
//如果编译器是AC5  就定义下面这个结构体
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
#endif

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(LOG_USART, (uint8_t)ch);
    while(RESET == usart_flag_get(LOG_USART, USART_FLAG_TBE));
    return ch;
}

void usart_send_data(uint32_t usart_periph, uint8_t ucch)
{
    usart_data_transmit(usart_periph, (uint8_t)ucch);  
    while(RESET == usart_flag_get(usart_periph, USART_FLAG_TBE)); // 等待发送数据缓冲区标志置位
}

void usart_send_buffer(uint32_t usart_periph, uint8_t *ucstr)
{   
    while(ucstr && *ucstr) {     
        usart_send_data(usart_periph, *ucstr++);    
    }
}

void usart_init(void) {
    usart0_init(115200U);
}
