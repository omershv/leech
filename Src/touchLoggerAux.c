#include "main.h"


static void loggerYield(void);

uint8_t isLoggingCompleted()
{
	return 0;
}

void init_logger()
{
	printf("Init logger\r\n");
	initI2cMemAux(PASS_THROUGH);
	setOnWrite(&loggerMemWrite);
	setOnReadListen(&loggerMemRead);
	setYield(&loggerYield);
}

void destroy_logger()
{
}

int currAddr = 0;
int idx = 0;
uint8_t data[100];

void loggerMemWrite(int addr, const uint8_t c)
{
	if(addr == currAddr)
	{
		data[idx++] = c;
	}
	else
	{
		/*char buff[sizeof(data)*3 + 100];
		char* buffptr = buff;
		buffptr += sprintf(buffptr, "transmitting pass through listen:");
		for(int i=0; i < sizeof(data); i++)
		{
			buffptr += sprintf(buffptr, " %02x", data[i]);
		}
		buffptr += sprintf(buffptr, "\r\n");
		*/
		currAddr = addr;
		idx = 0;
	}
	/*
	printf("%s %d\r\n",__FUNCTION__, __LINE__);
	*/
}

uint8_t loggerMemRead(int addr, const uint8_t* buff)
{
	/*printf("%s %d\r\n",__FUNCTION__, __LINE__);

	char pbuff[100*3 + 100];
	char* buffptr = pbuff;
	buffptr += sprintf(buffptr, "mem read listen - addr: %d data:", addr);
	for(int i=0; i < 100; i++)
	{
		buffptr += sprintf(buffptr, " %02x", buff[i]);
	}
	buffptr += sprintf(buffptr, "\r\n");
	printf("%s", pbuff);
	*/

	return 1;
}

static void loggerYield(void)
{
	HAL_GPIO_WritePin(INTERRUPT_OUT, HAL_GPIO_ReadPin(INTERRUPT_IN));
}

