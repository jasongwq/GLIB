void TIM1_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    static TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    TIM_DeInit(TIM1);
    //��ʼ��TIM1
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;          //ѭ����������ֵ
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM1  PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//ʹ�ܶ�ʱ���������
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;       //�������
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;     //�򿪿���״̬ѡ��ر�
    TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
    TIM_CtrlPWMOutputs(TIM1, ENABLE); //ʹ�ܶ�ʱ��1��PWM���
}
#endif