#include "keypad.h"

// nastaví GPIO do výchozí konfigurace
void keypad_init(void){
// Radky jako vstupy s aktivovaným pull-up rezistorem (30-50k)
GPIO_Init(RDK1_GPIO,RDK1_PIN,GPIO_MODE_IN_PU_NO_IT);
GPIO_Init(RDK2_GPIO,RDK2_PIN,GPIO_MODE_IN_PU_NO_IT);
GPIO_Init(RDK3_GPIO,RDK3_PIN,GPIO_MODE_IN_PU_NO_IT);
GPIO_Init(RDK4_GPIO,RDK4_PIN,GPIO_MODE_IN_PU_NO_IT);
// Sloupce do režimu výstupy typu Open drain s počáteční hodnotou "H" (HiZ = "vstup")
GPIO_Init(SLP1_GPIO, SLP1_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
GPIO_Init(SLP2_GPIO, SLP2_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
GPIO_Init(SLP3_GPIO, SLP3_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
GPIO_Init(SLP4_GPIO, SLP4_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
}

// skenuje stav klávesnice a vrací hodnotu odpovídající stisknuté klávese nebo 0xFF pokud nic stisknuto není
uint8_t keypad_scan(void){
uint8_t tmp=0; // výchozí návratová hodnota ("nic nestisknuto")

AKT_SLP1; // aktivuje první sloupec
if(STAV_RDK1){tmp=1;} // čte stav prvního řádku...
if(STAV_RDK2){tmp=4;}
if(STAV_RDK3){tmp=7;}
if(STAV_RDK4){tmp=10;}
DEAKT_SLP1; // deaktivuje první sloupec

AKT_SLP2;
if(STAV_RDK1){tmp=2;}
if(STAV_RDK2){tmp=5;}
if(STAV_RDK3){tmp=8;}
if(STAV_RDK4){tmp=0;}
DEAKT_SLP2;

AKT_SLP3;
if(STAV_RDK1){tmp=3;}
if(STAV_RDK2){tmp=6;}
if(STAV_RDK3){tmp=9;}
if(STAV_RDK4){tmp=11;}
DEAKT_SLP3;

AKT_SLP4;
if(STAV_RDK1){tmp=12;}
if(STAV_RDK2){tmp=13;}
if(STAV_RDK3){tmp=14;}
if(STAV_RDK4){tmp=15;}
DEAKT_SLP4;

return tmp; // vrací stisknutou klávesu (resp. 0xFF pokud nic stisknuto není)
}
