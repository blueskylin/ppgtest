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


/******** 初始化脉率计算模块           ********/
typedef void (*InitDetectPR)();

/******** 实时脉率计算                 ********
 ******** parameter 采集的血氧参数     ********
 ******** 返回值 无起搏返回0 有返回脉率********
 ******** 失败返回-1                   ********/
typedef int (*DetectPR)(SPO2Parameter *parameter);


#endif // PPG_ANAlYSE_H



