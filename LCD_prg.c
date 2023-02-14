/*********************************************************************/
/*********************************************************************/
/**********Author: Mohamed Rezk Bayoumi*******************************/
/**********File: LCD_prg.c****************************************/
/**********Date: 2nd sep 2022*****************************************/
/**********Version: V1.1*****************************************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LCD_private.h"
#include "LCD_cfg.h"
#include <avr/delay.h>


void LCD_VidWriteData(u8 Copy_U8Data)
{
	/*this function supposed to display data on the LCD*/
	DIO_VidSetPinValue(CONTROL_PORT,RS,1);
	DIO_VidSetPinValue(CONTROL_PORT,RW,0);

	DIO_VidSetPortValue(DATA_PORT,Copy_U8Data);

	DIO_VidSetPinValue(CONTROL_PORT,EN,1);
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,EN,0);
	_delay_ms(2);
}




void LCD_VidSendComm(u8 Copy_U8Comm)
{
	DIO_VidSetPinValue(CONTROL_PORT,RW,0);
	DIO_VidSetPinValue(CONTROL_PORT,RS,0);
	
	

	DIO_VidSetPortValue(DATA_PORT,Copy_U8Comm);
	
	
	
	DIO_VidSetPinValue(CONTROL_PORT,EN,1);
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,EN,0);
	_delay_ms(2);
}

void LCD_VidInit(void)
{
	DIO_VidSetPinDirection(CONTROL_PORT,RS,1);
	DIO_VidSetPinDirection(CONTROL_PORT,RW,1);
	DIO_VidSetPinDirection(CONTROL_PORT,EN,1);
	DIO_VidSetPortDirection(DATA_PORT,0xff);

	_delay_ms(35);
	LCD_VidSendComm(FUNSET);
	_delay_ms(1);
	LCD_VidSendComm(ON_OFF);
	_delay_ms(1);
	LCD_VidSendComm(DIS_CLR);
	_delay_ms(15);
	LCD_VidSendComm(0b00000110);
	_delay_ms(2);
}
void LCD_VidGoToPos(u8 Copy_U8X,u8 Copy_U8Y)
{
		switch(Copy_U8Y)
		{
			case 0:
			LCD_VidSendComm((Copy_U8X&0x0f)|0x80);
			break;
			case 1: 
			LCD_VidSendComm((Copy_U8X&0x0f)|0xc0);
			break;
			default:
			break;
		}

}
void LCD_VidSendString(u8 * Str)
{
	u8 i=0;
	while(Str[i]!='\0')
	{
		LCD_VidWriteData(Str[i]);
		i++;
	}
}


 void LCD_VidPrintNum(u32 copy_u32Number)
{
	u8 Local_u8Digit;
	u8 Local_u8Counter=0;
	s8 Local_u8Counter2;
	static u8 Local_ArrayOfChar[10]={'0','1','2','3','4','5','6','7','8','9'};
	static u8 Local_ArrayOfDigits[10];

	if(copy_u32Number==0)
	{
		LCD_VidWriteData(Local_ArrayOfChar[0]);
	}
	else
	{

		while(copy_u32Number>0)
		{
			Local_u8Digit=copy_u32Number%10;
			copy_u32Number=copy_u32Number/10;
			Local_ArrayOfDigits[Local_u8Counter]=Local_ArrayOfChar[Local_u8Digit];
			Local_u8Counter++;
		}

		for(Local_u8Counter2=Local_u8Counter-1;Local_u8Counter2>=0;Local_u8Counter2--)
		{
			LCD_VidWriteData(Local_ArrayOfDigits[Local_u8Counter2]);
		}
	}
}


void LCD_VidCustomChar(u8 * chr,u8 Copy_U8index)
{
	LCD_VidSendComm(0b01000000 + (8*Copy_U8index));
	for(u8 i=0;i<8;i++)
	{
		LCD_VidWriteData(chr[i]);
	}
}


void LCD_VidWriteCustomChar(u8 Copy_U8Char,u8 Copy_U8X,u8 Copy_U8Y)
{
	LCD_VidGoToPos(Copy_U8X,Copy_U8Y);
	LCD_VidWriteData(Copy_U8Char);	

	
}

void LCD_VidClearDisplay(void)
{
	LCD_VidSendComm(1);
	_delay_ms(2);
}



