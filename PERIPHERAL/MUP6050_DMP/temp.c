/***************************
��ƽ��ϵͳ for Arduino
by ����
 ���ݲɼ�    2012-03-21
 �˲�        2012-03-23
 PID����     2012-03-27
 PID����
 �˶�����
***************************/

#include <Wire.h>
#include <Servo.h> 

/************ ���������� ***********/
#define Acc 0x1D           // ADXL345��ַ
#define Gyr 0x69           // L3G4200D��ַ
#define Mag 0x1E           // HMC5883L��ַ
#define Gry_offset -13     // ������ƫ����
#define Gyr_Gain 0.07      // ������2000dpsʱ������(dps/digital)
#define pi 3.14159

/********** �����˲������� *********/
unsigned long preTime = 0; // ����ʱ��
float f_angle = 0.0;       // �˲������ĽǶ�ֵ

/*********** PID���������� *********/
unsigned long lastTime;           // ǰ��ʱ��
float ITerm, lastInput;    // �����ǰ������
float Output = 0.0;        // PID���ֵ

/*********** �����Ʋ��� **********/
Servo servoL;              // ��������
Servo servoR;              // ��������
# define servoL_offset 90  // ����ƫ��
# define servoR_offset 90  // ����ƫ��

/************ �����ʼ�� ***********/
void setup() {
    sensor_init();        // ���ô�����
    Serial.begin(19200);  // ���������Ա��������
    servoL.attach(30);    // PIN30���������
    servoR.attach(32);    // PIN32���������
    delay(1000);
  }
/************** ������ *************/
void loop() {
    unsigned long now = millis();                           // ��ǰʱ��(ms)
    float dt = (now - preTime) / 1000.0;                    // ΢��ʱ��(s)
    preTime = now;                                          // ��¼����ʱ��(ms)

/********** ��ȡ��̬������ *********/
    float Y_Acc = gDat(Acc, 1);                             // ��ȡ��ǰ�ļ��ٶ�(digite)
    float Z_Acc = gDat(Acc, 2);                             // ��ȡ���µļ��ٶ�(digite)
    float angleA = atan(Y_Acc / Z_Acc) * 180 / pi;          // ���ݼ��ٶȷ����õ��ĽǶ�(degree)
    float omega =  Gyr_Gain * (gDat(Gyr, 0) +  Gry_offset); // ��ǰ���ٶ�(degree/s)

/*********** һ�׻����˲� **********/
    float K = 0.8;                                          // ȡֵȨ��
    float A = K / (K + dt);                                 // ��Ȩϵ��
    f_angle = A * (f_angle + omega * dt) + (1-A) * angleA;  // �����˲��㷨
/************ PID������ ***********/
    now = millis();                                         // ��ǰʱ��(ms)
    float TimeCh = (now - lastTime) / 1000.0;               // ����ʱ��(s)
    float Kp = 10.0, Ki = 0.0, Kd = 0.0;                    // ����ϵ��������ϵ����΢��ϵ��
    float SampleTime = 0.1;                                 // ����ʱ��(s)
    float Setpoint = -3.8;                                  // �趨Ŀ��ֵ(degree)
    float outMin = -80.0, outMax = +80.0;                   // ������ޡ��������
    if(TimeCh >= SampleTime) {                              // ����Ԥ������ʱ��ʱ
        float Input = f_angle;                              // ���븳ֵ
        float error = Setpoint - Input;                     // ƫ��ֵ
        ITerm+= (Ki * error * TimeCh);                      // ���������
        ITerm = constrain(ITerm, outMin, outMax);           // �޶�ֵ��
        float DTerm = Kd * (Input - lastInput) / TimeCh;    // ����΢����
        Output = Kp * error + ITerm - DTerm;                // �������ֵ
        Output = constrain(Output, outMin, outMax);         // �޶�ֵ��
        servoL.write(Output + servoL_offset);               // ��������
        servoR.write(Output + servoR_offset);               // ��������
        lastInput = Input;                                  // ��¼����ֵ
        lastTime = now;                                     // ��¼����ʱ��
    }
/************ �����ϴ� ***********/
    Serial.print(now);          // ����ʱ��
    Serial.print(",");
    Serial.print(f_angle, 6);   // ƫ��Ƕ�
    Serial.print(",");
    Serial.print(Output, 6);    // PID���ֵ
    Serial.print(";");
// ����΢��ʱ��
    delay(10);
}

/***************************************
������̬�������Ĵ�����ȡ����
For Arduino, by ����
****************************************
        ���ò�����
****************************************
  type    device      axis
                   0   1   2
ADXL345     Acc    x   y   z
L3G4200D    Gyr    x   y   z
HMC5883L    Mag    x   z   y
****************************************
Example
****************************************
00 #include <Wire.h>
01 #define Acc 0x1D;
02 #define Gyr 0x69;
03 #define Mag 0x1E;
04
05  void setup() {
06    sensor_init();
07    delay(1000);
08  }
09
10  void loop() {
11    int Z-Gyroscope;
12    Z-Gyroscope = gDat(Gyr, 2);
13    delay(50);
14  }
***************************************/

int gDat(int device, int axis) {
    int v;
    byte vL, vH, address;               // ���byte��ֵ
    if (device == Acc) address = 0x32;  // ADXL345�Ķ�����ַ
    if (device == Gyr) address = 0xA8;  // L3G4200D�Ķ�����ַ
    if (device == Mag) address = 0x03;  // HMC5883L�Ķ�����ַ
    address = address + axis * 2;       // ����ƫ��-������
    Wire.beginTransmission(device);     // ��ʼ��������
    Wire.send(address);                 // ����ָ��
    Wire.requestFrom(device, 2);        // ����2 byte����
    while(Wire.available() < 2);        // �ɹ���ȡǰ�ȴ�
    vL = Wire.receive();
    vH = Wire.receive();                // ��ȡ����
    Wire.endTransmission();             // ��������
    if (device == Mag) v = (vL << 8) | vH;
    else v = (vH << 8) | vL;            // ��byte���ݺϲ�ΪInt
    return v;                           // ���ض���ֵ
}

/********************************************
���þ�����̬������
********************************************/
void sensor_init() {

/************ ���� ADXL345 ***********/
    writeRegister(Acc, 0x2D, 0b00001000);    // ����ģʽ

/************ ����L3G4200D ***********/
    writeRegister(Gyr, 0x20, 0b00001111);    // ����˯��ģʽ��x, y, z��ʹ��
    writeRegister(Gyr, 0x21, 0b00000000);    // ѡ���ͨ�˲�ģʽ�͸�ͨ��ֹƵ�� 
    writeRegister(Gyr, 0x22, 0b00000000);    // �����ж�ģʽ
    writeRegister(Gyr, 0x23, 0b00110000);    // ��������(2000dps)���Լ�״̬��SPIģʽ
    writeRegister(Gyr, 0x24, 0b00000000);    // FIFO & ��ͨ�˲�

/************ ����HMC5883L ***********/
    writeRegister(Mag, 0x02, 0x00);          // ��������
}

/********************************************
�Ĵ���д�뺯��
********************************************/
void writeRegister(int device, byte address, byte val) {
    Wire.beginTransmission(device);          // д��Ĵ�����
    Wire.send(address);                      // д���ַ
    Wire.send(val);                          // д��ֵ
    Wire.endTransmission();                  // ��������
}