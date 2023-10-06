/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include <stdio.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../RIT/RIT.h"

#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"



extern int s;
extern int m;
extern int h;
extern int happiness;
extern int satiety;
extern int reset;

extern int isEating;

										 
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		AGE TIMER 
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	char time_in_char[13] = "";
	
	if (LPC_TIM0->IR & 01){
		
		s++;
		sprintf(time_in_char,"Age %02d:%02d:%02d",h,m,s);
	
		
		if(s == 60){
			m++;
			s=0;
			sprintf(time_in_char,"Age %02d:%02d:%02d",h,m,s);
		}
	
		if(m == 60){
			h++;
			m=0;
			s=0;
			sprintf(time_in_char,"Age %02d:%02d:%02d",h,m,s);
		}
		
	
	GUI_Text(70,10, (unsigned char*) time_in_char,Black,White);	
	LPC_TIM0->IR = 1;			/* clear interrupt flag */
	} else if (LPC_TIM0->IR & 02){
		
				s++;
		sprintf(time_in_char,"Age %02d:%02d:%02d",h,m,s);
	
		
		if(s == 60){
			m++;
			s=0;
			sprintf(time_in_char,"Age %02d:%02d:%02d",h,m,s);
		}
		
		if(m == 60){
			h++;
			m=0;
			s=0;
			sprintf(time_in_char,"Age %02d:%02d:%02d",h,m,s);
		}
		
	GUI_Text(70,10, (unsigned char*) time_in_char,Black,White);
	LPC_TIM0->IR = 2;			/* clear interrupt flag */
	}
	
	return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		ANIMATION TIMER
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	int i,j;
	
	
		
		/* Match register 0 interrupt service routine */
	if (LPC_TIM1->IR & 01 && happiness != 0 && satiety != 0){
		
		//isEating = 0;
		enable_RIT();
		
					for(i = 0; i < LINK_HEIGHT;i++){
						for(j = 0; j < LINK_LENGHT;j++){
							if(link2[i][j]==1)
								LCD_DrawRectangle(50+5*j,90+5*i,5,5,Black,Black);
							if(link2[i][j]==0)
								LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
				
						}
					}
			

		
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
	}
		/* Match register 1 interrupt service routine */
	else if(LPC_TIM1->IR & 02 && happiness != 0 && satiety != 0){
		
	 
	
		for(i = 0; i < LINK_HEIGHT;i++){
			for(j = 0; j < LINK_LENGHT;j++){
				if(link[i][j]==1)
					LCD_DrawRectangle(50+5*j,90+5*i,5,5,Black,Black);
				if(link[i][j]==0)
					LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
				
			}
		}
	

	LPC_TIM1->IR =  2 ;			/* clear interrupt flag */	
	
}
	
	/* Match register 2 interrupt service routine */
	else if(LPC_TIM1->IR & 4)
  {		
		LPC_TIM1->IR =  4 ;			/* clear interrupt flag */	
	}
		/* Match register 3 interrupt service routine */
	else if(LPC_TIM1->IR & 8)
  {
		LPC_TIM1->IR =  8 ;			/* clear interrupt flag */	
	}
	
  return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Happiness timer
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER2_IRQHandler (void)
{
	int i,j;
	if(LPC_TIM2->IR & 01){

			happiness--;	
			
			switch(happiness){
						case 3: LCD_DrawRectangle(72,47,6,16,White,White);
							break;
						case 2: LCD_DrawRectangle(62,47,6,16,White,White);
							break;
						case 1: LCD_DrawRectangle(52,47,6,16,White,White);
							break;
						case 0:  
							{
							
							if(reset == 0){
							disable_timer(0);
							disable_timer(3); //devo disattivare anche l'altro timer
							disable_timer(2);
							disable_timer(1);
							reset = 2;				//settato ma ancora non selezionato	
							LCD_DrawRectangle(42,47,6,16,White,White);	
							//LCD_DrawRectangle(10,250,220,60,White,White);
							//GUI_Text(100, 275, (uint8_t *) "RESET", Black, White);
							
							
					//		}
						/*EXIT ANIMATION*/
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(50+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
								}
						}
						
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(70+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(70+5*j,90+5*i,5,5,White,White);
								}
						}
						
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(90+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(90+5*j,90+5*i,5,5,White,White);
								}
						}
						
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(110+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(110+5*j,90+5*i,5,5,White,White);
								}
						}
						
					
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(130+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(130+5*j,90+5*i,5,5,White,White);
								}
						}
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(150+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(150+5*j,90+5*i,5,5,White,White);
								}
						}
						
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(170+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(170+5*j,90+5*i,5,5,White,White);
								}
						}
						
								LCD_DrawRectangle(110,90,130,140,White,White);
							
							for(i = 0; i < 28;i++){
								for(j = 0; j < 28;j++){
									if(gameOver[i][j]==1) LCD_DrawRectangle(50+5*j,90+5*i,5,5,Black,Black);
									if(gameOver[i][j]==0) LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
									}
								}
							
							LCD_DrawRectangle(10,250,220,60,Black,White);
							GUI_Text(100, 275, (uint8_t *) "RESET", Black, White);
							
							
						}
							//questa parentesi 
					}
							break;
					}
			
		LPC_TIM2->IR =  1 ;
	} 
	else if (LPC_TIM2->IR & 02){
		LPC_TIM2->IR =  2 ;
	}
	else if(LPC_TIM2->IR & 4)
  {		
		LPC_TIM2->IR =  4 ;			/* clear interrupt flag */	
	}
	else if(LPC_TIM2->IR & 8)
  {
		LPC_TIM2->IR =  8 ;			/* clear interrupt flag */	
	}
  return;

}

/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		SATIETY
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER3_IRQHandler (void)
{
	int i, j;
	if(LPC_TIM3->IR & 01){
		satiety--;
		switch(satiety){
						case 3: LCD_DrawRectangle(192,47,6,16,White,White);
							break;
						case 2: LCD_DrawRectangle(182,47,6,16,White,White);
							break;
						case 1: LCD_DrawRectangle(172,47,6,16,White,White);
							break;
						case 0: 
							{								
								if(reset == 0){
									disable_timer(1);
									disable_timer(0);
									disable_timer(3);
									disable_timer(2); // devo fermare anche l'altro timer se uno dei due si ferma
									
									reset = 2;				//settato ma non ancora selezionato	
									LCD_DrawRectangle(162,47,6,16,White,White);
									
									LCD_DrawRectangle(10,250,220,60,White,White);
								//}
								
								
								/*EXIT ANIMATION*/
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(50+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
								}
						}
						
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(70+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(70+5*j,90+5*i,5,5,White,White);
								}
						}
						
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(90+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(90+5*j,90+5*i,5,5,White,White);
								}
						}
						
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(110+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(110+5*j,90+5*i,5,5,White,White);
								}
						}
						
					
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(130+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(130+5*j,90+5*i,5,5,White,White);
								}
						}
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(150+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(150+5*j,90+5*i,5,5,White,White);
								}
						}
						
						for(i = 0; i<LINK_HEIGHT;i++){
								for(j = 0; j < LINK_LENGHT;j++){
									if(linkOver[i][j]==1) LCD_DrawRectangle(170+5*j,90+5*i,5,5,Black,Black);
									if(linkOver[i][j]==0) LCD_DrawRectangle(170+5*j,90+5*i,5,5,White,White);
								}
						}
						
								LCD_DrawRectangle(110,90,130,140,White,White);
						
								
								for(i = 0; i < 28;i++){
									for(j = 0; j < 28;j++){
										if(gameOver[i][j]==1)
											LCD_DrawRectangle(50+5*j,90+5*i,5,5,Black,Black);
										if(gameOver[i][j]==0)
											LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
									}
								}
								LCD_DrawRectangle(10,250,220,60,Black,White);
								GUI_Text(100, 275, (uint8_t *) "RESET", Black, White);
						}
//questa parentesi	
							}
							break;
					}
		
		LPC_TIM3->IR =  1 ;
	} 
	else if (LPC_TIM3->IR & 02){
		LPC_TIM3->IR =  2 ;
	}
	else if(LPC_TIM3->IR & 4)
  {		
		LPC_TIM3->IR =  4 ;			/* clear interrupt flag */	
	}
	else if(LPC_TIM3->IR & 8)
  {
		LPC_TIM3->IR =  8 ;			/* clear interrupt flag */	
	}
  return;

}

/******************************************************************************
**                            End Of File
******************************************************************************/
