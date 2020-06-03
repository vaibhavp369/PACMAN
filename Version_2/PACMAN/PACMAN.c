/*
 * PACMAN.c
 *
 * Created: 20/03/2020 6:02:14 PM
 * Author : vaibhav
 */ 

#include <avr/io.h>
#include "firebird_simulation.h"
#include "lcd.h"
#include <util/delay.h>


void custom_char (unsigned char index, unsigned char *data)
{
	unsigned char i;
	if(index<8)
	{
		lcd_wr_command(0x40 + (index*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)            	    /* Write 8 byte for generation of 1 character */
		lcd_wr_char(0,0,data[i]);
	}
}

void creat_char()

{

	unsigned char round[]       =  {0x00,0x0E,0x1F,0x1F,0x1F,0x0E,0x00,0x00};
	unsigned char open_round[]  =  {0x00,0x0F,0x1E,0x18,0x1E,0x0F,0x00,0x00};
	unsigned char three_teeth[] =  {0x00,0x0E,0x1F,0x15,0x1F,0x15,0x00,0x00};
	unsigned char two_teeth[]   =  {0x00,0x0E,0x1F,0x15,0x1F,0x0A,0x00,0x00};
	unsigned char four_dot[]    =  {0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00};
	unsigned char fade1[]       =  {0x00,0x0E,0x1F,0x1F,0x1F,0x0E,0x00,0x00};
	unsigned char fade2[]       =  {0x00,0x0A,0x1B,0x1F,0x1F,0x0E,0x00,0x00};
	unsigned char fade3[]       =  {0x00,0x00,0x00,0x04,0x0E,0x0E,0x00,0x00};
	
	custom_char(7,round);
	custom_char(1,open_round);
	custom_char(2,three_teeth);
	custom_char(3,two_teeth);
	custom_char(4,four_dot);
	custom_char(5,fade1);
	custom_char(6,fade2);
	custom_char(0,fade3);
	
}


void play_game()
{
 unsigned char i;
 lcd_wr_char(2,16,3);
 for(i=1;i<=15;i++)
  {
	  lcd_wr_char(2,i,4);
	  
	  if(i%2 == 0)
	    lcd_wr_char(2,16,3);
	  else
	     lcd_wr_char(2,16,2);
	_delay_ms(100);
  }
  
   for(i=1;i<=15;i++)
   {
	   	   
	   if(i%2 == 0)
	   {
		 lcd_wr_char(2,i,' ');
		 lcd_wr_char(2,i,1);   //open mouth
		 lcd_wr_char(2,16,3);  //two teeth
		 lcd_wr_char(2,i-1,' ');
		 _delay_ms(75);
		 
	   }
	   
	   else
	   {
		lcd_wr_char(2,i,' ');
		lcd_wr_char(2,i,7);  // round
		lcd_wr_char(2,16,2); // three teeth
		lcd_wr_char(2,i-1,' ');
		_delay_ms(75);
		
	   }
	   
	   _delay_ms(150);
   }
   
   lcd_wr_char(2,15,5);
   _delay_ms(150);
   lcd_wr_char(2,15,6);
   _delay_ms(150);
   lcd_wr_char(2,15,0);
   _delay_ms(150);
   lcd_wr_char(2,15,' ');
  
}



int main(void)
{
	lcd_port_config();
	lcd_init();
	creat_char();
	while (1)
	{
		lcd_clear();
		lcd_home();
		lcd_string(1,5,"PACMAN");
		play_game();
		_delay_ms(2000);
	}
}


