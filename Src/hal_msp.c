#include "main.h"

/**
* @brief UART MSP Init
* @param huart: uart handle
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef	GPIO_InitStruct;

	/* USART2 Configuration */
	if(huart->Instance == USART2)
	{
		/* Enable UART2 GPIO TX/RX clock */
		__HAL_RCC_GPIOA_CLK_ENABLE();

		/* Enable USART2 clock */
		__HAL_RCC_USART2_CLK_ENABLE();

		/* Configure USART2 Rx as alternate function	*/
		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* Configure USART2 Tx as alternate function	*/
		GPIO_InitStruct.Pin = GPIO_PIN_15;
		GPIO_InitStruct.Alternate = GPIO_AF3_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* Enable and set USART2 Interrupt to the highest priority */
		HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
	}
}


/**
	* @brief I2C MSP Initialization
	*				This function configures the hardware resources used in this example:
	*					 - Peripheral's clock enable
	*					 - Peripheral's GPIO Configuration
	*					 - DMA configuration for transmission request by peripheral
	*					 - NVIC configuration for DMA interrupt request enable
	* @param hi2c: I2C handle pointer
	* @retval None
	*/
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	RCC_PeriphCLKInitTypeDef	RCC_PeriphCLKInitStruct;

	if(hi2c->Instance == I2C1)
	{
		/*##-1- Configure the I2C clock source. The clock is derived from the SYSCLK #*/
		RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
		RCC_PeriphCLKInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
		HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);

		/*##-2- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		I2C1_SCL_GPIO_CLK_ENABLE();
		I2C1_SDA_GPIO_CLK_ENABLE();
		/* Enable I2Cx clock */
		I2C1_CLK_ENABLE(); 

		/*##-3- Configure peripheral GPIO ##########################################*/
		/* I2C TX GPIO pin configuration	*/
		GPIO_InitStruct.Pin			 = I2C1_SCL_PIN;
		GPIO_InitStruct.Mode			= GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull			= GPIO_PULLUP;
		GPIO_InitStruct.Speed		 = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = I2C1_SCL_SDA_AF;
		HAL_GPIO_Init(I2C1_SCL_GPIO_PORT, &GPIO_InitStruct);
			
		/* I2C RX GPIO pin configuration	*/
		GPIO_InitStruct.Pin			 = I2C1_SDA_PIN;
		GPIO_InitStruct.Alternate = I2C1_SCL_SDA_AF;
		HAL_GPIO_Init(I2C1_SDA_GPIO_PORT, &GPIO_InitStruct);
			
		/*##-4- Configure the NVIC for I2C ########################################*/
		/* NVIC for I2Cx */
		HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
		HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 2);
		HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
	}
	else
	{
		/*##-1- Configure the I2C clock source. The clock is derived from the SYSCLK #*/
		RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C3;
		RCC_PeriphCLKInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_SYSCLK;
		HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);

		/*##-2- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		I2C3_SCL_GPIO_CLK_ENABLE();
		I2C3_SDA_GPIO_CLK_ENABLE();
		/* Enable I2Cx clock */
		I2C3_CLK_ENABLE(); 

		/*##-3- Configure peripheral GPIO ##########################################*/
		/* I2C TX GPIO pin configuration	*/
		GPIO_InitStruct.Pin			 = I2C3_SCL_PIN;
		GPIO_InitStruct.Mode			= GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull			= GPIO_PULLUP;
		GPIO_InitStruct.Speed		 = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = I2C3_SCL_SDA_AF;
		HAL_GPIO_Init(I2C3_SCL_GPIO_PORT, &GPIO_InitStruct);
			
		/* I2C RX GPIO pin configuration	*/
		GPIO_InitStruct.Pin			 = I2C3_SDA_PIN;
		GPIO_InitStruct.Alternate = I2C3_SCL_SDA_AF;
		HAL_GPIO_Init(I2C3_SDA_GPIO_PORT, &GPIO_InitStruct);
			
		/*##-4- Configure the NVIC for I2C ########################################*/
		/* NVIC for I2Cx */
		HAL_NVIC_SetPriority(I2C3_ER_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
		HAL_NVIC_SetPriority(I2C3_EV_IRQn, 0, 2);
		HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
	}
}

/**
	* @brief I2C MSP De-Initialization
	*				This function frees the hardware resources used in this example:
	*					- Disable the Peripheral's clock
	*					- Revert GPIO, DMA and NVIC configuration to their default state
	* @param hi2c: I2C handle pointer
	* @retval None
	*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance == I2C1)
	{
		/*##-1- Reset peripherals ##################################################*/
		I2C1_FORCE_RESET();
		I2C1_RELEASE_RESET();

		/*##-2- Disable peripherals and GPIO Clocks #################################*/
		/* Configure I2C Tx as alternate function	*/
		HAL_GPIO_DeInit(I2C1_SCL_GPIO_PORT, I2C1_SCL_PIN);
		/* Configure I2C Rx as alternate function	*/
		HAL_GPIO_DeInit(I2C1_SDA_GPIO_PORT, I2C1_SDA_PIN);
		
		/*##-3- Disable the NVIC for I2C ##########################################*/
		HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
		HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
	}
	else
	{
		/*##-1- Reset peripherals ##################################################*/
		I2C3_FORCE_RESET();
		I2C3_RELEASE_RESET();

		/*##-2- Disable peripherals and GPIO Clocks #################################*/
		/* Configure I2C Tx as alternate function	*/
		HAL_GPIO_DeInit(I2C3_SCL_GPIO_PORT, I2C3_SCL_PIN);
		/* Configure I2C Rx as alternate function	*/
		HAL_GPIO_DeInit(I2C3_SDA_GPIO_PORT, I2C3_SDA_PIN);
		
		/*##-3- Disable the NVIC for I2C ##########################################*/
		HAL_NVIC_DisableIRQ(I2C3_ER_IRQn);
		HAL_NVIC_DisableIRQ(I2C3_EV_IRQn);
	}
}
