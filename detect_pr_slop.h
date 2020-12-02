#ifndef DETECT_PR_SLOP_H
#define DETECT_PR_SLOP_H

#include "ppg_analyse.h"

#ifdef __cplusplus
extern "C" {
#endif
void initDetectPulseBySlop(int sampleRate);
int detectPulseBySlop(SPO2Parameter *parameter);
int calulatePr(const int *rawPr, int dataSize);

#ifdef __cplusplus
}
#endif

#endif //DETECT_PR_SLOP_H




