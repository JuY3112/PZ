/*
Demonstraèní aplikace pro jednoduché ètení stavu maticové klávesnice

*/
#include "stm8s.h"
#include "milis.h"
#include "stm8_hd44780.h"
#include "stdio.h"
#include "keypad.h" // tady máme "knihovnu" pro skenování stavu klávesnice

void process_keypad(void);

char text[24];


void main(void){
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz z interního RC oscilátoru
init_milis(); // milis kvuli delay_ms()
lcd_init();		// inicializace displeje
keypad_init();

  while (1){
		process_keypad(); // obsluhujeme klávesnici
	}
}


// pravidelnì sleduje stav klávesnice a reaguje na stisknutí kláves
// mechanismus jak reagovat na stisk klávesy jde napsat mnohem elegantnìji - prostor pro vás :)
void process_keypad(void){
static uint8_t minule_stisknuto=0xFF;	// ukládáme poslední stav klávesnice (zde "volno")
static uint16_t last_time=0; 
uint8_t stisknuto;

	if(milis()-last_time > 20){ // každých 20ms ...
		last_time = milis();
		stisknuto=keypad_scan(); // ... skenujeme klávesnici
		if(minule_stisknuto == 0 && stisknuto != 0){ // pokud byla minule uvolnìná a teï je nìco stisknuto
			minule_stisknuto = stisknuto;
			// zachytili jsme stisk klávesy - mùžeme na to zareagovat
			// pro demonstraci ji vypíšu na displej
			sprintf(text,"%2u",stisknuto);
			lcd_gotoxy(0,0);
			lcd_puts(text);
		}
		if(stisknuto == 0){minule_stisknuto=0;}
	}
}



// pod tímto komentáøem nic nemìòte 
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
