#include <stm32f2xx.h>

int main()
{
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

	GPIOE.MODER = GPIO_ODR_ODR_5;

//	GPIOE.MODER = GPIO_Pin_5;

//	IS_GPIO_PIN(GPIO_Pin_5);

//	IS_GET_GPIO_PIN(GPIO_Pin_5);
//	GPIO_Init();
//	GPIO_Write();
//	GPIO_ReadInputDataBit();
//	GPIO_SetBits();
}

