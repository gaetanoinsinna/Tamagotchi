/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
//#include "../led/led.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;   
unsigned short AD_last = 0xFF;     /* Last converted value               */
volatile int volume;


void ADC_IRQHandler(void) {
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  if(AD_current != AD_last){
				
		AD_last = AD_current;

		switch(AD_current*7/0xFFF){
			case 0: 
				{LCD_DrawRectangle(22,14,2,6,White,White);
			   LCD_DrawRectangle(27,13,2,8,White,White);
				 LCD_DrawRectangle(32,12,2,10,White,White);
					volume = 0;
				 	
			}
				break;
			case 1:{
				LCD_DrawRectangle(22,14,2,6,Black,Black);
				LCD_DrawRectangle(27,13,2,8,White,White);
				LCD_DrawRectangle(32,12,2,10,White,White);
				volume = 1;
				}
				break;
			case 4:{
				LCD_DrawRectangle(22,14,2,6,Black,Black);				
				LCD_DrawRectangle(27,13,2,8,Black,Black);
				LCD_DrawRectangle(32,12,2,10,White,White);
				volume = 2;
			}
			
				break;
			case 7:{
				LCD_DrawRectangle(22,14,2,6,Black,Black);				
				LCD_DrawRectangle(27,13,2,8,Black,Black);
				LCD_DrawRectangle(32,12,2,10,Black,Black);
				volume = 3;
			}
				
				break;
			
			default:
				break;
		}
		AD_last = AD_current;
  }	
}
