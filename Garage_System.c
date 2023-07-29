/*
 * Garage_System.c
 *
 * Created: 8/24/2022 11:11:30 PM
 *  Author: MSI
 */ 


#include "LCD.h"
#include "Timer.h"
#include "DIO.h"
#define F_CPU 8000000UL
#define MAX_CARS 3
#include <util/delay.h>

int main(void)
{
	unsigned char flag1=0,flag2=0,counter=0;
	LCD_init();
	_delay_ms(200);
	DIO_SET_DIR('D',0,0);
	DIO_SET_DIR('D',1,0);
	LCD_send_string("There are ");
	LCD_send_char(counter+'0');
	LCD_send_string(" Cars");
	LCD_move_cursor(2,1);
	LCD_send_string("Garage has space");
    while(1)
    {
		if (counter<MAX_CARS&&flag1==0&&DIO_READ('D',0)==1)
		{
			counter++;
			if (counter==3)
			{
				Timer2_fastPWM_generate2(90);
				LCD_clear();
					LCD_send_string("There are ");
					LCD_send_char(counter+'0');
					LCD_send_string(" Cars");
					LCD_move_cursor(2,1);
					LCD_send_string("NO space");
					flag1=1;
						_delay_ms(500);
						Timer2_fastPWM_generate2(0);
			}
			else{
			Timer2_fastPWM_generate2(90);
			flag1=1;
			LCD_move_cursor(1,11);
			LCD_send_char(counter+'0');
			_delay_ms(500);
			Timer2_fastPWM_generate2(0);
			}
		}					
		else if (counter<MAX_CARS&&DIO_READ('D',0)==0)
		{
			flag1=0;
		}
	
		if (counter<=MAX_CARS&&counter>0&&flag2==0&&DIO_READ('D',1)==1)
		{
			counter--;
			LCD_clear();
			Timer2_fastPWM_generate1(90);
				LCD_send_string("There are ");
				LCD_send_char(counter+'0');
				LCD_send_string(" Cars");
				LCD_move_cursor(2,1);
				LCD_send_string("Garage has space");
				flag2=1;
				_delay_ms(500);
				Timer2_fastPWM_generate1(0);
		}
		else if (DIO_READ('D',1)==0&&counter<=MAX_CARS&&counter>0)
		{
			flag2=0;
		}
	
				
        
    }
}