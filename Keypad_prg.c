/*********************************************************************/
/*********************************************************************/
/**********Author: Mohamed Rezk Bayoumi*******************************/
/**********File: Keypad_prg.c***********************************/
/**********Date: 9th sep 2022*****************************************/
/**********Version: V1*****************************************/
/*********************************************************************/
/*********************************************************************/
#include "STD_TYPES.h"
#include "bit_math.h"
#include  "DIO_interface.h"

#include <avr/delay.h>


#define KPD_PORT 0
#define COL_INIT 4
#define COL_FIN 8
#define ROW_INIT 0
#define ROW_FIN 4


u8 Kpad_U8GetKey(void)
{

    u8 Loc_U8key=20;
    
    for(u8 Loc_U8Col=0+COL_INIT;Loc_U8Col<COL_FIN;Loc_U8Col++)
    {
        DIO_VidSetPinValue(KPD_PORT,Loc_U8Col,0);
        for(u8 Loc_U8R=0+ROW_INIT;Loc_U8R<ROW_FIN;Loc_U8R++)
        {
            if(!DIO_U8GetPinValue(KPD_PORT,Loc_U8R))
            {
                Loc_U8key = Loc_U8R*4+Loc_U8Col-4;
                while(!DIO_U8GetPinValue(KPD_PORT,Loc_U8R))
                {
                
                }
                _delay_ms(5);
            }
            
            
        }
       DIO_VidSetPinValue(KPD_PORT,Loc_U8Col,1);
    }
    return Loc_U8key;
}

void Kpad_init(void)
{
    DIO_VidSetPortDirection(KPD_PORT,0b11110000);
    DIO_VidSetPortValue(KPD_PORT,0b11111111);
}
