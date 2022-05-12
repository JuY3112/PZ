#include "stm8s.h"
#include "milis.h"
#include "stm8_hd44780.h"
#include "stdio.h"
#include "keypad.h"


char text[32];
void sleduj_enc(void);
void blikani_ledky(void);
void init_pwn(void);
uint16_t blink_period1 = 600;
uint16_t blink_period2 = 1200;
uint16_t hodnota=0;
uint16_t stav =0;
uint16_t rezim =1;


void main(void){
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
GPIO_Init(GPIOB,GPIO_PIN_7,GPIO_MODE_OUT_PP_HIGH_SLOW);
GPIO_Init(GPIOG,GPIO_PIN_2,GPIO_MODE_OUT_PP_HIGH_SLOW);
GPIO_Init(GPIOE,GPIO_PIN_2,GPIO_MODE_IN_FL_NO_IT); //CLK
GPIO_Init(GPIOE,GPIO_PIN_1,GPIO_MODE_IN_FL_NO_IT); //DT
GPIO_Init(GPIOC,GPIO_PIN_5,GPIO_MODE_IN_FL_NO_IT); //SW
init_milis();
lcd_init();		
init_pwm();
stav=1;
  while (1){
	blikani_ledky();
	sleduj_enc();

	}
	}
	
void sleduj_enc(void){
	static minule=1;	
	if(GPIO_ReadInputPin(GPIOE,GPIO_PIN_2) == RESET && minule==1){
		minule = 0; 
		if(GPIO_ReadInputPin(GPIOE,GPIO_PIN_1) != RESET){
		
			}
		else{


			}
	}
	else if (minule==0 && GPIO_ReadInputPin(GPIOE,GPIO_PIN_2) != RESET){
		minule=1;
		if(GPIO_ReadInputPin(GPIOE,GPIO_PIN_1) != RESET){
	
			}
		else{
		
			}
	}
}
void blikani_ledky(void){
	static uint16_t posledni_cas=0;
	static uint16_t strida=1000;
	TIM2_SetCompare1(strida);
	
}
	
void zmena_jasu(void){
static uint16_t x=0; //stisk tlaèítka 
static uint16_t last_time=0; 
static uint16_t strida;
if (GPIO_ReadInputPin(GPIOE,GPIO_PIN_4)==RESET && x==0) {
	x=1;
	last_time = milis();
		
}
if (GPIO_ReadInputPin(GPIOE,GPIO_PIN_4)!=RESET && x==1) {
	x=0;
}
if (x==1 && milis() - last_time > 250){
strida = (milis() - last_time - 250) / 1.09375;
	TIM2_SetCompare1(strida);

}	
}

	void init_pwm(void){
	GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_SLOW);
	TIM2_TimeBaseInit(TIM2_PRESCALER_1,TIMER_TOP);
	TIM2_OC1Init( 	// inicializujeme kanál 1 (TM2_CH1)
	TIM2_OCMODE_PWM1, 				// režim PWM1
	TIM2_OUTPUTSTATE_ENABLE,	// Výstup povolen (TIMer ovládá pin)
	0,											// výchozí hodnota šíøky pulzu (støídy) 1056/1600 = 66%
	TIM2_OCPOLARITY_HIGH				// Polarita LOW protože LED rozsvìcím 0 (spol. anoda)	
	);
	TIM2_OC1PreloadConfig(ENABLE);
	TIM2_Cmd(ENABLE);
}	


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/