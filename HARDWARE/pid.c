#include "pid.h"
//struct PID spid; // PID Control Structure
s32 PID_out; // PID Response (Output)
s32 PID_in; // PID Feedback (Input)

//void PID_Init(struct PID *pp)
//{
//    memset(pp, 0, sizeof(struct PID));//��pp��ǰsizeof(struct PID)�ֽ���0�滻

//    p-pProportion = 0; // Set PID Coefficients//��������
//    spid.Integral = 0;//���ֳ���
//    spid.Derivative = 0;//΢�ֳ���
//    spid.SetPoint = 0; // Set PID Setpoint//�趨Ŀ��
//}
/*========================= PID���㲿�� =========================================*/
s32 PID_Calc(struct PID *pp, s16 NextPoint)
{
    unsigned int dError, Error;
    Error = pp -> SetPoint - NextPoint; // ƫ��
    pp -> SumError += Error; // ����
    dError = pp -> LastError - pp -> PrevError; // ��ǰ΢��//��һ��-���ϴ�ƫ��
    pp -> PrevError = pp -> LastError;
    pp -> LastError = Error;

    return (pp -> Proportion * Error // ������//��������*ƫ��
            +
            pp -> Integral * pp -> SumError // ������//���ֳ���*��ƫ��
            +
            pp -> Derivative * dError); // ΢����//΢�ֳ���*
}
/*********************************************************** �¶ȱȽϴ����ӳ��� ***********************************************************/

