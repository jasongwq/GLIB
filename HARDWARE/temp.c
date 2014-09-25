void TIM1_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    static TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //使能定时器3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    TIM_DeInit(TIM1);
    //初始化TIM1
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;          //循环计数次数值
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //初始化TIM1  PWM模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //比较输出使能
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//使能定时器互补输出
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;       //输出极性
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;     //打开空闲状态选择关闭
    TIM_Cmd(TIM1, ENABLE);  //使能TIM1
    TIM_CtrlPWMOutputs(TIM1, ENABLE); //使能定时器1的PWM输出
}
#endif