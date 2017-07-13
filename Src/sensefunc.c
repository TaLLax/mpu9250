
#include "sensefunc.h"
#include "main.h"
#include "stm32f7xx_hal.h"
#include "spi.h"
#include "gpio.h"

void write_spi(uint8_t *value,uint8_t amount){

	
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);


	HAL_SPI_Transmit(&hspi1, value,amount, 5000);
	//HAL_SPI_Receive(&hspi1, reciev, amount, 5000);

	
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);

}

void read_spi(uint8_t *value){
uint8_t a=0x3b|0x80;
	
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);


	HAL_SPI_Transmit(&hspi1, &a,1, 5000);
	HAL_SPI_Receive(&hspi1, value, 14, 5000);

	
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);

}

void setup_sensor()
{

	uint8_t array[2];	
	
	array[0]=0x6a;
	array[1]=0x60;
	write_spi(array,2);
	HAL_Delay(20);
	
	array[0]=36;
	array[1]=0x89;
	write_spi(array,2);
	HAL_Delay(20);
	
	array[0]=0x6b;
	array[1]=0x00;
	write_spi(array,2);
	HAL_Delay(20);
	
	array[0]=0x6b;
	array[1]=0x01;
	write_spi(array,2);
	HAL_Delay(20);
	
	array[0]=0x1a;
	array[1]=0x00;
	write_spi(array,2);
	HAL_Delay(20);
	
	array[0]=0x19;
	array[1]=0x04;
	write_spi(array,2);
	HAL_Delay(20);
	
	array[0]=0x23;
	array[1]=0xf8;
	write_spi(array,2);
	HAL_Delay(20);
	
	array[0]=0x24;
	array[1]=0x09;
	write_spi(array,2);
	HAL_Delay(20);
	
//	array[0]=0x25;
//	array[1]=0x0C;
//	write_spi(array,2);
//	HAL_Delay(20);
//	
//	array[0]=0x26;
//	array[1]=0x0B;
//	write_spi(array,2);
//	HAL_Delay(20);
//	
//	array[0]=0x27;
//	array[1]=0x81;
//	write_spi(array,2);
//	HAL_Delay(20);
//	
//	array[0]=0x63;
//	array[1]=0x01;
//	write_spi(array,2);
//	HAL_Delay(20);
//		
//  array[0]=0x27;
//	array[1]=0x81;
//	write_spi(array,2);
//	HAL_Delay(500);	
//	
//	array[0]=0x25;
//	array[1]=0x0C;
//	write_spi(array,2);
//	HAL_Delay(20);
//	
//  array[0]=0x26;
//	array[1]=0x0A;
//	write_spi(array,2);
//	HAL_Delay(20);
//  
//	array[0]=0x27;
//	array[1]=0x81;
//	write_spi(array,2);
//	HAL_Delay(20);
//	
//	array[0]=0x63;
//	array[1]=0x12;
//	write_spi(array,2);
//	HAL_Delay(20);
//	   
//  array[0]=0x27;
//	array[1]=0x81;
//	write_spi(array,2);
//	HAL_Delay(20);
		
	
	array[0]=0x1B;
	array[1]=0x03;
	write_spi(array,2);//Gyro Config
	HAL_Delay(20);
	
	array[0]=0x1C;
	array[1]=0x00;
	write_spi(array,2); //ACC Config
	HAL_Delay(20);
	
	array[0]=0x1D;
	array[1]=0x2;
	write_spi(array,2); //ACC2 Config
	HAL_Delay(20);
	
	array[0]=0x37;
	array[1]=0x22;
	write_spi(array,2); //Int_Pin_Cfg 
	HAL_Delay(20);
	
	array[0]=0x38;
	array[1]=0x01;
	write_spi(array,2); //Int_Enable 
	HAL_Delay(20);

}


void read_sensor(int16_t *values)
{

uint8_t arry[16],n,x=0;
read_spi(arry);

	for(n=0;n<14;n+=2)
		{
		values[x]=(int16_t)((arry[n] << 8) | arry[n+1]);
		x++;			
		}	
	
	}
	
uint8_t read_mag_sensor(uint8_t address)
{
uint8_t b=0,array[2];
	

	uint8_t a=0,i;
	uint8_t datenwerte[24];
	

array[0]=0x25;
array[1]=0x0c|0x80;
write_spi(array,2);
HAL_Delay(100);	
	
array[0]=0x26;
array[1]=address;
write_spi(array,2);
HAL_Delay(100);		
	
array[0]=0x27;
array[1]=0x81;
write_spi(array,2);
HAL_Delay(100);		

a=0x49|0x80;
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);


	HAL_SPI_Transmit(&hspi1,&a,1, 5000);
	
	HAL_SPI_Receive(&hspi1,&b,1, 5000);
	
	
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
//HAL_Delay(100);
//printf("\r\n datenwerte=%i \n",datenwerte[0]);
//printf("\r\n datenwerte=%i \n",datenwerte[1]);
//printf("\r\n datenwerte=%i \n",datenwerte[2]);
//printf("\r\n datenwerte=%i \n",datenwerte[3]);
//printf("\r\n datenwerte=%i \n",datenwerte[4]);
//printf("\r\n datenwerte=%i \n",datenwerte[5]);
//printf("\r\n datenwerte=%i \n",datenwerte[6]);
return b;


}
