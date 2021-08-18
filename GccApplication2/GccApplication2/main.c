/*
 * CharacterPrint_H_Offline_1.c
 *
 * Created: 4/13/2021 12:22:55 PM
 * Author : ASUS
 */ 
#define F_CPU 4000000UL
 
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

int shift_delay = 1;
int flag_simulation = 1;
int flag_simulation1 = 0;
int num, remainder;
int play_flag = 1;
int stuck = 0;
int score = 0; 
unsigned char flag = 1;
unsigned char jump_flag = 1;
unsigned char row = 116; 
unsigned char col = 119; unsigned char col1 = 119;
unsigned char human_leg_col= 0b00110000;
unsigned char human_leg_row;
unsigned char obj_leg_col;
unsigned char obj_top_row = 0b00110100;
unsigned char obj_leg_col1; 
unsigned char obj_top_row1 = 0b00110101;
unsigned char human_c[4] = {0b00000000,  0b00000001, 0b00000010, 0b00000011};
unsigned char human_r[8] = {0b00110000,0b00110001,0b00110010,0b00110011,0b00110100,0b00110101,0b00110110,0b00110111}; 
char score_array[100];

void create_human()
{	
	human_leg_row = human_r[7];
	obj_leg_col = col;
	obj_leg_col1 = col1;
	
	if(flag_simulation==1 && play_flag==1) simulate();
	if(flag_simulation1==1 && play_flag==1 && score>100) simulate1();
	
	// This block Represents the Human
	// ---------------
	PORTA = human_c[0];
	PORTB = human_r[4];
	_delay_ms(1);
	
	PORTA = human_c[0];
	PORTB = human_r[7];
	_delay_ms(1);
	
	PORTA = human_c[1];
	for(int j = 1; j  <= 6; j++)
	{
		PORTB = human_r[j];
		_delay_ms(1);
	}
	
	PORTA = human_c[2];
	for(int j = 1; j  <= 6; j++)
	{
		if(j==2) continue;
		PORTB = human_r[j];
		_delay_ms(1);
	}
	
	PORTA = human_c[3];
	PORTB = human_r[4];
	_delay_ms(1);
	
	PORTA = human_c[3];
	PORTB = human_r[7];
	_delay_ms(1);
	// ---------------

}

void default_position()
{
	human_c[0] = 0b00000000; human_c[1] =0b00000001 ; human_c[2] = 0b00000010; human_c[3] = 0b00000011;
	human_r[0] = 0b00110000; human_r[1] =0b00110001 ; human_r[2] =0b00110010 ; human_r[3] =0b00110011 ; human_r[4] =0b00110100 ; human_r[5] =0b00110101 ; human_r[6] =0b00110110 ; human_r[7] =0b00110111 ;
}
void jump_1()
{
	human_c[0] = 0b00000000; human_c[1] =0b00000001 ; human_c[2] = 0b00000010; human_c[3] = 0b00000011;
	human_r[0] = 0b11000111; human_r[1] =0b00110000 ; human_r[2] =0b00110001 ; human_r[3] =0b00110010 ; human_r[4] =0b00110011 ; human_r[5] =0b00110100 ; human_r[6] =0b00110101 ; human_r[7] =0b00110110 ;
}

void jump_2()
{
	human_c[0] = 0b00000000; human_c[1] =0b00000001 ; human_c[2] = 0b00000010; human_c[3] = 0b00000011;
	human_r[0] = 0b11000110,human_r[1] = 0b11000111; human_r[2] =0b00110000 ; human_r[3] =0b00110001 ; human_r[4] =0b00110010 ; human_r[5] =0b00110011 ; human_r[6] =0b00110100 ; human_r[7] =0b00110101 ;	
}

void jump_3()
{
	human_c[0] = 0b00000000; human_c[1] =0b00000001 ; human_c[2] = 0b00000010; human_c[3] = 0b00000011;
	human_r[0] = 0b11000101;human_r[1] = 0b11000110,human_r[2] = 0b11000111; human_r[3] =0b00110000 ; human_r[4] =0b00110001 ; human_r[5] =0b00110010 ; human_r[6] =0b00110011 ; human_r[7] =0b00110100 ;
}

void jump_4()
{
	human_c[0] = 0b00000000; human_c[1] =0b00000001 ; human_c[2] = 0b00000010; human_c[3] = 0b00000011;
	human_r[0] = 0b11000100; human_r[1] = 0b11000101;human_r[2] = 0b11000110; human_r[3] = 0b11000111; human_r[4] =0b00110000 ; human_r[5] =0b00110001 ; human_r[6] =0b00110010 ; human_r[7] =0b00110011 ;
}

void jump_5()
{
	human_c[0] = 0b00000000; human_c[1] =0b00000001 ; human_c[2] = 0b00000010; human_c[3] = 0b00000011;
	human_r[0] = 0b11000011; human_r[1] = 0b11000100; human_r[2] = 0b11000101;human_r[3] = 0b11000110; human_r[4] = 0b11000111; human_r[5] =0b00110000 ; human_r[6] =0b00110001 ; human_r[7] =0b00110010 ;
}

void jump_6()
{
	human_c[0] = 0b00000000; human_c[1] =0b00000001 ; human_c[2] = 0b00000010; human_c[3] = 0b00000011;
	human_r[0] = 0b11000010; human_r[1] = 0b11000011; human_r[2] = 0b11000100; human_r[3] = 0b11000101;human_r[4] = 0b11000110; human_r[5] = 0b11000111; human_r[6] =0b00110000 ; human_r[7] =0b00110001 ;
}

void jump_7()
{
	human_c[0] = 0b00000000; human_c[1] =0b00000001 ; human_c[2] = 0b00000010; human_c[3] = 0b00000011;
	human_r[0] = 0b11000001; human_r[1] = 0b11000010; human_r[2] = 0b11000011; human_r[3] = 0b11000100; human_r[4] = 0b11000101;human_r[5] = 0b11000110; human_r[6] = 0b11000111; human_r[7] =0b00110000 ;
}

void jump()
{	
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_1();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_2();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_3();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_4();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_5();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_6();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_7();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	// Reverse Order
	jump_7();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_6();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_5();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_4();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_3();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_2();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	jump_1();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	
	default_position();
	create_human();
	score++;
	show_score();
	_delay_ms(8);
	if(stuck!=1) score++;

}

void simulate()
{
	//----collision check
	if(obj_leg_col-human_leg_col<=3 && human_leg_row-obj_top_row>0)
	{
		collision();
	}

	//---------
	
	if(col > 110)
	{
		row = 117;
	}
	else if(col > 55)
	{
		row = 61;
	}
	else if(col > 46)
	{
		row = 53;
	}
	else row = 117;
	
	PORTA = col;
	PORTB = row;
	_delay_ms(1);
	
	row++;
	PORTA = col;
	PORTB = row;
	_delay_ms(1);
	
	row++;
	PORTA = col;
	PORTB = row;
	_delay_ms(1);

	col--;
	if(col == 111)
	{
		col = 0b00111111;
		row = 60;
	}
	
	if(col == 52 )
	{
		flag_simulation1 = 1;
	}

	if(col == 55)
	{
		row = 53;
	}
	
	if(col == 47)
	{
		col = 119;
		row = 117;
		
		if(score>200)
		{
			flag_simulation = 0;
		}
		
		
		if(score>300)
		{
			flag_simulation = 1;
		}
		
		
		if(score>400)
		{
			flag_simulation = 0;
		}
		
		
		if(score>500)
		{
			flag_simulation = 1;
		}
		
		
		if(score>600)
		flag_simulation = 0;
		
		if(score>700)
		flag_simulation = 1;
		
		if(score>800)
		flag_simulation = 0;
		
		if(score>900)
		flag_simulation = 1;
		
	}
	
}


void simulate1()
{
	//----collision check
	if(obj_leg_col1-human_leg_col<=3 && human_leg_row-obj_top_row1>0)
	{
		collision();
	}

	//---------
	
	if(col1 > 110)
	{
		row = 116;
	}
	else if(col1 > 55)
	{
		row = 60;
	}
	else if(col1 > 46)
	{
		row = 52;
	}
	else row = 116;
	
	PORTA = col1;
	PORTB = row;
	_delay_ms(1);
	
	row++;
	PORTA = col1;
	PORTB = row;
	_delay_ms(1);
	
	row++;
	PORTA = col1;
	PORTB = row;
	_delay_ms(1);
	
	row++;
	PORTA = col1;
	PORTB = row;
	_delay_ms(1);

col1--;


if(col1 == 111)
{	
	col1 = 0b00111111;
	row = 0b00111111;
}

if(col1 == 52)
{
	flag_simulation = 1;
}

if(col1 == 55)
{
	row = 52;
}

if(col1 == 47)
{
	col1 = 119;
	row = 116;
	flag_simulation1 = 0;
	
}
	
}

void obstacle_move()
{
	//row = 116;
	//col = 119;
	for(int loop = 0; loop < 24; loop++)
	{	

		for(int i = 0; i < 10; i++)
		{
			
			if(jump_flag == 1)
			{
				jump();
				jump_flag = 0;
			}
			else 
			{
				create_human();
				_delay_ms(8);
			}
				
			score++;
			show_score();
			
			for(int w = 0; w < shift_delay; w++)
			_delay_ms(1);
			
		}
		    
		
			
	}
	
	
	
}

void collision()
{	
	stuck = 1;
	
	while (1)
	{
		//---- display GAME OVER 
		PORTA = 48;
		PORTB = 51;
		_delay_ms(1);
		
		PORTA = 49;
		PORTB = 50;
		_delay_ms(1);
		
		PORTA = 49;
		PORTB = 52;
		_delay_ms(1);
		
		PORTA = 50;
		PORTB = 49;
		_delay_ms(1);
		
		PORTA = 50;
		PORTB = 53;
		_delay_ms(1);
		
		PORTA = 51;
		PORTB = 50;
		_delay_ms(1);
		
		PORTA = 51;
		PORTB = 52;
		_delay_ms(1);
		
		PORTA = 52;
		PORTB = 51;
		_delay_ms(1);
		
		PORTA = 54;
		PORTB = 49;
		_delay_ms(1);
		
		PORTA = 54;
		PORTB = 50;
		_delay_ms(1);
		
		PORTA = 54;
		PORTB = 51;
		_delay_ms(1);
		
		PORTA = 55;
		PORTB = 52;
		_delay_ms(1);
		
		PORTA = 56;
		PORTB = 61;
		_delay_ms(1);
		
		PORTA = 58;
		PORTB = 57;
		_delay_ms(1);
		
		PORTA = 58;
		PORTB = 58;
		_delay_ms(1);
		
		PORTA = 58;
		PORTB = 59;
		_delay_ms(1);
		
		PORTA = 57;
		PORTB = 60;
		_delay_ms(1);
		
		
		PORTA = 60;
		PORTB = 57;
		_delay_ms(1);
		
		PORTA = 60;
		PORTB = 58;
		_delay_ms(1);
		
		PORTA = 60;
		PORTB = 59;
		_delay_ms(1);
		
		PORTA = 60;
		PORTB = 60;
		_delay_ms(1);
		
		PORTA = 60;
		PORTB = 61;
		_delay_ms(1);
		
		PORTA = 61;
		PORTB = 57;
		_delay_ms(1);
		
		PORTA = 61;
		PORTB = 59;
		_delay_ms(1);
		
		PORTA = 61;
		PORTB = 61;
		_delay_ms(1);
		
		PORTA = 62;
		PORTB = 57;
		_delay_ms(1);
		
		PORTA = 62;
		PORTB = 59;
		_delay_ms(1);
		
		PORTA = 62;
		PORTB = 61;
		_delay_ms(1);
		
		PORTA = 63;
		PORTB = 57;
		_delay_ms(1);
		
		
		PORTA = 63;
		PORTB = 61;
		_delay_ms(1);
		
		PORTA = 113;
		PORTB = 113;
		_delay_ms(1);
		
		PORTA = 113;
		PORTB = 114;
		_delay_ms(1);
		
		PORTA = 113;
		PORTB = 115;
		_delay_ms(1);
		
		PORTA = 113;
		PORTB = 116;
		_delay_ms(1);
		
		PORTA = 113;
		PORTB = 117;
		_delay_ms(1);
		
		PORTA = 114;
		PORTB = 113;
		_delay_ms(1);
		
		PORTA = 114;
		PORTB = 115;
		_delay_ms(1);
		
		PORTA = 115;
		PORTB = 113;
		_delay_ms(1);
		
		PORTA = 115;
		PORTB = 115;
		_delay_ms(1);
		
		PORTA = 115;
		PORTB = 116;
		_delay_ms(1);
		
		PORTA = 116;
		PORTB = 114;
		_delay_ms(1);
		
		PORTA = 116;
		PORTB = 117;
		_delay_ms(1);
		
		// Top Part
		
		PORTA = 192;
		PORTB = 196;
		_delay_ms(1);
		
		PORTA = 193;
		PORTB = 195;
		_delay_ms(1);
		
		PORTA = 193;
		PORTB = 197;
		_delay_ms(1);
		
		PORTA = 194;
		PORTB = 194;
		_delay_ms(1);
		
		PORTA = 194;
		PORTB = 196;
		_delay_ms(1);
		
		PORTA = 194;
		PORTB = 198;
		_delay_ms(1);
		
		PORTA = 195;
		PORTB = 196;
		_delay_ms(1);
		
		PORTA = 195;
		PORTB = 197;
		_delay_ms(1);
		
		PORTA = 196;
		PORTB = 196;
		_delay_ms(1);
		
		PORTA = 198;
		PORTB = 196;
		_delay_ms(1);
		
		PORTA = 198;
		PORTB = 197;
		_delay_ms(1);
		
		PORTA = 198;
		PORTB = 198;
		_delay_ms(1);
		
		
		PORTA = 199;
		PORTB = 195;
		_delay_ms(1);
		
		PORTA = 199;
		PORTB = 196;
		_delay_ms(1);
		
		PORTA = 200;
		PORTB = 202;
		_delay_ms(1);
		
		PORTA = 200;
		PORTB = 204;
		_delay_ms(1);
		
		PORTA = 201;
		PORTB = 202;
		_delay_ms(1);
		
		PORTA = 201;
		PORTB = 204;
		_delay_ms(1);
		
		PORTA = 202;
		PORTB = 203;
		_delay_ms(1);
		
		PORTA = 202;
		PORTB = 204;
		_delay_ms(1);
		
		PORTA = 203;
		PORTB = 204;
		_delay_ms(1);
		
		PORTA = 203;
		PORTB = 205;
		_delay_ms(1);
		
		PORTA = 203;
		PORTB = 206;
		_delay_ms(1);
		
		PORTA = 205;
		PORTB = 202;
		_delay_ms(1);
		
		PORTA = 205;
		PORTB = 203;
		_delay_ms(1);
		
		PORTA = 205;
		PORTB = 204;
		_delay_ms(1);
		
		PORTA = 205;
		PORTB = 205;
		_delay_ms(1);
		
		PORTA = 205;
		PORTB = 206;
		_delay_ms(1);
		
		PORTA = 206;
		PORTB = 203;
		_delay_ms(1);
		
		PORTA = 207;
		PORTB = 204;
		_delay_ms(1);
		
		PORTA = 208;
		PORTB = 211;
		_delay_ms(1);
		
		PORTA = 209;
		PORTB = 210;
		_delay_ms(1);
		
		PORTA = 209;
		PORTB = 211;
		_delay_ms(1);
		
		PORTA = 209;
		PORTB = 212;
		_delay_ms(1);
		
		PORTA = 209;
		PORTB = 213;
		_delay_ms(1);
		
		PORTA = 209;
		PORTB = 214;
		_delay_ms(1);
		
		PORTA = 211;
		PORTB = 210;
		_delay_ms(1);
		
		PORTA = 211;
		PORTB = 211;
		_delay_ms(1);
		
		PORTA = 211;
		PORTB = 212;
		_delay_ms(1);
		
		PORTA = 211;
		PORTB = 213;
		_delay_ms(1);
		
		PORTA = 211;
		PORTB = 214;
		_delay_ms(1);
		
		PORTA = 212;
		PORTB = 210;
		_delay_ms(1);
		
		PORTA = 212;
		PORTB = 212;
		_delay_ms(1);
		
		PORTA = 212;
		PORTB = 214;
		_delay_ms(1);
		
		PORTA = 213;
		PORTB = 210;
		_delay_ms(1);
		
		PORTA = 213;
		PORTB = 214;
		_delay_ms(1);
		
		
		//----


	}
	

}

void show_score()
{
	sprintf(score_array,"%d",score);
	LCD_cmd(0x88); //Refreshes the LCD Display for Score only
	LCD_Write_String(score_array);
	
}

ISR(INT1_vect){
	if (jump_flag==0)
	{
		jump_flag = 1;
	}
	else{
		jump_flag = 0;
	}
}

ISR(INT2_vect){
	if (play_flag==0)
	{
		play_flag = 1;
	}
	else{
		play_flag = 0;
	}
}

int main(void)
{	

	
	DDRA = 0xff;		/// led column active -- 1
						/// led row active -- 0
						//A COL, B ROW
	DDRB = 0xff;
	int k=0;		
	
	//3 -- 011
	//4 -- 
	//GICR =(1<<INT1)
	GICR =GICR | 11000000;
	MCUCR = MCUCR | 0b00000101;
	sei();
	
	// --- LCD DISPLAY
	DDRC = 0xFF;
	DDRD = 0xE0;
	init_LCD();
	_delay_ms(10);
	LCD_cmd(0x0C);
	_delay_ms(10);
	sprintf(score_array,"%d",score);
	LCD_Write_String("SCORE = ");
	_delay_ms(50);
	LCD_Write_String(score_array);
	_delay_ms(100);
	LCD_cmd(0xC0);
	_delay_ms(100);
	// ---
	
	jump_flag = 0;
    while (1) 
    {
		if(play_flag==1)
		{
			obstacle_move();
		}
		else
		{
			create_human();
			
		}
		
		
			
				
		
	} // While loop ends
}

