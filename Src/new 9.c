/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
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
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "stm32f7xx_hal.h"
#include "spi.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "sensefunc.h"
#include "math.h"
//#include "arm_math.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
#define M_PI    3.14159265358979323846
/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
uint8_t sign(double val);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{
	uint8_t amount=0,a=0x75|0x80,atx[2]={0x75|0x80,0x00},b=0;
	uint8_t buffer[3]={0x55,0x12,0x99};
	uint8_t hal=0x75,rx[2];
	uint16_t k=0;
	int16_t sensor_values[7];//[0]->Ax,[1]->Ay,[2]->Az,[3]->Temp,[4]->Gx,[5]->Gy,[6]->Gz
	uint32_t countervalue=0;
	uint32_t werte=0;
	double Temperatur,cls,roll,pitch,rad_to_deg,Ax,Ay,Az;
	double offset_gyro[3],offset_acc[3],winkel[3],dt,offset_temp;
	//SystemInit();
	cls=(double)32/(double)218000000;
	for(uint8_t i=0;i<3;i++)
	{
	offset_gyro[i]=0;
	winkel[i]=0;	
	}
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
	MX_USART3_UART_Init();
	MX_TIM1_Init();
	int16_t mag_sens[3];
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
	setup_sensor();

//  /* Infinite loop */
//  /* USER CODE BEGIN WHILE */
//	
//		for(k=0;k<1024;k++)
//		{
//		read_sensor(sensor_values);
//		offset_acc[0]+=sensor_values[0];
//		offset_acc[1]+=sensor_values[1];
//		offset_acc[2]+=sensor_values[2];
//		offset_temp+=sensor_values[3];
//		offset_gyro[0]+=sensor_values[4];
//		offset_gyro[1]+=sensor_values[5];
//		offset_gyro[2]+=sensor_values[6];
//		HAL_Delay(1);
//		}
//	offset_acc[0]/=k;
//	offset_acc[1]/=k;
//	offset_acc[2]/=k;	
//	offset_gyro[0]/=k;
//	offset_gyro[1]/=k;
//	offset_gyro[2]/=k;
//	offset_temp/=k;
//	rad_to_deg=180/M_PI;
HAL_Delay(5000);
	HAL_TIM_Base_Start(&htim1);
 while (werte<300000)
 {
	
		//double read_mag_sensor(void)
	__HAL_TIM_SetCounter(&htim1,0);	
	read_sensor(sensor_values);
////		Ax=sensor_values[0]/16384;
////		Ay=sensor_values[1]/16384;
////		Az=sensor_values[2]/16384;
////	
////			
	//Temperatur=(sensor_values[3]-offset_temp)/333.87+21;
	//winkel[0]=0.98* (winkel[0]+((sensor_values[4]-offset_gyro[0]-Temperatur*0.04)/131)*dt)+0.02*rad_to_deg*-atan(sensor_values[2]/(sign(sensor_values[1])*sqrt(sensor_values[0]*sensor_values[0]+sensor_values[1]*sensor_values[1])));
	//winkel[1]+= ((sensor_values[5]-offset_gyro[1]-Temperatur*0.04)/131)*dt;
	//winkel[2]= 0.98*(winkel[2]+((sensor_values[6]-offset_gyro[2]-Temperatur*0.04)/131)*dt)+0.02*rad_to_deg*-atan(-sensor_values[0]/sensor_values[1]);		
//	winkel[0]+=((sensor_values[4])/131)*dt;
//	winkel[1]+=((sensor_values[5])/131)*dt;
//	winkel[2]+=((sensor_values[6])/131)*dt;
	//printf("\r\nstart \n");
	printf("\r\n%i\n",sensor_values[4]);
	printf("\r\n%i\n",sensor_values[5]);
	printf("\r\n%i\n",sensor_values[6]);
	printf("\r\n%i\n",sensor_values[0]);
	printf("\r\n%i\n",sensor_values[1]);
	printf("\r\n%i\n",sensor_values[2]);
	printf("\r\n%f\n",dt); 	
	//printf("\r\dt=%f \n",dt);
	//printf("\r\nend \n");
	//printf("\r\n Temperatur=%f \n",Temperatur);
		//TIM_GetCounter(&htim1);
//		roll= atan(((double)sensor_values[1]/16384)/sqrt(((double)sensor_values[0]/16384)*((double)sensor_values[0]/16384)+((double)sensor_values[3]/16384)*((double)sensor_values[3]/16384)))*rad_to_deg;
//		pitch=atan(((double)-sensor_values[0]/16384)/sqrt(((double)sensor_values[2]/16384)*((double)sensor_values[2]/16384)+((double)sensor_values[1]/16384)*((double)sensor_values[1]/16384)))*rad_to_deg;
//		
//	printf("\r\n roll=%f \n",roll);
//	printf("\r\n pitch=%f \n",pitch);
//	printf("\r\n gx=%f \n",((double)sensor_values[0]/16384));
//	printf("\r\n gy=%f \n",((double)sensor_values[1]/16384));
//	printf("\r\n gz=%f \n",((double)sensor_values[2]/16384));

	
//	

	//HAL_Delay(100);
//


//printf("\r\n Magsense=%x \n",read_mag_sensor(0x00));
			//read_mag_sensor(mag_sens);
//			while(amount<0x13)
//			{
//				HAL_Delay(50);
//		printf("\r\n Adresse=%x    Wert=%i \n",amount,read_mag_sensor(amount));
//				amount++;
//			}
//			amount=0;
//		//printf("\r\n Magsensey=%i \n",mag_sens[1]);
//		printf("\r\n Magsensez=%i \n",mag_sens[2]);
//amount=0;
////printf("\r\n Magsensez=%x Hallo\n",b);
	
	dt=cls*__HAL_TIM_GET_COUNTER(&htim1);
	werte++;
 }


}



uint8_t sign(double val)
{
if(val==0)return 0;
	else
	{
	return val/(sqrt(val*val));
	}

}

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}


/** System Clock Configuration
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
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

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
