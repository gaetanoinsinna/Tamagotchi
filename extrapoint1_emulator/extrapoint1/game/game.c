

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "../GLCD/GLCD.h" 
#include "../joystick/joystick.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "game.h"


volatile int happiness;
volatile int satiety;
volatile int reset;
volatile int s;
volatile int m;
volatile int h;										

void GUIinit(){
	
	
	
	
	
int i,j;


LCD_Clear(White);
	
		

	/*BATTERY*/
	/*Happiness*/
	LCD_DrawRectangle(40,45,40,20,Black,White);
	LCD_DrawRectangle(80,50,2,10,Black,Black);
	
	LCD_DrawLine(50,45,50,70,Black);
	LCD_DrawLine(60,45,60,70,Black);
	LCD_DrawLine(70,45,70,70,Black);

	/*HAPPINESS LEVEL*/
	LCD_DrawRectangle(42,47,6,16,Black,Black);
	LCD_DrawRectangle(52,47,6,16,Black,Black);
	LCD_DrawRectangle(62,47,6,16,Black,Black);
	LCD_DrawRectangle(72,47,6,16,Black,Black);
	
	GUI_Text(25, 66, (uint8_t *) "Happiness", Black, White);
	
	
	
	/*SATIETY*/
	LCD_DrawRectangle(160,45,40,20,Black,White);
	LCD_DrawRectangle(200,50,2,10,Black,Black);

	
	LCD_DrawLine(170,45,170,70,Black);
	LCD_DrawLine(180,45,180,70,Black);
	LCD_DrawLine(190,45,190,70,Black);
	
	/*SATIETY LEVEL*/
	LCD_DrawRectangle(162,47,6,16,Black,Black);
	LCD_DrawRectangle(172,47,6,16,Black,Black);
	LCD_DrawRectangle(182,47,6,16,Black,Black);
	LCD_DrawRectangle(192,47,6,16,Black,Black);

	GUI_Text(152, 66, (uint8_t *) "Satiety", Black, White);
	
	
	/*BUTTONS*/
	/*MEAL*/
	LCD_DrawRectangle(10,250,100,60,Black,White);
	GUI_Text(45, 275, (uint8_t *) "MEAL", Black, White);
	
	/*SNACK*/
	LCD_DrawRectangle(130,250,100,60,Black,White);
	GUI_Text(160, 275, (uint8_t *) "SNACK", Black, White);
	
	
	/*LINK INIT*/
	GUI_Text(70,10, "Age 00:00:00",Black,White);
	for(i = 0; i < 28; i++)
		for(j = 0; j < 28; j++){
				if(link[i][j] == 0) LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
				if(link[i][j] == 1) LCD_DrawRectangle(50+5*j,90+5*i,5,5,Black,Black);
		}
	
		
}

void gameInit(){
	
	happiness = MAX_HAPPINESS;
	satiety = MAX_SATIETY;
	reset = 0;
	s = 0;
	m = 0; 
	h = 0;
	
	/*TIMER0 PER ETA'*/
	init_timer(0,0,0,1,0x17D7840); 
	init_timer(0,0,1,3,0x2FAF080);

	/*TIMER1 PER ANIMAZIONE*/
	init_timer(1,0,0,1,0x17D7840); 
	init_timer(1,0,1,3,0x2FAF080);
	
	/*TIMER2 PER HAPPINESS*/
	init_timer(2,0,0,3,0x7735940);

	
	/*TIMER3 PER SATIETY*/
	init_timer(3,0,0,3,0x7735940);

	
	/*RIT per POLLING DEL JOYSTICK*/
	joystick_init();
	init_RIT(0x1312D0);
	
}

void startGame(){
	enable_timer(0);
	enable_timer(1);
	enable_timer(2);
	enable_timer(3);
	enable_RIT();
}

void resetGame(){
	reset_timer(0);
	reset_timer(1);
	reset_timer(2);
	reset_timer(3);
	reset_RIT();

	
	GUIinit();
	gameInit();
	startGame();
	
}
