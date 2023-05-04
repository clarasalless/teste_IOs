/**
  ******************************************************************************
  * @file    teste_IO.c
  * @author  Clara Luz Salles Cavalcante
  * 		 Danilo Mota Alencar Filho
  * @brief   O objetivo deste arquivo é testar a funcionalidade
  * 		 de entradas e saídas digitais do dispositivo.
  *
  ******************************************************************************/



/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f3xx_hal.h"

/**
  * @brief  Inicializa o clock do GPIOx especificado.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @retval None
  */
void CLKEnable(GPIO_TypeDef* GPIOx)
{
	if(GPIOx == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	if(GPIOx == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	if(GPIOx == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	if(GPIOx == GPIOD)
		__HAL_RCC_GPIOD_CLK_ENABLE();
	if(GPIOx == GPIOF)
		__HAL_RCC_GPIOF_CLK_ENABLE();
}

/**
  * @brief  Inicializa GPIOx especificado como saída em modo 'Output Push Pull',
  * 		sem resistores de pull-up/pull down e velocidade máxima de saída alta.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @param  GPIO_Pin especifica o pino a ser inicializado.
  * @retval None
  */
void initOutput(GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_Pin_out;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOout, &GPIO_InitStruct);
}

/**
  * @brief  Inicializa GPIOx especificado como saída em modo 'Input',
  * 		sem resistores de pull-up/pull down.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @param  GPIO_Pin especifica o pino a ser inicializado.
  * @retval None
  */
void initInput(GPIO_TypeDef* GPIOin, uint16_t GPIO_Pin_in)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = GPIO_Pin_in;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOin, &GPIO_InitStruct);
}

/**
  * @brief  Deinicializa o pino do GPIO especificado.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @param  GPIO_Pin especifica o pino a ser deinicializado.
  * @retval None
  */
void DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin){
	HAL_GPIO_DeInit(GPIOx,GPIO_Pin);
}

/**
  * @brief  Realiza a leitura do pino de entrada especificado.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @param  GPIO_Pin especifica o pino a ser lido.
  * @retval O valor lido no pino de entrada.
  */
GPIO_PinState read_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	return HAL_GPIO_ReadPin(GPIOx,GPIO_Pin);
}

/**
  * @brief  Determina um valor para o bit do pino especificado.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @param  GPIO_Pin especifica o pino a ser escrito.
  * @param  PinState especifica o valor a ser escrito no bit.
  * 		GPIO_PIN_RESET: escreve 0 no bit
  * 		GPIO_PIN_SET: escreve 1
  * @retval None.
  */
void write_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,GPIO_PinState PinState){
	HAL_GPIO_WritePin(GPIOx,GPIO_Pin,PinState);
}

/**
  * @brief  Inverte valor do o bit do pino especificado.
  * @param  GPIOx, onde x pode ser (A..F), para selecionar qual GPIO será utilizado.
  * @param  GPIO_Pin especifica o pino a ser invertido.
  * @retval None.
  */
void toggle_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	HAL_GPIO_TogglePin(GPIOx,GPIO_Pin);
}

/**
  * @brief  Gera um delay preciso em milisegundos.
  * @param  Delay especifica o tempo de delay, em milisegundos.
  * @retval None.
  */
void delay(uint32_t Delay){
	HAL_Delay(Delay);
}

/**
  * @brief  A função repete a leitura do pino de entrada, mantendo um pino de
  * 		saída em estado HIGH, até que haja uma elevação do nível lógico do
  * 		sinal de LOW para HIGH na entrada, invertendo o nível lógico no pino de saída.
  * @param  GPIOin é a porta que recebe o sinal de entrada.
  * @param  GPIO_Pin_in especifica o pino que recebe a entrada.
  * @param  GPIOout é a porta que gera o sinal de saída.
  * @param  GPIO_Pin_out especifica o pino de saída.
  * @retval None
  */
void inputTC(GPIO_TypeDef* GPIOin, uint16_t GPIO_Pin_in, GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out)
{
	//Ativação dos pinos utilizados no teste
	initInput(GPIOin,GPIO_Pin_in);
	initOutput(GPIOout,GPIO_Pin_out);

	//Rotina do teste de verificação da tensão de operaçãodo pino de input
	while(read_pin(GPIOin, GPIO_Pin_in) == 0)
	{
		write_pin(GPIOout, GPIO_Pin_out, GPIO_PIN_SET);
	}
	write_pin(GPIOout, GPIO_Pin_out, GPIO_PIN_RESET); //O teste não denota um valor exato da tensão mínima de operação do pino.

	//Desativação dos pinos
	DeInit(GPIOin, GPIO_Pin_in);
	DeInit(GPIOout, GPIO_Pin_out);
}

/**
  * @brief  A função recebe um parâmetro que define o nível lógico do pino de saída,
  * 		mantendo-o nesse estado por 5 segundos.
  * @param  GPIOout é a porta que gera o sinal de saída.
  * @param  GPIO_Pin_out especifica o pino de saída.
  * @param  logic define o nível lógico para 1 = HIGH e 0 = LOW.
  * @retval None
  */
void outputTC(GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out, int logic)
{
	//Ativação do pino de output para o teste
	initOutput(GPIOout, GPIO_Pin_out);

	//Quando o parâmetro "logic" for igual a 1, o teste realizado será da medição em nível lógico alto.
	if(logic == 1)
		write_pin(GPIOout, GPIO_Pin_out, GPIO_PIN_SET);
	//Quando o parâmetro "logic" for igual a 0, o teste realizado será da medição em nível lógico baixo.
	else if(logic == 0)
		write_pin(GPIOout, GPIO_Pin_out, GPIO_PIN_RESET);

	delay(5000);

	//Desativação do pino
	DeInit(GPIOout, GPIO_Pin_out);
}

/**
  * @brief  Recebe um sinal quadrado como entrada e gera um sinal similar em um pino de saída.
  * @param  GPIOin é a porta que recebe o sinal de entrada.
  * @param  GPIO_Pin_in especifica o pino que recebe a entrada.
  * @param  GPIOout é a porta que gera o sinal de saída.
  * @param  GPIO_Pin_out especifica o pino de saída.
  * @retval None
  */
void testeInput(GPIO_TypeDef* GPIOin, uint16_t GPIO_Pin_in, GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out)
{
	/*Inicialização dos GPIOs*/
	initInput(GPIOin, GPIO_Pin_in);
	initOutput(GPIOout, GPIO_Pin_out);

	/*O laço faz 1000 iterações, verifica o estado lógico da entrada e gera o sinal de saída*/
	for(int i = 0; i < 1000; i++)
	{
		if(read_pin(GPIOin, GPIO_Pin_in) == 1)
			/*Quando o sinal de entrada estiver em HIGH o valor na saída também é HIGH*/
			write_pin(GPIOout, GPIO_Pin_out, GPIO_PIN_SET);
		else if(read_pin(GPIOin, GPIO_Pin_in) == 0)
			/*Quando o sinal de entrada estiver em LOW o valor na saída também é LOW*/
			write_pin(GPIOout, GPIO_Pin_out, GPIO_PIN_RESET);
	}

	/*Desativação dos GPIOs*/
	DeInit(GPIOin, GPIO_Pin_in);
	DeInit(GPIOout, GPIO_Pin_out);
}

/**
  * @brief  A função gera uma onda quadrada em um pino de saída.
  * @param  GPIOout é a porta que gera o sinal de saída.
  * @param  GPIO_Pin_out especifica o pino de saída.
  * @retval None
  */
void testeOutput(GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out)
{
	/*Inicialização dos GPIOs*/
	initOutput(GPIOout, GPIO_Pin_out);

	/*O laço faz 1000 iterações, e varia o estado lógico do pino de saída*/
	for(int i = 0; i < 1000; i++)
		toggle_pin(GPIOout, GPIO_Pin_out);

	/*Desativação dos GPIOs*/
	DeInit(GPIOout, GPIO_Pin_out);
}


