#include "G32_UI.h"
#include "lcd.h"
#include "touch.h"

AX_BUTTON Ax_Button[1];
AX_SLIDER Ax_Slider[2];

int UI_Button(AX_BUTTON Activex[], int num)
{
    if (Touch(Activex[num].Attribute.poix, Activex[num].Attribute.poiy, Activex[num].Attribute.Width, Activex[num].Attribute.high))
    {
        while (tp_dev.sta & TP_PRES_DOWN)
            tp_dev.scan(0);
        Activex[num].func(&Activex[num].Attribute);

        LCD_DrawRectangle(
            Activex[num].Attribute.poix,
            Activex[num].Attribute.poiy,
            Activex[num].Attribute.poix + Activex[num].Attribute.Width,
            Activex[num].Attribute.poiy + Activex[num].Attribute.high);
        LCD_ShowString(
            Activex[num].Attribute.poix + 1,
            Activex[num].Attribute.poiy + 1,
            Activex[num].Attribute.Width,
            Activex[num].Attribute.high,
            16,
            Activex[num].Attribute.Caption);
    }
    return 0;
}
int UI_Slider(AX_SLIDER Activex[], int num)
{
    if (Touch(Activex[num].Attribute.poix, Activex[num].Attribute.poiy, Activex[num].Attribute.Width, Activex[num].Attribute.high))
    {
        for(int i=10;(i<10)&&(tp_dev.sta & TP_PRES_DOWN)&&(Touch(Activex[num].Attribute.poix, Activex[num].Attribute.poiy, Activex[num].Attribute.Width, Activex[num].Attribute.high));i++)
        {
            Activex[num].func(&Activex[num].Attribute);
						tp_dev.scan(0);
        }
				LCD_ShowString(
                Activex[num].Attribute.poix + 1,
                Activex[num].Attribute.poiy + 1,
                Activex[num].Attribute.Width,
                Activex[num].Attribute.high,
                16,
                Activex[num].Attribute.Caption);
				LCD_DrawRectangle(
                Activex[num].Attribute.poix,
                Activex[num].Attribute.poiy,
                Activex[num].Attribute.poix + Activex[num].Attribute.Width,
                Activex[num].Attribute.poiy + Activex[num].Attribute.high);
				Activex[num].func(&Activex[num].Attribute);
    }
    return 0;
}
