
//#include "XPT2046.h"




//#define CMD_RDX 0X90  
//#define CMD_RDY 0XD0 

//#define READ_TIMES 15 //��ȡ����
//#define LOST_VAL   5	//��������

//void XPT2046_Init(void)
//{
//	  Disable_SWJ();
//		XPT_2046_MOSI_Init 
//		XPT_2046_MISO_Init  
//		XPT_2046_SCK_Init  
//		XPT_2046_PEN_Init  
//		XPT_2046_CS_Init   

//    Clr_PEN			//PEn	�������ź�Ӳ������ 
//}
///* д���� */   
//void XPT2046_Write_Byte(u8 num)    
//{  
//	u8 count=0;   
//	for(count=0;count<8;count++)  
//	{ 	  
//		if(num&0x80)Set_MOSI  
//		else Clr_MOSI   		    
//	  num<<=1;	Clr_SCK  Set_SCK    //��������Ч	   	 		      
//	} 			    
//} 		 
///* ��ȡ���� */ 
//u16 XPT2046_Read_Byte(u8 CMD)	  
//{ 	 
//	u8 count=0; 	  
//	u16 Num=0; 
//	Clr_SCK	  Clr_CS  
//	XPT2046_Write_Byte(CMD);
//	delay_us(3);
//	Set_SCK  Clr_SCK 	 
//	for(count=0;count<16;count++)  
//	{ 				  
//		Num<<=1;  Clr_SCK Set_SCK//�½�����Ч  	    	   
//		if(XPT2046_MISO)Num++; 		 
//	}  	
//	Num>>=4;   //ֻ�и�12λ��Ч.
//	Set_CS//�ͷ�ADS7843	 
//	return(Num);   
//}
///* ȥ�������� Ȼ��ȡƽ�� */
//u16 XPT2046_Read_XY(u8 xy)
//{
//	u16 i, j;
//	u16 buf[READ_TIMES];
//	u16 sum=0;
//	u16 temp;
//	for(i=0;i<READ_TIMES;i++)			 
//		buf[i]=XPT2046_Read_Byte(xy);	    			    
//	for(i=0;i<READ_TIMES-1; i++)//����
//		for(j=i+1;j<READ_TIMES;j++)
//			if(buf[i]>buf[j])//��������
//			{ temp=buf[i]; buf[i]=buf[j]; buf[j]=temp; }  
//	sum=0;
//	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
//	temp=sum/(READ_TIMES-2*LOST_VAL);
//	return temp;   
//}
///* ���˲��Ķ�ȡ���� */
//u8 Read_Once(u16 *x,u16 *y)
//{
//	u16 xtemp,ytemp;		 	 		  
//	xtemp=XPT2046_Read_XY(CMD_RDX);
//	ytemp=XPT2046_Read_XY(CMD_RDY);	  												   
//	if(xtemp<4096 && xtemp)*x=xtemp;		
//	if(ytemp<4096 && ytemp)*y=ytemp;						
//	return 1;//�����ɹ�
//}
///* ���ζ�ȡ���� ȡ��Χ�ڵ� �ɴ�����ߴ�����ȡ���� */
//#define ERR_RANGE 50 //��Χ 
//u8 XPT2046_Read_Dat(u16 *x,u16 *y) 
//{
//	 u16 x1,y1;
// 	 u16 x2,y2;
// 	 u8 flag;    
//    flag=Read_Once(&x1,&y1);   
//    if(flag==0)return(0);
//    flag=Read_Once(&x2,&y2);	   
//    if(flag==0)return(0);   
//    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-50��
//    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
//    {
//        *x=(x1+x2)/2; *y=(y1+y2)/2; return 1;
//    }else return 0;	  
//}
