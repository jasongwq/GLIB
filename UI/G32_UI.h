#ifndef __G32_UI_
#define __G32_UI_

typedef enum
{
    click = 0x01
} command;

typedef struct
{
    int poix;
    int poiy;
    int Width;
    int high;
    char Caption[125];
    command Command;
} AE_BUTTON;
typedef struct
{
    int poix;
    int poiy;
	  int l_poix;
    int l_poiy;
	
    int Width;
    int high;
    char Caption[125];
    command Command;
} AE_SLIDER;

typedef struct
{
    int (*func)(AE_BUTTON*);
    AE_BUTTON Attribute;
} AX_BUTTON;
typedef struct
{
    int (*func)(AE_SLIDER*);
    AE_SLIDER Attribute;
} AX_SLIDER;

int UI_Button(AX_BUTTON Activex[],int num);
int UI_Slider(AX_SLIDER Activex[],int num);


extern AX_BUTTON Ax_Button[];
extern AX_SLIDER Ax_Slider[];


#endif
