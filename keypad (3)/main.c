/*
Demonstra�n� aplikace pro jednoduch� �ten� stavu maticov� kl�vesnice

*/
#include "stm8s.h"
#include "milis.h"
#include "stm8_hd44780.h"
#include "stdio.h"
#include "keypad.h" // tady m�me "knihovnu" pro skenov�n� stavu kl�vesnice

void process_keypad(void);

char text[24];


void main(void){
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz z intern�ho RC oscil�toru
init_milis(); // milis kvuli delay_ms()
lcd_init();		// inicializace displeje
keypad_init();

  while (1){
		process_keypad(); // obsluhujeme kl�vesnici
	}
}


// pravideln� sleduje stav kl�vesnice a reaguje na stisknut� kl�ves
// mechanismus jak reagovat na stisk kl�vesy jde napsat mnohem elegantn�ji - prostor pro v�s :)
void process_keypad(void){
static uint8_t minule_stisknuto=0xFF;	// ukl�d�me posledn� stav kl�vesnice (zde "volno")
static uint16_t last_time=0; 
uint8_t stisknuto;

	if(milis()-last_time > 20){ // ka�d�ch 20ms ...
		last_time = milis();
		stisknuto=keypad_scan(); // ... skenujeme kl�vesnici
		if(minule_stisknuto == 0xFF && stisknuto != 0xFF){ // pokud byla minule uvoln�n� a te� je n�co stisknuto
			minule_stisknuto = stisknuto;
			// zachytili jsme stisk kl�vesy - m��eme na to zareagovat
			// pro demonstraci ji vyp�u na displej
			sprintf(text,"%2u",stisknuto);
			lcd_gotoxy(0,0);
			lcd_puts(text);
		}
		if(stisknuto == 0xFF){minule_stisknuto=0xFF;}
	}
}



// pod t�mto koment��em nic nem��te 
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
