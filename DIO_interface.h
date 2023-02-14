/*********************************************************************/
/*********************************************************************/
/**********Author: Mohamed Rezk Bayoumi*******************************/
/**********File: DIO_interface.h****************************************/
/**********Date: 2nd sep 2022*****************************************/
/**********Version: V1*****************************************/
/*********************************************************************/
/*********************************************************************/


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

void DIO_VidSetPinDirection(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Dir);
void DIO_VidSetPortDirection(u8 Copy_U8Port,u8 Copy_U8Dir);

void DIO_VidSetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Val);

void DIO_VidSetPortValue(u8 Copy_U8Port,u8 Copy_U8Val);

void DIO_VidTogglePinValue(u8 Copy_U8Port,u8 Copy_U8Pin);

u8 DIO_U8GetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin);














#endif
