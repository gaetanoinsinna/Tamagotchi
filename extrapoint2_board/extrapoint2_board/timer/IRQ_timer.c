/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#define UPTICKS 1
#include <string.h>
#include <stdio.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../RIT/RIT.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../game/game.h"
#include "../music/music.h"
#include "../adc/adc.h"




extern int s;
extern int m;
extern int h;
extern int happiness;
extern int satiety;
extern int reset;
extern int cuddle;
extern int isEating;
extern int isDead;
volatile int sound = 0;
extern int isButtonPressed;

extern int happinessSeconds;
extern int satietySeconds;

extern int volume;
extern int J_select;
extern int isSelected;

//static int ticks = 0;
//static int currentNote = 0;
//static int duration = 0;

//NOTE click[] = {{a4, time_semicroma}};
//NOTE eating[] = { {f4, time_semicroma},{b3, time_semicroma},{g4, time_croma}};
//NOTE death[] = { {a4, time_semicroma},{d3, time_semicroma},{b2, time_semicroma},{c3,time_semicroma},{b2,time_croma}};
//NOTE cuddles_sound[] = { {a4, time_semicroma},{b4, time_semicroma},{c5, time_croma},{a4, time_semicroma},{c5, time_semicroma},{g4, time_croma},{f3, time_semicroma},{b4, time_croma}};
//




uint16_t SinTable[45] =                                       /* ÕýÏÒ±í                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};




										 
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		AGE and ANIMATION TIMER 
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	int i,j;
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
		
		if(happiness!=0 && satiety !=0 && isEating == 0){
		//isEating = 0;
		enable_RIT();
		
					for(i = 0; i < LINK_HEIGHT;i++){
						for(j = 0; j < LINK_LENGHT;j++){
							if(link2[i][j]==1) LCD_DrawRectangle(50+5*j,90+5*i,5,5,Black,Black);
							if(link2[i][j]==0) LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
							if(cuddle > 0){
								if(link2[i][j]==2) LCD_DrawRectangle(50+5*j,90+5*i,5,5,Red,Red);
							} else if(link2[i][j]==2) LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
				
						}
					}
					
		for(i = 0; i < HEART_HEIGHT; i++){
			for(j = 0; j < HEART_LENGHT; j++){
				if(cuddle > 0) if(heart[i][j]==1) LCD_DrawRectangle(15+1*j,100+1*i,1,1,Red,Red);
				if(cuddle <= 0) if(heart[i][j]==1 ) LCD_DrawRectangle(15+1*j,100+1*i,1,1,White,White);
				//else if (heart[i][j]==2) LCD_DrawRectangle(15+1*j,100+1*i,1,1,Red,Red);
			}
		}
		
		for(i = 0; i < HEART_HEIGHT; i++){
			for(j = 0; j < HEART_LENGHT; j++){
				if(cuddle > 0) if(heart[i][j]==1) LCD_DrawRectangle(5+1*j,115+1*i,1,1,Red,Red);
				if(cuddle <= 0) if(heart[i][j]==1 ) LCD_DrawRectangle(5+1*j,115+1*i,1,1,White,White);
				//else if (heart[i][j]==2) LCD_DrawRectangle(15+1*j,100+1*i,1,1,Red,Red);
			}
		}
			

		}
		
		
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
		
	if(happiness != 0 && satiety != 0 && isEating == 0){
	
		for(i = 0; i < LINK_HEIGHT;i++){
			for(j = 0; j < LINK_LENGHT;j++){
				if(link[i][j]==1)
					LCD_DrawRectangle(50+5*j,90+5*i,5,5,Black,Black);
				if(link[i][j]==0)
					LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
				if(cuddle > 0){
								if(link[i][j]==2) LCD_DrawRectangle(50+5*j,90+5*i,5,5,Red,Red);
							} else if(link[i][j]==2) LCD_DrawRectangle(50+5*j,90+5*i,5,5,White,White);
				
			}
		}
		
		for(i = 0; i < HEART_HEIGHT; i++){
			for(j = 0; j < HEART_LENGHT; j++){
				if(cuddle > 0) if(heart[i][j]==1) LCD_DrawRectangle(15+1*j,100+1*i,1,1,Red,Red);
				if(cuddle <= 0) if(heart[i][j]==1 ) LCD_DrawRectangle(15+1*j,100+1*i,1,1,White,White);
				//else if (heart[i][j]==2) LCD_DrawRectangle(15+1*j,100+1*i,1,1,Red,Red);
			}
		}
		
		for(i = 0; i < HEART_HEIGHT; i++){
			for(j = 0; j < HEART_LENGHT; j++){
				if(cuddle > 0) if(heart[i][j]==1) LCD_DrawRectangle(5+1*j,115+1*i,1,1,Red,Red);
				if(cuddle <= 0) if(heart[i][j]==1 ) LCD_DrawRectangle(5+1*j,115+1*i,1,1,White,White);
				//else if (heart[i][j]==2) LCD_DrawRectangle(15+1*j,100+1*i,1,1,Red,Red);
			}
		}
	
	}
		
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
	static int cuddlesSeconds = 0;
	if(LPC_TIM1 -> IR & 01){
		
		
		if(cuddle>0) cuddlesSeconds++; else cuddlesSeconds = 0;
		if(cuddlesSeconds == 2){
		happiness++;
		cuddle = 0;
		sound = 0;
		isButtonPressed = 0;
		cuddlesSeconds = 0;
			
		LCD_DrawRectangle(50+5*11,90+5*12,5,5,White,White);
		LCD_DrawRectangle(50+5*16,90+5*12,5,5,White,White);
		LCD_DrawRectangle(50+5*13,90+5*13,10,5,White,White);
			
			for(i = 0; i < HEART_HEIGHT; i++){
				for(j = 0; j < HEART_LENGHT; j++){
					if(heart[i][j]==1) LCD_DrawRectangle(15+1*j,100+1*i,1,1,White,White);

			}
		}
		
		for(i = 0; i < HEART_HEIGHT; i++){
			for(j = 0; j < HEART_LENGHT; j++){
				if(heart[i][j]==1) LCD_DrawRectangle(5+1*j,115+1*i,1,1,White,White);
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
		}
		
			happinessSeconds++;
		if(happinessSeconds == 5){
				happinessSeconds = 0;
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
							isDead = 1;
							sound = 0;
							disable_timer(0);
							disable_timer(1);
							//disable_timer(3); //devo disattivare anche l'altro timer
							//disable_timer(2);
							//disable_timer(1);
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
							
						
						
											for(i = 0; i < HEART_HEIGHT; i++){
				for(j = 0; j < HEART_LENGHT; j++){
					if(heart[i][j]==1) LCD_DrawRectangle(15+1*j,100+1*i,1,1,White,White);

			}
		}
		
		for(i = 0; i < HEART_HEIGHT; i++){
			for(j = 0; j < HEART_LENGHT; j++){
				if(heart[i][j]==1) LCD_DrawRectangle(5+1*j,115+1*i,1,1,White,White);
			}
		}
						
						
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
		}

			satietySeconds++;
		
		if(satietySeconds == 5){
			satietySeconds = 0;
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
									isDead = 1; 
									sound = 0;
									disable_timer(1);
									disable_timer(0);
									//disable_timer(3);
									//disable_timer(2); // devo fermare anche l'altro timer se uno dei due si ferma
									
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
						
								
								
								
									for(i = 0; i < HEART_HEIGHT; i++){
				for(j = 0; j < HEART_LENGHT; j++){
					if(heart[i][j]==1) LCD_DrawRectangle(15+1*j,100+1*i,1,1,White,White);

			}
		}
		
		for(i = 0; i < HEART_HEIGHT; i++){
			for(j = 0; j < HEART_LENGHT; j++){
				if(heart[i][j]==1) LCD_DrawRectangle(5+1*j,115+1*i,1,1,White,White);
			}
		}
		
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
		}
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
	}

  return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		SOUND EFFECTS
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER2_IRQHandler (void)

{
	static int sineticks=0;
	static int currentValue; 
	currentValue = SinTable[sineticks];
		
	switch(volume){
		case 0: LPC_DAC->DACR = 0 * currentValue/819 <<6;
			break;
		case 1: LPC_DAC->DACR = (int) ((500 * currentValue/819))<<6; //819 max value of sin table
			break;
		case 2: LPC_DAC->DACR = (int)((800 * currentValue/819))<<6;
			break;
		case 3: LPC_DAC->DACR = (int)((1023 * currentValue/819)) <<6;
			break;
		default: break;
	}
	sineticks++;
	if(sineticks==45) sineticks=0;
			
	LPC_TIM2->IR =  1 ; 

	return;

}

/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		SOUND EFFECTS
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER3_IRQHandler (void)
{
		disable_timer(2);
		reset_timer(2);
	
		if((LPC_GPIO1->FIOPIN & (1<<25)) != 0) isButtonPressed = 0;
		
		if(isSelected == 1 && sound!=-1 && isEating == 0 && isDead == 0 && cuddle == 0){
			
			sound++;
			switch(sound){
				case 1: 
					init_timer(2,0,0,3,2249);
					
						break;
				
				case 2:
					sound = -1;
					//enable_RIT();
					//disable_timer(2);
				break;
		} 
			enable_timer(2);
			isButtonPressed = 1;
			
			
	}
	
		else if (isEating == 1  && sound !=-1){
			sound++;
			switch(sound){
				
			case 1: 
				init_timer(2,0,0,3,2249);
				
					break;
			
				case 2: init_timer(2,0,0,3,0);break;
				//case 3: init_timer(2,0,0,3,0);break;
				//case 4: init_timer(2,0,0,3,0);break;
					
			case 3:
				
				init_timer(2,0,0,3,1592);
			
				
			break;
			case 4:
				init_timer(2,0,0,3,2249);
			
			break;
			case 5:
				init_timer(2,0,0,3,1417);
				
			break;
			case 6: 
				sound = -1;
			break;
			}
			enable_timer(2);
		} 
	else if(cuddle > 0 && sound != -1){
			sound++;
			switch(sound){
			case 1:
				init_timer(2,0,0,3,1263);
				
			break;
			case 2:
				init_timer(2,0,0,3,1125);
				
			break;
			case 3:
				init_timer(2,0,0,3,1062);
			
			break;
			case 4:
				init_timer(2,0,0,3,1263);
				
			
			break;
			case 5:
				init_timer(2,0,0,3,1062);
				
			break;
			case 6:
				init_timer(2,0,0,3,1417);
				
			break;
			case 7: 
				init_timer(2,0,0,3,2249);
				
			break;
			case 8: 
				init_timer(2,0,0,3,1125);
				
			break;
			case 9:
				sound = -1;
			break;
			}
			enable_timer(2);
		} else if(isDead > 0 && sound != -1){
			sound++;
			switch(sound){
			case 1:
				init_timer(2,0,0,3,1263);
				
			break;
			case 2:
				init_timer(2,0,0,3,1592);
				
			break;
			case 3:
				init_timer(2,0,0,3,2249);
				
			break;
			case 4:
				init_timer(2,0,0,3,1263);
				
			break;
			case 5:
				init_timer(2,0,0,3,1417);
			break;
			case 6:
				sound = -1;
			break;
			}
		enable_timer(2);
		}
	
		LPC_TIM3->IR =  1 ;

		return;

}

/******************************************************************************
**                            End Of File
******************************************************************************/
