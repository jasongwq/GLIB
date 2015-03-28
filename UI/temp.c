#define DelaySPI()  delay_us(10)

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPIx_ReadWriteByte(u8 TxData)
{
    u8 i, RxData = 0, num = 0x80;
    for (i = 0; i < 0x08; i++)
    {
        SDClkOut(0);  //sck=0

        //Mosi:׼����Ҫд���ֵ---------------------
        if (TxData & num)SDMosiOut(1); //do=1
        else  SDMosiOut(0); //do=0
        if (num > 0x01)num = num >> 1;
        //------------------------
        //DelayXms(4);//4ms
        DelaySPI();
        SDClkOut(1);//sck=1   //������д�룬ͬʱmiso���������Ѿ��������

        //miso���������� --------------
        if (SDMisoIn())RxData |= 0x01;
        if (i < 7) RxData = RxData << 1; //
        //-----------------------

        //DelayXms(4);//4ms
        DelaySPI();
    }
    return RxData;
}