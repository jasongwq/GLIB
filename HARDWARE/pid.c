#include "pid.h"
//struct PID spid; // PID Control Structure
s32 PID_out; // PID Response (Output)
s32 PID_in; // PID Feedback (Input)

//void PID_Init(struct PID *pp)
//{
//    memset(pp, 0, sizeof(struct PID));//将pp中前sizeof(struct PID)字节用0替换

//    p-pProportion = 0; // Set PID Coefficients//比例常数
//    spid.Integral = 0;//积分常数
//    spid.Derivative = 0;//微分常数
//    spid.SetPoint = 0; // Set PID Setpoint//设定目标
//}
/*========================= PID计算部分 =========================================*/
s32 PID_Calc(struct PID *pp, s16 NextPoint)
{
    unsigned int dError, Error;
    Error = pp -> SetPoint - NextPoint; // 偏差
    pp -> SumError += Error; // 积分
    dError = pp -> LastError - pp -> PrevError; // 当前微分//上一次-上上次偏差
    pp -> PrevError = pp -> LastError;
    pp -> LastError = Error;

    return (pp -> Proportion * Error // 比例项//比例常数*偏差
            +
            pp -> Integral * pp -> SumError // 积分项//积分常数*总偏差
            +
            pp -> Derivative * dError); // 微分项//微分常数*
}
/*********************************************************** 温度比较处理子程序 ***********************************************************/

