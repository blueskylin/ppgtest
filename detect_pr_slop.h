#ifndef DETECT_PR_SLOP_H
#define DETECT_PR_SLOP_H

#include "ppg_analyse.h"

void initDetectPulseBySlop(int sampleRate);
int detectPulseBySlop(SPO2Parameter *parameter);
int calulatePr(const int *rawPr, int dataSize);



#endif //DETECT_PR_SLOP_H




