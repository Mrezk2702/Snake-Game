#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
void LCD_VidInit(void);

void LCD_VidSendComm(u8 Copy_U8Comm);

void LCD_VidWriteData(u8 Copy_U8Data);
void LCD_VidGoToPos(u8 Copy_U8X,u8 Copy_U8Y);
void LCD_VidSendString(u8 * Str);
void LCD_VidCustomChar(u8 * chr,u8 Copy_U8index);
 void LCD_VidPrintNum(u32 copy_u32Number);
 void LCD_VidWriteCustomChar(u8 Copy_U8Char,u8 Copy_U8X,u8 Copy_U8Y);
 void LCD_VidClearDisplay(void);
 #endif