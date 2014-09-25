/*
 * lcd12864.h
 *
 *  Created on: 2014-2-28
 *      Author: ken
 */

#ifndef LCD12864_H_
#define LCD12864_H_

//#include "msp430.h"
#include "stdint.h"

#define CS_SET  PDout(12)=1
#define RST_SET PDout(10)=1
#define RS_SET  PDout( 8)=1
#define SDA_SET PBout(14)=1
#define SCL_SET PBout(12)=1
 
#define CS_CLR  PDout(12)=0
#define RST_CLR PDout(10)=0
#define RS_CLR  PDout( 8)=0
#define SDA_CLR PBout(14)=0
#define SCL_CLR PBout(12)=0

void initial_lcd(void);
void waitkey(void);
void lcd_address(unsigned char page, unsigned char column);
void clear_screen(void);
void full_display(void);
void display_string_5x7(unsigned int page, unsigned int column, unsigned char *text);
#endif /* LCD12864_H_ */
