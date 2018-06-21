#include "main.h"

UART_HandleTypeDef UARTHandle;
GPIO_InitTypeDef	GPIO_InitStruct;
I2C_HandleTypeDef I2cHandle1;
I2C_HandleTypeDef I2cHandle2;

	
/**
	* @brief	System Clock Configuration
	*				 The system Clock is configured as follows :
	*						System Clock source						= PLL (MSI)
	*						SYSCLK(Hz)										 = 80000000
	*						HCLK(Hz)											 = 80000000
	*						AHB Prescaler									= 1
	*						APB1 Prescaler								 = 1
	*						APB2 Prescaler								 = 1
	*						MSI Frequency(Hz)							= 4000000
	*						PLL_M													= 1
	*						PLL_N													= 40
	*						PLL_R													= 2
	*						PLL_P													= 7
	*						PLL_Q													= 4
	*						Flash Latency(WS)							= 4
	* @param	None
	* @retval None
	*/
void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};

	/* MSI is enabled after System reset, activate PLL with MSI as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 40;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLP = 7;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		while(1);
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
		 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		/* Initialization Error */
		while(1);
	}
}

#ifdef __GNUC__
	/* With GCC, small printf (option LD Linker->Libraries->Small printf
		 set to 'Yes') calls __io_putchar() */
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
* @brief	Retargets the C library printf function to the UART.
* @param	None
* @retval None
*/
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
	HAL_UART_Transmit(&UARTHandle, (uint8_t *)&ch, 1, 0xFFFF);

	return ch;
}

int _write(int fd, char *str, int len)
{
	for(int i=0; i < len; i++)
	{
		HAL_UART_Transmit(&UARTHandle, (uint8_t *)(str + i), 1, 0xFFFF);
	}
	return len;
}

void USART2_Config(void)
{
	UARTHandle.Instance = USART2;
	UARTHandle.Init.BaudRate = 115200;
	UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UARTHandle.Init.StopBits = UART_STOPBITS_1;
	UARTHandle.Init.Parity = UART_PARITY_NONE;
	UARTHandle.Init.HwFlowCtl	= UART_HWCONTROL_NONE;
	UARTHandle.Init.Mode = UART_MODE_TX_RX;
	UARTHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	UARTHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;

	if(HAL_UART_Init(&UARTHandle) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}

void GPIO_Config(void)
{
	__GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pin = DEBUG_PIN_PIN;
	HAL_GPIO_Init(DEBUG_PIN_PORT, &GPIO_InitStruct);
	
	__GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Mode	= GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pin = INTERRUPT_IN_PIN;
	HAL_GPIO_Init(INTERRUPT_IN_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pin = INTERRUPT_OUT_PIN;
	HAL_GPIO_Init(INTERRUPT_OUT_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(DEBUG_PIN, GPIO_PIN_RESET);
	#if 0
	
	#define SCLPORT GPIOB
#define SDAPORT GPIOB

#define SCLPIN GPIO_PIN_6
#define SDAPIN GPIO_PIN_7

	__GPIOB_CLK_ENABLE();
	
	GPIO_InitStruct.Mode	= GPIO_MODE_IT_RISING /*GPIO_MODE_INPUT*/;
	GPIO_InitStruct.Pull	= GPIO_PULLUP /*GPIO_NOPULL*/;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pin = SCLPIN;
	HAL_GPIO_Init(SCLPORT, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.Mode	= GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull	= GPIO_PULLUP /*GPIO_NOPULL*/;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pin = SDAPIN;
	HAL_GPIO_Init(SDAPORT, &GPIO_InitStruct);
	

	
	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	#endif
}


void I2C_Config(void)
{
	I2cHandle1.Instance						 = I2C1;
	I2cHandle1.Init.Timing					= I2C_TIMING_400;
	I2cHandle1.Init.OwnAddress1		 = I2C1_ADDRESS;
	I2cHandle1.Init.AddressingMode	= I2C_ADDRESSINGMODE_7BIT;
	I2cHandle1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2cHandle1.Init.OwnAddress2		 = 0xFF;
	I2cHandle1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2cHandle1.Init.NoStretchMode	 = I2C_NOSTRETCH_DISABLE;

	if(HAL_I2C_Init(&I2cHandle1) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/* Enable the Analog I2C Filter */
	HAL_I2CEx_ConfigAnalogFilter(&I2cHandle1,I2C_ANALOGFILTER_ENABLE);

	I2cHandle2.Instance						 = I2C3;
	I2cHandle2.Init.Timing					= I2C_TIMING_400;
	I2cHandle2.Init.OwnAddress1		 = I2C3_ADDRESS;
	I2cHandle2.Init.AddressingMode	= I2C_ADDRESSINGMODE_7BIT;
	I2cHandle2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2cHandle2.Init.OwnAddress2		 = 0xFF;
	I2cHandle2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2cHandle2.Init.NoStretchMode	 = I2C_NOSTRETCH_DISABLE;
	
	if(HAL_I2C_Init(&I2cHandle2) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_I2CEx_ConfigAnalogFilter(&I2cHandle2,I2C_ANALOGFILTER_ENABLE);
}


/**
	* @brief	I2C error callbacks.
	* @param	I2cHandle: I2C handle
	* @note	 This example shows a simple way to report transfer error, and you can
	*				 add your own implementation.
	* @retval None
	*/
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
	/** Error_Handler() function is called when error occurs.
		* 1- When Slave don't acknowledge it's address, Master restarts communication.
		* 2- When Master don't acknowledge the last data transferred, Slave don't care in this example.
		*/
	if (HAL_I2C_GetError(I2cHandle) != HAL_I2C_ERROR_AF)
	{
		Error_Handler();
	}
}
