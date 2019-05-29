
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */

#include <string.h>
#include "cc_commands.h"
#include "cc_definitions.h"
#include "ax25.h"
//#include "log.h"
#include "cc112x_spi.h"
#include "cc_tx_init.h"
/*
#include "cc_rx_init.h"
#include "comms.h"
#include "pkt_pool.h"
#include "service_utilities.h"
*/
#include "comms_manager.h"
#include "stm32f4xx_hal_iwdg.h"

#include "config.h"
#include "utils.h"
/*
#include "sensors.h"
#include "stats.h"
#include "sysview.h"
#include "sha256.h"
#include "persistent_mem.h"
*/
#include "mxconstants.h"
#include "stm32f4xx_hal_uart.h"
#include "upsat.h"


/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
IWDG_HandleTypeDef hiwdg;
UART_HandleTypeDef huart5;
SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_uart5_tx;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t res;
uint16_t size = 0;

volatile uint8_t tx_thr_flag = 0;
volatile uint8_t tx_fin_flag = 0;
volatile uint8_t rx_sync_flag = 0;
volatile uint8_t rx_finished_flag = 0;
volatile uint8_t rx_thr_flag = 0;

uint8_t uart_temp[512];
uint8_t debug_temp[256];

// extern comms_rf_stat_t comms_stats;



// =================================================================================
// Cette variable gobale permet d'activer l'envoi du code morse (activerCW = 1).
// L'envoi des données AX.25 va alterner avec l'envoi du code morse.
// Si activerCW = 0, seules les données AX.25 sont envoyées.
// =================================================================================
uint8_t activerCW = 1;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_IWDG_Init(void);
static void MX_UART5_Init(void);


/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init_suite(GPIO_InitTypeDef *GPIO_InitStruct);

void testCommunicationUART();

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  uint8_t myBuf[100] = "Hello World \r\n"; // Utilisé pour la communication USB

  uint32_t compteurIteration = 0;  // Utilisé pour compter le nombre d'itérations dans la boucle while

  uint8_t rst_src;
  uint32_t tick;
  uint32_t heartbeat_tick;
  comms_tx_job_list_t tx_jobs;
  uint32_t now;
  uint32_t tx_job_cnt = 0;
  uint32_t tx_job_desc = __COMMS_DEFAULT_HEADLESS_TX_PATTERN;

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();
  MX_IWDG_Init();
  MX_UART5_Init();


  /* USER CODE BEGIN 2 */


  // Reset Pin
  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, GPIO_PIN_SET);	// Nouvelle pin reset

/*
  // Allumer la LED bleue pour fins de test
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);

   TX Pins RESETN_TX, PA_CTRL_PIN, CSN1
  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, GPIO_PIN_SET);	// Nouvelle pin reset
  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_10, GPIO_PIN_SET);	// Ancienne pin reset (ne fonctionne pas sur le microcontrolleur)

  // HAL_GPIO_WritePin (PA_CNTRL_GPIO_Port, PA_CNTRL_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_15, GPIO_PIN_SET);

   RX Pins RESETN_RX, CSN2
  HAL_GPIO_WritePin (GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
  HAL_GPIO_WritePin (GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
*/

  /*Start the watchdog ASAP */

  // Debug
  //HAL_IWDG_Start(&hiwdg);


  /*Must use this in order the compiler occupies flash sector 3*/
  // Comment Add, to remove error
  //comms_persistent_mem_init();

  /* Initialize the systemview */
  // Comment Add, to remove error
/*  SEGGER_SYSVIEW_Conf();
  sysview_init();*/

  /*Make all the proper initializations for the COMMS */
  comms_init();

   /* UART initializations */
   // Comment Add to remove error
 //  HAL_UART_Receive_IT (&huart5, comms_data.obc_uart.uart_buf, UART_BUF_SIZE);

   /* Get the reason of re-booting */
   // Comment Add to remove error
   //HAL_reset_source(&rst_src);
   // comms_rf_stats_set_reset_src(&comms_stats, rst_src); READD
   /* USER CODE END 2 */

   /* Infinite loop */
   /* USER CODE BEGIN WHILE */

   tick = HAL_GetTick();
   heartbeat_tick = tick;
   memset((void *)&tx_jobs, 0, sizeof(comms_tx_job_list_t));


   // ============================================================================
   // Enlever le commentaire pour tester la réception sur UART.
   // Todo Il manque du code...
   // testCommunicationUART();

   while (1)
   {

 	  // Envoi du numero de l'iteration sur le port USB
 	  	sprintf(myBuf,"Iteration %ld; now: %ld", compteurIteration, now);
 	  	strcat(myBuf, "\r\n");
 	  	sendOverUSB(myBuf);

 	  	      now = HAL_GetTick();
 	  	      /* Sent a heartbeat message to the EPS*/
 	  	      if(now < heartbeat_tick
 	  	  	|| now - heartbeat_tick > __HEARTBEAT_EPS_INTERVAL_MS){
 	  	        heartbeat_tick = now;
 	  	        // Comment Add to remove error
 	  	        /*SYSVIEW_PRINT("HEARTBEAT to EPS");
 	  	        sys_refresh();*/
 	  	      }

 	  	      if(now - tick > __TX_INTERVAL_MS){

 	  	        /*
 	  	         * Check which type of TX job should be performed. At this time any
 	  	         * previous unfinished TX jobs are dropped.
 	  	         */

 	  	        // Turn on blue LED for test purposes
 	  	        //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);

 	  	        memset((void *)&tx_jobs, 0, sizeof(comms_tx_job_list_t));
 	  	        tick = now;

 	  	        /* Zero ID always refer to CW beacon */
 	  	        if((tx_job_cnt % 2) == 0) {
 	  	  	/* Should be reset from comms_routine_dispatcher() when served */
 	  	  	tx_jobs.tx_cw = 1;
 	  	        }
 	  	        else{
 	  	  	/*An active bit means ex_WOD whereas an inactive a WOD */
 	  	  	if((tx_job_desc >> tx_job_cnt) & 0x1){

 	  	  	  // Pour l'instant, seulement transmettre sur WOD
 	  	  	  tx_jobs.tx_wod = 1;
 	  	  	}
 	  	  	else{
 	  	  	  tx_jobs.tx_wod = 1;
 	  	  	}
 	  	        }

 	  	        tx_job_cnt++;	// Commente pour toujours demeurer dans le mode CW
 	  	        tx_job_cnt = tx_job_cnt % 8;
 	  	        /*
 	  	         * Now it's a good time to re-read the flash, in case the
 	  	         * headless transmission scheme altered
 	  	         */

 	  	        // Comment Add to remove error
 	  	        // tx_job_desc = comms_read_persistent_word(__COMMS_HEADLESS_TX_FLASH_OFFSET);

 	  	        /*
 	  	         * In case the ex_WOD number is greater than the WOD, shit happened.
 	  	         * So fall back to the default
 	  	         */
 	  	        if(bit_count(tx_job_desc) > 4){
 	  	  	tx_job_desc = __COMMS_DEFAULT_HEADLESS_TX_PATTERN;
 	  	        }
 	  	      }

 	  	      comms_routine_dispatcher(&tx_jobs);

 	  	 // Compte du nombre d'iterations dans la boucle while
 	  	 compteurIteration = compteurIteration + 1;

 	    /* USER CODE BEGIN 3 */

 	    }
 	    /* USER CODE END 3 */

 }


void testCommunicationUART()
{

	while(1)
	{

		HAL_StatusTypeDef status;

		uint8_t uart_buf[256] = {0};
		status = HAL_UART_Receive_IT (&huart5, uart_buf, UART_BUF_SIZE);

		HAL_Delay(1000);
	}
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* IWDG init function */
static void MX_IWDG_Init(void)
{

  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */

#include "stm32f4xx_hal_uart.h"

static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */


  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 9600;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}


/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

  HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin : PF0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN 10 */
  // Ajout de configurations qui ne sont pas faites par CubeMX
  MX_GPIO_Init_suite(&GPIO_InitStruct);
  /* USER CODE END 10 */

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

static void MX_GPIO_Init_suite(GPIO_InitTypeDef *GPIO_InitStruct)
{
	/*Configure pins for SPI */
	      GPIO_InitStruct->Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	      GPIO_InitStruct->Mode = GPIO_MODE_AF_PP;
	      GPIO_InitStruct->Pull = GPIO_PULLUP;
	      GPIO_InitStruct->Speed = GPIO_SPEED_HIGH;
	      GPIO_InitStruct->Alternate = GPIO_AF5_SPI1;
	      HAL_GPIO_Init(GPIOA, GPIO_InitStruct);

	      // Configure GPIO pin : PA15
	         GPIO_InitStruct->Pin = GPIO_PIN_15;
	         GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;

	         HAL_GPIO_Init(GPIOA, GPIO_InitStruct);

	         // Reset Pin
	         // Configure GPIO pin : PA1
	              GPIO_InitStruct->Pin = GPIO_PIN_1;
	              GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	              GPIO_InitStruct->Pull = GPIO_PULLUP;
	              GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	              HAL_GPIO_Init(GPIOA, GPIO_InitStruct);
}






/* USER CODE BEGIN 4 */


void
HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin)
{
  GPIO_PinState state;
  switch(GPIO_Pin){
    case GPIO_PIN_3:
      tx_thr_flag = 1;
      break;
    case GPIO_PIN_2:
      tx_fin_flag = 1;
      break;
    case CC_GPIO2_START_END_OF_PACKET_Pin:
      state = HAL_GPIO_ReadPin (CC_GPIO2_START_END_OF_PACKET_GPIO_Port,
				CC_GPIO2_START_END_OF_PACKET_Pin);
      if(state){
	rx_sync_flag = 1;
      }
      else {
	rx_finished_flag = 1;
      }
      break;
    case CC_GPIO0_RXFIFO_THR_Pin:
      rx_thr_flag = 1;
      break;
  }
}


// Add 2
// Called when something is received over USB
void CDC_ReceiveCallBack(uint8_t *buf, uint32_t len)
{
	CDC_Transmit_FS(buf, len);	// Data echoed back to the transmitter
	//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);	// Toggle blue LED to show that data has been received
}







/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
