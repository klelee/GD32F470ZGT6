#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"


TaskHandle_t StartTask_Handler;

void LED_Init(void);
void CrateTask(void *pvParameters);
void task_led2(void *pvParameters);
void task_led4(void *pvParameters);


int main(void) {	
	systick_config();
	LED_Init();  // led初始化
	usart_init();
	
	xTaskCreate(CrateTask ,"CrateTask" , 128, NULL, 1, &StartTask_Handler);
	vTaskStartScheduler();          //开启任务调度
	
	while(1) {
		;
	}
}

void LED_Init(void)
{
	//LED2
	rcu_periph_clock_enable(RCU_GPIOD);
	gpio_mode_set(GPIOD,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_7);
	gpio_output_options_set(GPIOD,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_7);
	
	//LED4
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_5);
	gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_5);
}

void CrateTask(void *pvParameters){
	
	taskENTER_CRITICAL();
	
	xTaskCreate(task_led2 , "task_led2" ,50 ,NULL , 2 ,0);
	
	xTaskCreate(task_led4 , "task_led4" ,50 ,NULL , 2 ,0);
	
	vTaskDelete(StartTask_Handler);
	
	taskEXIT_CRITICAL(); 
	
}

void task_led2(void *pvParameters)
{  
	while(1)
	{	
		printf("task_led2\n");
		gpio_bit_write(GPIOD, GPIO_PIN_7, SET);
		vTaskDelay(500);
		gpio_bit_write(GPIOD, GPIO_PIN_7, RESET);
		vTaskDelay(500);
	}
}   

void task_led4(void *pvParameters)
{
	while(1)
	{
		printf("task_led4\n");
		gpio_bit_write(GPIOA, GPIO_PIN_5, SET);
		vTaskDelay(1000);
		gpio_bit_write(GPIOA, GPIO_PIN_5, RESET);
		vTaskDelay(1000);
		
	}
}
