#ifndef __FPMXX_H
#define __FPMXX_H
extern volatile unsigned char FPMXX_RECEICE_BUFFER[];
void FPMXX_Cmd_Send_Pack_Head(void);
void FPMXX_Cmd_Get_Img(void);
//void FINGERPRINT_Cmd_Search_Finger_Admin(void);
//void FINGERPRINT_Cmd_Search_Finger(void);
void FINGERPRINT_Cmd_Search_Finger(int BufferID,int StartPage,int PageNum);
void FINGERPRINT_Cmd_Save_Finger( unsigned char ucH_Char, unsigned char ucL_Char );
void FINGERPRINT_Cmd_Reg_Model(void);
void FINGERPRINT_Cmd_Img_To_Buffer2(void);
void FINGERPRINT_Cmd_Img_To_Buffer(int BufferID);
void FINGERPRINT_Cmd_Get_Templete_Num(void);
void FINGERPRINT_Cmd_Delete_Model(unsigned int uiID_temp);
void FINGERPRINT_Cmd_Delete_All_Model(void);
void FPMXX_Receive_Data(unsigned char ucLength);

#endif
