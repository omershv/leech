#include "main.h"

static unsigned int extendedAddr = 0;
static unsigned int lastAddr = 0;

static memoryWriteFuncType onWrite = NULL;
static memoryReadFuncType onRead = NULL;
static memoryReadListenFuncType onReadListen = NULL;

static int requestEvent(const uint8_t** bufloc);
static uint8_t requestEventListen(const uint8_t* buff);
static void receiveEvent(const uint8_t* buff, int numBytes);

void setOnWrite(memoryWriteFuncType f)
{
	onWrite = f;
}

void setOnRead(memoryReadFuncType f)
{
	onRead = f;
}

void setOnReadListen(memoryReadListenFuncType f)
{
	onReadListen = f;
}

void initI2cMemAux(I2cModes mode)
{
	extendedAddr = 0;
	lastAddr = 0;

	setI2cMode(mode);
	setOnTransmit(&requestEvent);
	setOnTransmitListen(&requestEventListen);
	setOnReceive(&receiveEvent);
}


static void receiveEvent(const uint8_t* buff, int numBytes)
{
	unsigned int idx = 0;
	unsigned char c = buff[idx++];

	if(c == 0xFF) // Extended address header
	{
		c = buff[idx++];
		extendedAddr = ((int) c) << 8;
	}
	else // Regular address header
	{
		lastAddr = c + extendedAddr;
	}

	while (idx < numBytes) // Actual data to write, if any exists
	{
		c = buff[idx++];
		onWrite(lastAddr, c);
	}
}


static int requestEvent(const uint8_t** bufloc)
{
	return onRead(lastAddr, bufloc);
}

static uint8_t requestEventListen(const uint8_t* buff)
{
	return onReadListen(lastAddr, buff);
}
