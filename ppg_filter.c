#include "ppg_filter.h"

#define FIR_FILTER_LENGTH 33

#define RING_ADD(a,b,m) ((a)+(b))%(m)
#define RING_SUB(a,b,m) ((a) - (b) >= 0 )? ((a) - (b)) :((a) - (b) + (m))

typedef long long INT64;



int FIR_COFFES[FIR_FILTER_LENGTH]=
{  
  -23, -16, -5, 9, 16, -4, -70, -184, -317,   
  -406, -374, -161, 241, 770,  1306, 1706, 1854, 1706,    
   1306, 770, 241, -161, -374, -406, -317, -184, 
  -70, -4, 16, 9, -5, -16, -23
};

static int mLpFilterIdx = 0;
static int mLpFilterBuff[40];

int filter(int data)
{
	INT64 sum = 0;
	INT64 temp = 0;
	int headIdx = 0;
	int caudaIdx = 0;
	int i = 0;
	int result = 0;

    	
	headIdx = mLpFilterIdx;
	caudaIdx = RING_ADD(headIdx, 1, FIR_FILTER_LENGTH);
	mLpFilterBuff[headIdx] = data;
	
	for(i = 0; i < FIR_FILTER_LENGTH/2; i++)
	{

		temp = (mLpFilterBuff[headIdx] + mLpFilterBuff[caudaIdx]);
		temp *= FIR_COFFES[i];
		sum += temp;
		headIdx = RING_SUB(headIdx, 1, FIR_FILTER_LENGTH);
		caudaIdx = RING_ADD(caudaIdx, 1, FIR_FILTER_LENGTH);
	}
	if(FIR_FILTER_LENGTH%2 != 0)
	{

		temp = mLpFilterBuff[caudaIdx];
		temp *= FIR_COFFES[i];
		sum += temp;
	}

	mLpFilterIdx = RING_ADD(mLpFilterIdx, 1, FIR_FILTER_LENGTH);
	result =   sum / 64;
	return result;
}

void initPpgFilter(void)
{
		int i;

	  mLpFilterIdx = 0;
		for(i = 0; i < 40; i++)
	  {
				mLpFilterBuff[i] = 0;
		}
}

int  ppgFilter(SPO2Parameter *parameter)
{
	parameter->sensorValue = filter(parameter->sensorValue);
	
	return 0;
}

int  judgePpgDataQuality(int value)
{
	 return 0;
}


