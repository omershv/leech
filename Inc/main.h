/**
	******************************************************************************
	* @file		I2C/I2C_TwoBoards_ComIT/Inc/main.h
	* @author	MCD Application Team
	* @version V1.6.0
	* @date		28-October-2016
	* @brief	 Header for main.c module
	******************************************************************************
	* @attention
	*
	* <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
	*
	* Redistribution and use in source and binary forms, with or without modification,
	* are permitted provided that the following conditions are met:
	*	 1. Redistributions of source code must retain the above copyright notice,
	*			this list of conditions and the following disclaimer.
	*	 2. Redistributions in binary form must reproduce the above copyright notice,
	*			this list of conditions and the following disclaimer in the documentation
	*			and/or other materials provided with the distribution.
	*	 3. Neither the name of STMicroelectronics nor the names of its contributors
	*			may be used to endorse or promote products derived from this software
	*			without specific prior written permission.
	*
	* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	*
	******************************************************************************
	*/

#ifndef __MAIN_H
#define __MAIN_H

#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo_32.h"
#include <string.h>

//#define VERBOSE

#define I2C1_CLK_ENABLE()							 __HAL_RCC_I2C1_CLK_ENABLE()
#define I2C1_SDA_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C1_SCL_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOB_CLK_ENABLE()

#define I2C3_CLK_ENABLE()							 __HAL_RCC_I2C3_CLK_ENABLE()
#define I2C3_SDA_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C3_SCL_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOA_CLK_ENABLE()

#define I2C1_FORCE_RESET()							__HAL_RCC_I2C1_FORCE_RESET()
#define I2C1_RELEASE_RESET()						__HAL_RCC_I2C1_RELEASE_RESET()

#define I2C3_FORCE_RESET()							__HAL_RCC_I2C3_FORCE_RESET()
#define I2C3_RELEASE_RESET()						__HAL_RCC_I2C3_RELEASE_RESET()

#define I2C1_SCL_PIN								GPIO_PIN_6
#define I2C1_SCL_GPIO_PORT							GPIOB
#define I2C1_SDA_PIN								GPIO_PIN_7
#define I2C1_SDA_GPIO_PORT							GPIOB
#define I2C1_SCL_SDA_AF								GPIO_AF4_I2C1

#define I2C3_SCL_PIN								GPIO_PIN_7
#define I2C3_SCL_GPIO_PORT							GPIOA
#define I2C3_SDA_PIN								GPIO_PIN_4
#define I2C3_SDA_GPIO_PORT							GPIOB
#define I2C3_SCL_SDA_AF								GPIO_AF4_I2C2


#define I2C_TIMING_400 0x10D1143A /* 400khz Analog Filter ON, Rise time 250ns, Fall Time 100ns */
#define I2C_TIMING_100 0x30C14E6B // 100khz
//#define I2C_TIMING			0x00D00E28 // 1mbit?
#define I2C1_ADDRESS				0xE0
#define I2C3_ADDRESS				0xE0


#define DEBUG_PIN_PIN GPIO_PIN_1
#define DEBUG_PIN_PORT GPIOB
#define DEBUG_PIN GPIOB, GPIO_PIN_1

#define INTERRUPT_IN_PIN GPIO_PIN_8
#define INTERRUPT_IN_PORT GPIOA
#define INTERRUPT_IN GPIOA, GPIO_PIN_8

#define INTERRUPT_OUT_PIN GPIO_PIN_11
#define INTERRUPT_OUT_PORT GPIOA
#define INTERRUPT_OUT GPIOA, GPIO_PIN_11

#define ERR 	printf("%s %d error\r\n", __FUNCTION__, __LINE__);

typedef enum I2cModes
{
	PASS_THROUGH = 1,
	ASK_DATA = 2
} I2cModes;

typedef void (*receiveFuncType)(const uint8_t*, int);
typedef int (*transmitFuncType)(const uint8_t**);
typedef uint8_t (*transmitListenFuncType)(const uint8_t*);
typedef void (*yieldFuncType)(void);
typedef void (*memoryWriteFuncType)(int, const uint8_t);
typedef int (*memoryReadFuncType)(int, const uint8_t**);
typedef uint8_t (*memoryReadListenFuncType)(int, const uint8_t*);

	
void SystemClock_Config(void);
void Error_Handler(void);
void USART2_Config(void);
void GPIO_Config(void);
void I2C_Config(void);
void i2cListenOnce(void);
void setI2cMode(I2cModes newMode);
void setOnReceive(receiveFuncType);
void setOnTransmit(transmitFuncType);
void setOnTransmitListen(transmitListenFuncType);
void setYield(yieldFuncType);

void init_exploit(void);
void destroy_exploit(void);
void exploitLoopActions(void);

void init_injector();
void destroy_injector();
void setOnWrite(memoryWriteFuncType f);
void setOnRead(memoryReadFuncType f);
void setOnReadListen(memoryReadListenFuncType f);
void initI2cMemAux(I2cModes mode);
uint8_t base_injector_is_injection_complete();


void init_logger();
void destroy_logger();
uint8_t isLoggingCompleted();
void loggerMemWrite(int addr, const uint8_t c);
uint8_t loggerMemRead(int addr, const uint8_t* buff);

static void inline interruptStart()
{
	//printf("%s %d\r\n",__FUNCTION__, __LINE__);
	HAL_GPIO_WritePin(INTERRUPT_OUT, GPIO_PIN_RESET);
#ifdef VERBOSE
	printf("%s %d\r\n",__FUNCTION__, __LINE__);
#endif
}

static void inline interruptStop()
{
	HAL_GPIO_WritePin(INTERRUPT_OUT, GPIO_PIN_SET);
#ifdef VERBOSE
	printf("%s %d\r\n",__FUNCTION__, __LINE__);
#endif
}

static void inline interruptMirror()
{
	HAL_GPIO_WritePin(INTERRUPT_OUT, HAL_GPIO_ReadPin(INTERRUPT_IN));
}



extern UART_HandleTypeDef UARTHandle;
extern GPIO_InitTypeDef GPIO_InitStruct;
extern I2C_HandleTypeDef I2cHandle1;
extern I2C_HandleTypeDef I2cHandle2;


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
