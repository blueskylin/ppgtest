#ifndef PPG_ANALYSE_H
#define PPG_ANALYSE_H

#define BASE_PR          60.0

typedef struct _SPO2Parameter
{

    int sensorValue;
    int xPosition;
    int yPosition;
    int zPosition;
} SPO2Parameter;


/******** ��ʼ�����ʼ���ģ��           ********/
typedef void (*InitDetectPR)();

/******** ʵʱ���ʼ���                 ********
 ******** parameter �ɼ���Ѫ������     ********
 ******** ����ֵ ���𲫷���0 �з�������********
 ******** ʧ�ܷ���-1                   ********/
typedef int (*DetectPR)(SPO2Parameter *parameter);


#endif // PPG_ANAlYSE_H



