/*********************************************************************/
/*********************************************************************/
/**********Author: Mohamed Rezk Bayoumi*******************************/
/**********File: DIO_prg.c****************************************/
/**********Date: 8thd sep 2022*****************************************/
/**********Version: V1.1************************************************/
/********* Desc: got rid of all the magic numbers*********************/
/**********so it's more readable *************************************/
/*********************************************************************/
/*********************************************************************/


#include "STD_TYPES.h"
#include "bit_math.h"
#include "DIO_private.h"



void DIO_VidSetPinDirection(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Dir)
{
    /*this function supposed to determine the pin direction
    *whether it's input or output 
    *PORTA_REG -> Copy_u8Port=0
    *PORTB_REG -> Copy_u8Port=1
    *PORTC_REG -> Copy_u8Port=2
    *PORTD_REG -> Copy_u8Port=3
    */
    if(LOW==Copy_U8Dir)
	{
        switch(Copy_U8Port)
        {
            case PORTA:
            {
            CLEAR_BIT(DDRA_REG,Copy_U8Pin);
            break;
            }
            case PORTB: /*PORT B*/
            {
            CLEAR_BIT(DDRB_REG,Copy_U8Pin);
            break;
            }
            case PORTC: /*PORT C*/
            {
            CLEAR_BIT(DDRC_REG,Copy_U8Pin);
            break;
            }
            case PORTD: /*PORT D*/
            {
            CLEAR_BIT(DDRD_REG ,Copy_U8Pin);
            break;
            }
            default :
            {
            	break; /*Do nothing*/

            }

        }
	}
    else
	{
        switch(Copy_U8Port)
        {
            case PORTA: /*PORT A*/
            {
            SET_BIT(DDRA_REG,Copy_U8Pin);
            break;
            }
            case PORTB: /*PORT B*/
            {
            SET_BIT(DDRB_REG,Copy_U8Pin);
            break;
            }
            case PORTC: /*PORTC_REG*/
            {
            SET_BIT(DDRC_REG,Copy_U8Pin);
            break;
            }
            case PORTD: /*PORTD_REG*/
            {
            SET_BIT(DDRD_REG,Copy_U8Pin);
            break;
            }
            default :
            	break; /*Do nothing*/
        }

    }
}









void DIO_VidSetPortDirection(u8 Copy_U8Port,u8 Copy_U8Dir)
{
    switch (Copy_U8Port)
    {
        case PORTA: /*PORT A */
        {
        DDRA_REG=Copy_U8Dir;
        break;
        }
        case PORTB: /*PORTB_REG*/
        {
        DDRB_REG=Copy_U8Dir;
        break;
        }
        case PORTC: /*PORTC_REG*/
        {
        DDRC_REG=Copy_U8Dir;
        break;
        }
        case PORTD: /*PORTD_REG*/
        {
        DDRD_REG=Copy_U8Dir;
        break;
        }
        default:
         break; /*Do nothing*/

    }
}

void DIO_VidSetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Val)
{
    if(Copy_U8Val==LOW)
    {
        switch(Copy_U8Port)
        {
            case PORTA: /*PORT A */
            {
            CLEAR_BIT(PORTA_REG,Copy_U8Pin);
            break;
            }
            case PORTB: /*PORT B*/
            {
            CLEAR_BIT(PORTB_REG,Copy_U8Pin);
            break;
            }
            case PORTC: /*PORT C */
            {
            CLEAR_BIT(PORTC_REG,Copy_U8Pin);
            break;
            }
            case PORTD: /*PORTD_REG*/
            {
            CLEAR_BIT(PORTD_REG,Copy_U8Pin);
            break;
            }
            default :
            {
            	break; /*Do nothing*/
            }
        }
    }

    else if(Copy_U8Val==HIGH)
    {
        switch(Copy_U8Port)
        {
            case PORTA: /*PORT A */
            SET_BIT(PORTA_REG,Copy_U8Pin);
            break;
            case PORTB: /*PORT B*/
            SET_BIT(PORTB_REG,Copy_U8Pin);
            break;
            case PORTC: /*PORT C */
            SET_BIT(PORTC_REG,Copy_U8Pin);
            break;
            case PORTD: /*PORT D */
            SET_BIT(PORTD_REG,Copy_U8Pin);
            break;
            default :
            	break; /*do nothing*/
        }
     }
}



void DIO_VidSetPortValue(u8 Copy_U8Port,u8 Copy_U8Val)
{
	switch (Copy_U8Port)
		{
			case PORTA:
			{
				PORTA_REG= Copy_U8Val;
				break;
			}
			case PORTB:
			{
				PORTB_REG=  Copy_U8Val;
				break;
			}
			case PORTC:
			{
				PORTC_REG= Copy_U8Val;
				break;
			}
			case PORTD:
			{
				PORTD_REG= Copy_U8Val;
				break;
			}
			default:;

}
}

void DIO_VidTogglePinValue(u8 Copy_U8Port,u8 Copy_U8Pin)
{
    switch(Copy_U8Port)
    {
        case PORTA: /*PORT A*/
        TOGGLE_BIT(PORTA_REG,Copy_U8Pin);
        break;
        case PORTB: /*PORT B*/
        TOGGLE_BIT(PORTB_REG,Copy_U8Pin);
        break;
        case PORTC: /*PORT C*/
        TOGGLE_BIT(PORTC_REG,Copy_U8Pin);
        break;
        case PORTD: /*PORT D*/
        TOGGLE_BIT(PORTD_REG,Copy_U8Pin);
        break;
        default:
        ; 
    }
}

u8 DIO_U8GetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin)
{
    u8 Loc_PinVal;
    switch(Copy_U8Port)
    {
        case PORTA: /*PIN A*/
        Loc_PinVal=GET_BIT(PINA_REG,Copy_U8Pin);
        break;
        case PORTB: /*PIN B*/
        Loc_PinVal=GET_BIT(PINB_REG,Copy_U8Pin);
        break;
        case PORTC: /*PORT C*/
        Loc_PinVal=GET_BIT(PINC_REG,Copy_U8Pin);
        break;
        case PORTD: /*PORT D*/
        Loc_PinVal=GET_BIT(PIND_REG,Copy_U8Pin);
        break;
        default:
         break; /*do nothing*/ 
    }
    return Loc_PinVal;
}
