/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/


#include "lpc17xx.h"

#include "RIT.h"

//#include "../led/led.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "../game/game.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
								

//volatile int J_select;
//volatile int J_left;
//volatile int J_right;

extern int happiness;
extern int satiety;
extern int reset;

volatile int isEating;

void RIT_IRQHandler (void)
{					
	
	int i,j;
	
	static int J_left = 0; // 27th pin
	static int J_right = 0; // 28th pin
	//static int J_select = 0; //25th pin
	
	//isEating = 0;
	
	
	/*LEFT JOYSTICK*/
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){
		if(happiness != 0 && satiety != 0 ){
			if(J_right!=0){
				J_right = 0;
				LCD_DrawRectangle(130,250,100,60,Black,White);
				GUI_Text(160, 275, (uint8_t *) "SNACK", Black, White);
			}
		
			J_left++;
		switch(J_left){
			case 1:
					/*MEAL*/
					LCD_DrawRectangle(10,250,100,60,White,Black);
					GUI_Text(45, 275, (uint8_t *) "MEAL", White, Black);
			
					
				break;
			default:
				break;
				}
			}	
			else {
				if(reset==2){
				LCD_DrawRectangle(10,250,220,60,White,Black);
				GUI_Text(100, 275, (uint8_t *) "RESET", White, Black);
				reset = 1;
				}
			}
	}
		 

	
	/*RIGHT JOYSTICK*/
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
		if(happiness != 0 && satiety != 0 ){
			
			/*MEAL*/
			if(J_left!=0){
				J_left = 0;
				LCD_DrawRectangle(10,250,100,60,Black,White);
				GUI_Text(45, 275, (uint8_t *) "MEAL", Black, White);
			}
				
		J_right++;
		switch(J_right){
			case 1:
		/*SNACK*/
		LCD_DrawRectangle(130,250,100,60,White,Black);
		GUI_Text(160, 275, (uint8_t *) "SNACK", White, Black);
				break;
			default:
				break;
		}
	}	else {
		if(reset == 2){
			LCD_DrawRectangle(10,250,220,60,White,Black);
			GUI_Text(100, 275, (uint8_t *) "RESET", White, Black);
			reset = 1;
		}
		}
	}
		

	
	/*SELECT JOYSTICK*/
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0 ){
		if(satiety == 0 || happiness == 0){
			if(reset == 1) resetGame();
		} else {
			if(J_left == 1){
				if (happiness < MAX_HAPPINESS) {
					happiness++;
					
					//isEating = 1;
					
					/*DISABLE JOYPAD POLLING*/
					disable_RIT();
					
					/*RESET TIMER2 HAPPINESS LEVEL*/
					reset_timer(2);
					enable_timer(2);
					/*RESET TIMER1 EATING ANIMATION*/
					reset_timer(1);
					enable_timer(1);
					
					for(i = 0; i < HEART_HEIGHT; i++){
						for(j = 0; j < HEART_LENGHT; j++){
							if(heart[i][j]==1) LCD_DrawRectangle(15+1*j,100+1*i,1,1,Black,Black);
							else if (heart[i][j]==0) LCD_DrawRectangle(15+1*j,100+1*i,1,1,White,White);
							//else if (heart[i][j]==2) LCD_DrawRectangle(15+1*j,100+1*i,1,1,Red,Red);
						}
					}	
					/*EATING ANIMATION*/
					LCD_DrawRectangle(35,90,190,140,White,White);
					for(i = 0; i < LINK_HEIGHT;i++){
						for(j = 0; j < LINK_LENGHT;j++){
							if(link[i][j]==1)
								LCD_DrawRectangle(10+5*j,90+5*i,5,5,Black,Black);
							if(link[i][j]==0)
								LCD_DrawRectangle(10+5*j,90+5*i,5,5,White,White);
				
						}
					}
				
					/*REPOSITIONING ANIMATION*/
					for(i = 0; i < LINK_HEIGHT;i++){
						for(j = 0; j < LINK_LENGHT;j++){
							if(link[i][j]==1)
								LCD_DrawRectangle(23+5*j,90+5*i,5,5,Black,Black);
							if(link[i][j]==0)
								LCD_DrawRectangle(23+5*j,90+5*i,5,5,White,White);
					
						}
					}
					
					/*REPOSITIONING ANIMATION*/
					for(i = 0; i < LINK_HEIGHT;i++){
						for(j = 0; j < LINK_LENGHT;j++){
							if(link[i][j]==1)
								LCD_DrawRectangle(36+5*j,90+5*i,5,5,Black,Black);
							if(link[i][j]==0)
								LCD_DrawRectangle(36+5*j,90+5*i,5,5,White,White);
					
						}
					}
					
				}
				
				switch(happiness){
					case 4: LCD_DrawRectangle(72,47,6,16,Black,Black);
						break;
					case 3: LCD_DrawRectangle(62,47,6,16,Black,Black);
						break;
					case 2: LCD_DrawRectangle(52,47,6,16,Black,Black);
						break;
					default:
						break;
				}
				
			} else if(J_right == 1){
				
				
				
				if(satiety < MAX_SATIETY){
					satiety++;
					//isEating = 1;
					/*DISABLE JOYPAD POLLING*/
					disable_RIT();
					/*RESET TIMER3 SATIETY LEVEL*/
					reset_timer(3);
					enable_timer(3);
					/*RESET TIMER1 EATING ANIMATION*/
					reset_timer(1);
					enable_timer(1);
					
					for(i = 0; i < PIZZA_HEIGHT;i++){
						for(j = 0; j < PIZZA_LENGHT; j++){
							if(pizza[i][j]==1) LCD_DrawRectangle(190+2*j,150+2*i,2,2,Black,Black);
							else if (pizza[i][j]==0) LCD_DrawRectangle(190+2*j,150+2*i,2,2,White,White);
							//else if (pizza [i][j]==2) LCD_DrawRectangle(190+2*j,150+2*i,2,2,Red,Red);
						}
					}
					/*EATING ANIMATION*/
					LCD_DrawRectangle(15,90,170,140,White,White);
					for(i = 0; i < LINK_HEIGHT;i++){
						for(j = 0; j < LINK_LENGHT;j++){
							if(link[i][j]==1)
								LCD_DrawRectangle(90+5*j,90+5*i,5,5,Black,Black);
							if(link[i][j]==0)
								LCD_DrawRectangle(90+5*j,90+5*i,5,5,White,White);
				
						}
					}
					/*REPOSITIONING ANIMATION*/
					for(i = 0; i < LINK_HEIGHT;i++){
						for(j = 0; j < LINK_LENGHT;j++){
							if(link[i][j]==1)
								LCD_DrawRectangle(76+5*j,90+5*i,5,5,Black,Black);
							if(link[i][j]==0)
								LCD_DrawRectangle(76+5*j,90+5*i,5,5,White,White);
					
						}
					}
					/*REPOSITIONING ANIMATION*/
					for(i = 0; i < LINK_HEIGHT;i++){
						for(j = 0; j < LINK_LENGHT;j++){
							if(link[i][j]==1)
								LCD_DrawRectangle(63+5*j,90+5*i,5,5,Black,Black);
							if(link[i][j]==0)
								LCD_DrawRectangle(63+5*j,90+5*i,5,5,White,White);
					
						}
					}
					
				}
				
				switch(satiety){
					case 4: LCD_DrawRectangle(192,47,6,16,Black,Black);
						break;
					case 3: LCD_DrawRectangle(182,47,6,16,Black,Black);
						break;
					case 2: LCD_DrawRectangle(172,47,6,16,Black,Black);
						break;
					default:
						break;
				}
				
			}
				
		}
			
	} //else J_select = 0; 	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
