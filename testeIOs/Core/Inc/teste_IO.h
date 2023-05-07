/**
  ******************************************************************************
  * @file    teste_IO.h
  * @author  Clara Luz Salles Cavalcante
  * 		 Danilo Mota Alencar Filho
  * @brief   Cabeçalho para arquivo de teste de entradas e saídas digitais.
  ******************************************************************************
  */

/* Protótipos das funções ------------------------------------------------------------------*/
void CLKEnable(GPIO_TypeDef* GPIOx);
void initOutput(GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out);
void initInput(GPIO_TypeDef* GPIOin, uint16_t GPIO_Pin_in);
void DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
GPIO_PinState read_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void write_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,GPIO_PinState PinState);
void toggle_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void delay(uint32_t Delay);
void inputTC(GPIO_TypeDef* GPIOin, uint16_t GPIO_Pin_in, GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out);
void outputTC(GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out, int logic);
void testeInput(GPIO_TypeDef* GPIOin, uint16_t GPIO_Pin_in, GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out);
void testeOutput(GPIO_TypeDef* GPIOout, uint16_t GPIO_Pin_out);
