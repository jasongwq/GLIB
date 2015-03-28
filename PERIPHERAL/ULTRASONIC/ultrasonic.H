#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
#include "sys.h"
#include "stm32_config.h"
#include "G32_timer_cap.h"
#include "Ultrasonic_Config.h"

#define TRIG1_H GPIO_SetBits  (ULTRASONIC_TRIG1_GPIO,ULTRASONIC_TRIG1_PIN)
#define TRIG1_L GPIO_ResetBits(ULTRASONIC_TRIG1_GPIO,ULTRASONIC_TRIG1_PIN)
#define TRIG2_H GPIO_SetBits  (ULTRASONIC_TRIG2_GPIO,ULTRASONIC_TRIG2_PIN)
#define TRIG2_L GPIO_ResetBits(ULTRASONIC_TRIG2_GPIO,ULTRASONIC_TRIG2_PIN)
//#define TRIG_H GPIO_SetBits  (ULTRASONIC_TRIG_GPIO,ULTRASONIC_TRIG_PIN)
//#define TRIG_L GPIO_ResetBits(ULTRASONIC_TRIG_GPIO,ULTRASONIC_TRIG_PIN)

extern void Ultrasonic_Init(void);
u32 ultrasonic (void);
extern u8		TIM4CH1_CAPTURE_STA;		    				
extern u16	TIM4CH1_CAPTURE_VAL;

#endif


