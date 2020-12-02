#ifndef PPG_FILTER_H
#define PPG_FILTER_H

#include "ppg_analyse.h"

void initPpgFilter(void);
int  ppgFilter(SPO2Parameter *parameter);
int  judgePpgDataQuality(int value);



#endif //PPG_FILTER_H
