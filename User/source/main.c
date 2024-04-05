#include "main.h"

int main(void)
{
    systick_config();
	usart_init();
	
    while(1) {
		delay_1ms(1000);
		printf("GD32F470 test!\n");
    }
}
