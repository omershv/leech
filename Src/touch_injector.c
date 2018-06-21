#include "main.h"

#include "touch_injector.h"
#include "touch_injection_URL.h"
#include "touch_injection_photo.h"
#include "touch_injection_APP.h"
#include "garbage_injection.h"

static struct injection_scheme injectors[] =
{
		{.injection_action = get_injection_APP, .injection_init = NULL, .injection_destroy = destroy_injection_APP},
		{.injection_action = get_injection_photo, .injection_init = NULL, .injection_destroy = destroy_injection_photo},
		{.injection_action = get_injection_URL, .injection_init = init_injector_URL, .injection_destroy = destroy_injection_URL},
		{.injection_action = get_injection_garbage, .injection_init = init_injection_garbage, .injection_destroy = destroy_injection_garbage}
};


static enum injection_types injection_type;

static uint8_t base_injector_is_stop = 0;
static uint8_t buff[100];
static uint32_t injection_delay_target_tick = (uint32_t) -1;

static void base_injector_yield(void)
{
	uint32_t currTime = HAL_GetTick();
	if(currTime > injection_delay_target_tick)
	{
		injection_delay_target_tick = (uint32_t) -1;
		interruptStart();
	}
}

static void base_injector_mem_write(int addr, const uint8_t c)
{
	printf("%s %d\r\n",__FUNCTION__, __LINE__);
}

//TODO ask Amir about the interrupt hacks here
int base_injector_mem_read(int addr, const uint8_t** bufloc)
{
	*bufloc = buff;
	interruptStop();

	const uint8_t* data = injectors[injection_type].injection_action(addr);
	if(data == 0)
	{
		interruptStart();
		printf("%s %d\r\n",__FUNCTION__, __LINE__);
		memset(buff, 0, 100);
		return 100;
	}
	else if(data[1] == 0)
	{
		printf("Stop\r\n");
		interruptStart();
		base_injector_is_stop = 1;
		memset(buff, 0, 100);
		return 100;
	}
	else
	{

	}
	//printf("data[0]=%d\r\n", data[0]);
	memcpy(buff, data + 2, data[1]);
	if(data[0] != 0)
	{
		injection_delay_target_tick = (((unsigned long)data[0])*4) + HAL_GetTick();
	}
	return data[1];
}


uint8_t base_injector_is_injection_complete()
{
	return base_injector_is_stop;
}

void base_injector_init(enum injection_types type)
{
	printf("%s %d\r\n",__FUNCTION__, __LINE__);
	injection_type = type;
	initI2cMemAux(ASK_DATA);
	setOnWrite(&base_injector_mem_write);
	setOnRead(&base_injector_mem_read);
	setYield(&base_injector_yield);
	if(injectors[injection_type].injection_init != NULL)
	{
		injectors[injection_type].injection_init();
	}
	interruptStart();
}

void base_injector_destroy()
{
	printf("%s %d\r\n",__FUNCTION__, __LINE__);
	base_injector_is_stop = 0;
	injectors[injection_type].injection_destroy();
}
