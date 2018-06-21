#include "main.h"
#include "sniff.h"

static uint8_t init_timer = 0;
static uint32_t timer_start_time = 0;
static uint8_t timer_triggered = 0;
static uint8_t isStop = 0;
static uint32_t timeout = 0;
static uint8_t has_slept = 0;
static uint8_t has_woken = 0;
static uint8_t was_reboot = 0;
static uint8_t should_stop_on_reboot = 0;

static uint8_t check_timer()
{
	uint8_t ans = 0;
	if(timeout != 0 && !init_timer)
	{
		timer_start_time = HAL_GetTick();
		init_timer = 1;
	}
	else
	{
		uint32_t current = HAL_GetTick();
		if(current - timer_start_time >  timeout)
		{
			ans = 1;
			isStop = 1;
		}
	}
	return ans;
}


static void logger_with_timer_yield(void)
{
	if(check_timer())
	{
		if(timer_triggered == 0)
		{
			timer_triggered = 1;
			init_timer = 0;
			printf("\r\nchange trigger to 1\r\n");
		}
		interruptStart();
	}
	else
	{
		interruptMirror();
	}
}

static void logger_with_timer_mem_write(int addr, const uint8_t c)
{
	loggerMemWrite(addr, c);
	if(addr == 0x15 && c == 0x07)
	{
		printf("Wake up\r\n");
		if(has_slept)
		{
			has_woken = 1;
			isStop = 1;
		}
	}
	else if(addr == 0x14 && c == 0x01)
	{
		printf("Sleep\r\n");
		has_slept = 1;
	}
}

static uint8_t logger_with_timer_mem_read(int addr, const uint8_t* buff)
{
	loggerMemRead(addr,buff);
	uint8_t allowTransmission = 1;
	isStop = hasInjection(addr ,0 , buff, &allowTransmission);
	if(isStop)
	{
		printf("hasInjection = %d\r\n", isStop);
	}
	if(addr == 0xE9)
	{
		printf("Reboot\r\n");
		if(should_stop_on_reboot)
		{
			was_reboot = 1;
			isStop = 1;
		}
	}
	return allowTransmission;
}

uint8_t logger_with_timer_was_timer_triggered()
{
	return timer_triggered;
}

uint8_t logger_with_timer_was_woken()
{
	return has_woken;
}

uint8_t logger_with_timer_was_reboot()
{
	return was_reboot;
}

uint8_t logger_with_timer_completed()
{
	return isStop;
}

void logger_with_timer_init(uint32_t timer_timeout, uint8_t stop_on_reboot)
{
	initI2cMemAux(PASS_THROUGH);
	setOnWrite(&logger_with_timer_mem_write);
	setOnReadListen(&logger_with_timer_mem_read);
	setYield(&logger_with_timer_yield);
	sniffer_init();
	timer_triggered = 0;
	timer_start_time = 0;
	init_timer = 0;
	timeout = timer_timeout;
	should_stop_on_reboot = stop_on_reboot;
}

void logger_with_timer_destroy()
{
	isStop = 0;
}
