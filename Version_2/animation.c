/*
*animation.c
*Created: 22/03/2020 12:26:12
*Author: VAIBHAV PATIL
*/
#include "firebird_simulation.h"
#include <util/delay.h>
#include "lcd.h"
#include "animation.h"

#define Button_reg  DDRB
#define Button_port PORTB
#define Left_button PB2
#define Right_button PB3
#define Up_button   PB4
#define Down_button  PB5
#define Status_Left_button   PINB2
#define Status_Right_button  PINB3
#define Status_Up_button PINB4
#define Status_Down_button PINB5

void config_UI()
{
	Button_reg  &=~((1<<Left_button)|(1<<Right_button0)|(1<<Up_button)|(1<<Down_button));
	Button_port |=((1<<Left_button)|(1<<Right_button)|(1<<Up_button)|(Down_button));
}	


/*
* Function Name :upload_custom_char
* Input : 1.index --> used to set on which CGRAM address loaction user want to store a data.
		  2.data  --> which takes the base address of and array and 
					  it is pointer so it access array element to send LCD
* Output: None
* Logic : Take array and index as parameter and 
*         send the 8 Byte of custom charactor to CGRAM
* Example Call: upload_custom_char(n,array_name);
*				where n takes value from 0 to 7
*/

void upload_custom_char(unsigned char index, unsigned char *data)
{
	unsigned char i;
	if(index<8)
	{
		lcd_wr_command(0x40 + (index*8));	//set pointer to desired address
		for(i=0;i<8;i++)            	    //write 8 Bytes of charactor
		lcd_wr_char(0,0,data[i]);
	}
}


/*
* Function Name: create_sine_char
* Input : None
* Output: None
* Logic : This function takes four array to define a charactor of "one cycle of sine wave"
* Example Call: create_sine_char();
*/

void creat_sine_char()
{
		unsigned char sineA[] = {0x03,0x04,0x08,0x10,0x00,0x00,0x00,0x00};  // define sine wave 0 to 90 degrees
		unsigned char sineB[] = {0x18,0x04,0x02,0x01,0x00,0x00,0x00,0x00};  // define sine wave 90 to 180 degrees
		unsigned char sineC[] = {0x00,0x00,0x00,0x00,0x10,0x08,0x07,0x00};  // define sine wave 180 to 270 degrees
		unsigned char sineD[] = {0x00,0x00,0x00,0x00,0x01,0x02,0x1C,0x00};  // define sine wave 270 to 360 degrees
	
		//upload the character to CGRAM
		upload_custom_char(1,sineA);
		upload_custom_char(2,sineB);
		upload_custom_char(3,sineC);
		upload_custom_char(4,sineD);
	
}

/*
* Function Name: creat_pacman_char
* Input : None
* Output: None
* Logic : This function uses 8 array to define 8 different charactor 
* Example Call: creat_pacman_char();
*/

void creat_pacman_char()
{
         //defined different charactors
		unsigned char round[]       =  {0x00,0x0E,0x1F,0x1F,0x1F,0x0E,0x00,0x00};
		unsigned char open_round[]  =  {0x00,0x0F,0x1E,0x18,0x1E,0x0F,0x00,0x00};
		unsigned char three_teeth[] =  {0x00,0x0E,0x1F,0x15,0x1F,0x15,0x00,0x00};
		unsigned char two_teeth[]   =  {0x00,0x0E,0x1F,0x15,0x1F,0x0A,0x00,0x00};
		unsigned char four_dot[]    =  {0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00};
		unsigned char fade1[]       =  {0x00,0x0E,0x1F,0x1F,0x1F,0x0E,0x00,0x00};
		unsigned char fade2[]       =  {0x00,0x0A,0x1B,0x1F,0x1F,0x0E,0x00,0x00};
		unsigned char fade3[]       =  {0x00,0x00,0x00,0x04,0x0E,0x0E,0x00,0x00};
		 
		 //upload to CGRAM
		upload_custom_char(7,round);
		upload_custom_char(1,open_round);
		upload_custom_char(2,three_teeth);
		upload_custom_char(3,two_teeth);
		upload_custom_char(4,four_dot);
		upload_custom_char(5,fade1);
		upload_custom_char(6,fade2);
		upload_custom_char(0,fade3);
}


/*
* Function Name: print_sine_wave
* Input : None
* Output: None
* Logic : used two loop to display sine charactor. As a wave is divide in two parts the 
*		  inner loop itrate 4 times and since a display has 16 columns outer loop itrate 
*		  16 times. 
* Example Call: print_sine_wave();
*/

void print_sine_wave()
{
		lcd_clear();
		unsigned char j=1;
		while(j<32)
		{
			for(unsigned char k=1;k<5;k++)
			{
				lcd_wr_char(1,j,k);
				lcd_wr_char(2,j,k);
				j++;
				_delay_ms(30);
			}
		}
		
}


/*
* Function Name: play_pacman
* Input : None
* Output: None
* Logic : here two loop are used, the fisrt loop is used to print a sckeleton of game i.e
		  the dotted path, pacman and ghost
		  Second loop is used to move pacman toward the ghost, pacman cut the dotted line using a 
		  mouth and he opens his mouth at alternate column to implement that sinario condition is used
		  inside a loop which checks column number to to open a pacmans mouth.
* Example Call:play_pacman();
*/

void play_pacman()
{
	lcd_clear();
	lcd_string(1,5,"PACMAN");
	unsigned char i;
	lcd_wr_char(2,16,3);
	
	// prints pacman, dotted path and ghost
	for(i=1;i<=15;i++)
		{
			lcd_wr_char(2,i,4);
		
			if(i%2 == 0)
			lcd_wr_char(2,16,3);
			else
			lcd_wr_char(2,16,2);
			_delay_ms(100);
		}
	
	// moves a pacman towards a ghost
	for(i=1;i<=15;i++)
		{
		
			if(i%2 == 0)
				{
					lcd_wr_char(2,i,' ');
					lcd_wr_char(2,i,1);
					lcd_wr_char(2,16,3);
					lcd_wr_char(2,i-1,' ');
					_delay_ms(75);					
				}
		
			else
				{
					lcd_wr_char(2,i,' ');
					lcd_wr_char(2,i,7);
					lcd_wr_char(2,16,2);
					lcd_wr_char(2,i-1,' ');
					_delay_ms(75);					
				}		
		    _delay_ms(150);
	    }
	// to give a faded effect at the end
	lcd_wr_char(2,15,5);
	_delay_ms(150);
	lcd_wr_char(2,15,6);
	_delay_ms(150);
	lcd_wr_char(2,15,0);
	_delay_ms(150);
	lcd_wr_char(2,15,' ');
	
}

// shows the demo of firing tank 
void fire_demo()
{
	lcd_wr_char(2,1,0);
	_delay_ms(500);
	lcd_wr_char(2,16,7);
	for(unsigned char i =2;i<16;i++)
	   {
		   lcd_wr_char(2,i,4);
		   _delay_ms(150);
		   if(i>1)
		    lcd_wr_char(2,i,' ');
		  _delay_ms(150);
	   }
	   
	   lcd_wr_char(2,16,5);
	   _delay_ms(120);
	   lcd_wr_char(2,16,6);
	   _delay_ms(120);
	   lcd_wr_char(2,16,' ');
	   
}