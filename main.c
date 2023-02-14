/*
 * main.c

 *
 *  Created on: Oct 12, 2022
 *      Author: mrezk
 */

#include "STD_TYPES.h"
#include "bit_math.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "Keypad_interface.h"
#include "stdlib.h"
#include <avr/delay.h>


/* Keypad Numbering (0-15)
 * ***1***
 * 4*****6 Directions
 * ***9***
 *
 *
 * */

#define RIGHT 6
#define LEFT 4
#define UP 1
#define DOWN 9
void Lcd_vidDisplay_Custom_Character_Array(char  LCD_Matrix[16][80]);

u8 Global_U8SnakeArr[8];
u8 Global_U8LCDArr[16][80];
u8 direction=RIGHT;
void main(void)
{

	u8 snake_head=2;
	s8 snake_row[80]={1,1,1};
	s8 snake_col[80]={3,4,5};
	u8 Loc_U8EggRow=rand()%16;
	u8 Loc_U8EggCol=rand()%80;
	u8 Egg_stat=1;
	u8 button=0;
	u8 score=1;
	LCD_VidInit();
	Kpad_init();
	u8 Egg_iterator;




	while (1)
	{
		_delay_ms(50);
		LCD_VidClearDisplay();
		_delay_ms(2);

		
		for(u8 iterator=0;iterator<=snake_head;snake_head++)
		{
			Global_U8LCDArr[snake_row[iterator]][snake_col[iterator]]=1;

		}
		Lcd_vidDisplay_Custom_Character_Array(Global_U8LCDArr);


		Egg_iterator=0;
		while(Egg_stat==1&&Egg_iterator<=snake_head)
		{
			if(snake_row[Egg_iterator]==Loc_U8EggRow&&snake_col[Egg_iterator]==Loc_U8EggCol)
			{
				Loc_U8EggCol=rand()%80;
				Loc_U8EggRow=rand()%16;
			}
			if(Egg_iterator==snake_head)
			{
				Egg_stat=0;
			}


			Egg_iterator++;
		}

		Global_U8LCDArr[Loc_U8EggRow][Loc_U8EggCol]=1;

		//moving the snake algorithm
		Global_U8LCDArr[snake_row[0]][snake_col[0]]=0;
		for (u8 i = 0; i<=snake_head;i++)
		{
			snake_col[i]=snake_col[i+1];
			snake_row[i]=snake_row[i+1];
		}

		button=Kpad_U8GetKey();
		if(button==RIGHT||button==LEFT||button==UP||button==DOWN)
		{
			switch(button)
			{
			case UP:
				if(direction==UP||direction==LEFT||direction==RIGHT)
				{
					direction=UP;
					snake_row[snake_head]--;
				}
				break;
			case RIGHT:
				if(direction==UP||direction==DOWN||direction==RIGHT)
				{
					direction=RIGHT;
					snake_col[snake_head]++;

				}
				break;
			case DOWN:
				if(direction==LEFT||direction==DOWN||direction==RIGHT)
				{
					direction=DOWN;
					snake_row[snake_head]++;
				}
				break;
			case LEFT:
				if(direction==UP||direction==DOWN||direction==LEFT)
				{
					direction=LEFT;
					snake_col[snake_head]--;
				}
			}
		}
		else
		{
			switch(direction)
			{
			case UP:
				snake_row[snake_head]--;
				break;
			case RIGHT:
				snake_col[snake_head]++;
				break;
			case DOWN:
				snake_row[snake_head]++;
				break;
			case LEFT:
				snake_col[snake_head]--;
				break;
			}
		}
		switch(snake_col[snake_head])
		{
		case -1:
			if(direction==LEFT)
			{
				snake_col[snake_head]=79;
			}
			break;
		case 80:
			if(direction==RIGHT)
			{
				snake_col[snake_head]=0;
			}
			break;
		}
		switch(snake_row[snake_head])
		{
		case -1:
			if(direction==UP)
			{
				snake_row[snake_head]=15;
			}
			break;
		case 15:
			if(direction==DOWN)
			{
				snake_row[snake_head]=0;
			}
			break;
		}
		if((Loc_U8EggRow==snake_row[snake_head])&&(snake_col[snake_head]==Loc_U8EggCol)&&Egg_stat==0)
		{
			Egg_stat=1;
			Loc_U8EggRow=rand()%16;
			Loc_U8EggCol=rand()%80;
			snake_head++;
		}








	}
}









void Lcd_vidDisplay_Custom_Character_Array(char  LCD_Matrix[16][80])
{
	u8 Flag_Char_Exist = 0;
	u8 Row;
	u8 Reg=0;
	u8 Character_order = 0;

	for(u8 i=0;i<80;i=i+5)
	{
		for(u8 j=0;j<16;j++)
		{
			for(u8 z=i;z<i+5;z++)
			{
				if(LCD_Matrix[j][z] == 1)
				{
					Flag_Char_Exist = 1;
					if(j>=8)
					{
						Row = 1;
					}
					break;
				}
			}
			if(Flag_Char_Exist == 1)
			{
				break;
			}
		}

		if(Flag_Char_Exist == 1)
		{
			for(u8 j=0;j<9;j++)
			{
				u8 Col = 4;
				for(u8 z=i;z<i+5;z++)
				{
					if(LCD_Matrix[j][z] == 1)
					{
						SET_BIT(Reg,Col);
					}
					Col--;
				}
				Global_U8SnakeArr[j] = Reg;
				Reg = 0;
			}
			//LCD_VidDrawSpecialChar(Character_order , Char);
			LCD_VidCustomChar(Global_U8SnakeArr,Character_order);
			LCD_VidGoToPos(i/5 , 0);
			LCD_VidWriteData(Character_order);
			Character_order++;
			for(u8 j=0;j<9;j++)
			{
				u8 Col = 4;
				for(u8 z=i;z<i+5;z++)
				{
					if(LCD_Matrix[j+8][z] == 1)
					{
						SET_BIT(Reg,Col);
					}
					Col--;
				}
				Global_U8SnakeArr[j] = Reg;
				Reg = 0;
			}
			LCD_VidCustomChar( Global_U8SnakeArr,Character_order );
			LCD_VidGoToPos(i/5 , 1);
			LCD_VidWriteData(Character_order);
			Character_order++;
			Flag_Char_Exist = 0;
		}
	}
	Character_order = 0;
}
