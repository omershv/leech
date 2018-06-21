#include "main.h"
#include "string.h"

static uint8_t i2c1rxbuffer[5000];
static uint8_t i2c2rxbuffer[100];


static __IO uint8_t	dataReceived = 0;
static __IO uint32_t uwTransferInitiated = 0;
static __IO uint32_t uwTransferEnded = 0;
static __IO uint8_t waitingForSlave = 0;
static I2cModes mode;

static receiveFuncType onReceive = NULL;
static transmitFuncType onTransmit = NULL;
static transmitListenFuncType onTransmitListen = NULL;
static yieldFuncType yield = NULL;

void setYield(yieldFuncType f)
{
	yield = f;
}

void setOnReceive(receiveFuncType f)
{
	onReceive = f;
}

void setOnTransmit(transmitFuncType f)
{
	onTransmit = f;
}

void setOnTransmitListen(transmitListenFuncType f)
{
	onTransmitListen = f;
}

void setI2cMode(I2cModes newMode)
{
	mode = newMode;
	if(mode == PASS_THROUGH)
	{
		HAL_GPIO_WritePin(INTERRUPT_OUT, HAL_GPIO_ReadPin(INTERRUPT_IN));
	}
}

// Called in interrupt context
void dataReceiveAsSlaveStart(void)
{
	if(HAL_I2C_Slave_Sequential_Receive_IT(&I2cHandle1, i2c1rxbuffer, sizeof(i2c1rxbuffer), I2C_FIRST_FRAME) != HAL_OK)
	{
		Error_Handler();
	}
	dataReceived++;
}

// Called while transfer is in proccess
void dataReceiveAsSlaveDuring(void)
{
}

// Called after transfer ended
void dataReceiveAsSlaveEnd(void)
{
	if(dataReceived)
	{
		int transferSize = sizeof(i2c1rxbuffer) - I2cHandle1.XferSize;

		if(onReceive != NULL)
		{
			onReceive(i2c1rxbuffer, transferSize);
		}
		if(mode == ASK_DATA)
		{
		}
		else
		{
#ifdef VERBOSE

			char buff[sizeof(i2c1rxbuffer)*3 + 100];
			char* buffptr = buff;
			buffptr += sprintf(buffptr, "received %x:", transferSize);
			for(int i = 0; i < transferSize; i++)
			{
				buffptr += sprintf(buffptr, " %02x", i2c1rxbuffer[i]);
			}
			buffptr += sprintf(buffptr, "\r\n");
			printf("%s", buff);
#endif
			if(transferSize > 500)
			{
				HAL_GPIO_WritePin(DEBUG_PIN, GPIO_PIN_SET);
			}
			HAL_I2C_Master_Transmit_IT(&I2cHandle2, 0xE0, i2c1rxbuffer, transferSize);
			while (HAL_I2C_GetState(&I2cHandle2) != HAL_I2C_STATE_READY)
			{
			}
			if(transferSize > 500)
			{
				HAL_GPIO_WritePin(DEBUG_PIN, GPIO_PIN_RESET);
			}
		}
		
		dataReceived = 0;
		memset(i2c1rxbuffer, 0, sizeof(i2c1rxbuffer));
	}
}

// Called in interrupt context
void dataRequestAsSlaveStart(void)
{
	if(mode == ASK_DATA)
	{
#ifdef VERBOSE
		printf("requesting data\r\n");
#endif
		const uint8_t* buff;
		int transferSize = onTransmit(&buff);
#ifdef VERBOSE
		printf("transmitting data %d\r\n", transferSize);
#endif
		if(HAL_I2C_Slave_Sequential_Transmit_IT(&I2cHandle1, (uint8_t*) buff, transferSize, I2C_FIRST_AND_LAST_FRAME) != HAL_OK)
		{
			Error_Handler();
		}
	}
	else
	{
		HAL_I2C_Master_Receive_IT(&I2cHandle2, I2C1_ADDRESS | 0x1, i2c2rxbuffer, sizeof(i2c2rxbuffer));
#ifdef VERBOSE
		//printf("requesting data\r\n");
#endif
		waitingForSlave = 1;
	}
}

// Called while transfer is in proccess
void dataRequestAsSlaveDuring(void)
{
	if(waitingForSlave)
	{
		while (HAL_I2C_GetState(&I2cHandle2) != HAL_I2C_STATE_READY)
		{
		}
		
		waitingForSlave = 0;
		uint8_t allow_transmission = 1;

		if(onTransmitListen != NULL)
		{
			allow_transmission = onTransmitListen(i2c2rxbuffer);
		}
		
		if(!allow_transmission)
		{
			memset(i2c2rxbuffer, 0, sizeof(i2c2rxbuffer));
		}

		if(HAL_I2C_Slave_Sequential_Transmit_IT(&I2cHandle1, i2c2rxbuffer, sizeof(i2c2rxbuffer), I2C_FIRST_AND_LAST_FRAME) != HAL_OK)
		{
			Error_Handler();
		}
		
#ifdef VERBOSE
		char buff[sizeof(i2c2rxbuffer)*3 + 100];
		char* buffptr = buff;
		buffptr += sprintf(buffptr, "transmitting pass through:");
		for(int i=0; i < sizeof(i2c2rxbuffer); i++)
		{
			buffptr += sprintf(buffptr, " %02x", i2c2rxbuffer[i]);
		}
		buffptr += sprintf(buffptr, "\r\n");
		printf("%s", buff);
#endif
	}
}

// Called after transfer ended
void dataRequestAsSlaveEnd(void)
{
}

void i2cListenOnce(void)
{
	if(HAL_I2C_EnableListen_IT(&I2cHandle1) != HAL_OK)
	{
		Error_Handler();
	}
	
	while(uwTransferInitiated != 1)
	{
		yield();
	}

	while(uwTransferEnded != 1)
	{
		dataReceiveAsSlaveDuring();
		dataRequestAsSlaveDuring();
		yield();
	}
	
	dataReceiveAsSlaveEnd();
	dataRequestAsSlaveEnd();
	
	uwTransferInitiated = 0;
	uwTransferEnded = 0;
}


/**
	* @brief	Slave Address Match callback.
	* @param	hi2c Pointer to a I2C_HandleTypeDef structure that contains
	*								the configuration information for the specified I2C.
	* @param	TransferDirection: Master request Transfer Direction (Write/Read), value of @ref I2C_XferOptions_definition
	* @param	AddrMatchCode: Address Match Code
	* @retval None
	*/
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	if(AddrMatchCode == I2C1_ADDRESS)
	{
		uwTransferInitiated = 1;

		if(TransferDirection == I2C_DIRECTION_TRANSMIT)
		{
			dataReceiveAsSlaveStart();
		}
		else
		{
			dataRequestAsSlaveStart();
		}
	}
	else
	{
		Error_Handler();
	}
}

/**
	* @brief	Listen Complete callback.
	* @param	hi2c Pointer to a I2C_HandleTypeDef structure that contains
	*								the configuration information for the specified I2C.
	* @retval None
	*/
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance == I2C1)
	{
		uwTransferEnded = 1;
	}
}
