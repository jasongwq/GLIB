#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H
#include "sys.h"

//LED端口定义
#define MOTOR0_0 PDout(0)// A+
#define MOTOR0_1 PDout(1)// A- 
#define MOTOR0_2 PDout(2)// B+
#define MOTOR0_3 PDout(3)// B+
extern int MOTOR0_dir;
extern int MOTOR0_Step;

extern int MOTOR1_Step;
#define MOTOR1_0 PBout(5)// A+
#define MOTOR1_1 PBout(6)// A- 
#define MOTOR1_2 PBout(7)// B+
#define MOTOR1_3 PBout(8)// B+
extern int MOTOR1_dir;

#endif
