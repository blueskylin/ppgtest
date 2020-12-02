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



typedef void (*InitDetectPR)();


typedef int (*DetectPR)(SPO2Parameter *parameter);


#endif // PPG_ANAlYSE_H



