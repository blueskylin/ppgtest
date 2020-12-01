#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "detect_pr_slop.h"



/* Pulse detection parameters */

#define VALUE_SHAKE_THRESHOLD       5//7
#define STEP_OVERFLOW_COMPENSATION    256
#define PULSE_BPM_SAMPLE_SIZE       5 //Moving average size
#define DEFAULT_PR 75

static int preSensorValue = 0;
static int currentBeat = 0;
static int lastBeat = 0;
static unsigned char stepCount = 0;
static int valueShakeCnt = 0;
static unsigned char isFirstPulse = 0;
static int resultCnt = 0;
static char slopFlag = 0;
static int preSlop = 0;
static int currentSlop = 0;
static int ppgSample = 1;

static int prePr = 0;
static float valuesBPM[PULSE_BPM_SAMPLE_SIZE];
static unsigned char BPMCnt;

static int debug = 0;


void initDetectPulseBySlop(int sampleRate)
{
	  int i;
	
    preSensorValue = 0;
    currentBeat = 0;
    lastBeat = 0;
    stepCount = 0;
    valueShakeCnt = 0;
    isFirstPulse = 0;
    resultCnt = 0;
    slopFlag = 0;
    preSlop = 0;
    currentSlop = 0;
	  ppgSample = sampleRate;
	  prePr = DEFAULT_PR;
	
	  for(i = 0; i < PULSE_BPM_SAMPLE_SIZE; i++)
				valuesBPM[i] = 0;

}

int detectPulseBySlop(SPO2Parameter *parameter)
{

//	int i;
    int value;
    int ret = 0;

    if(parameter == NULL)
        return -1;

    value = parameter->sensorValue;
    stepCount++;
    currentSlop = value - preSensorValue;

    /***********  波形拐点 **************************/
    if(currentSlop < 0 && preSlop >= 0 && slopFlag == 0)
        {
            currentBeat = stepCount;
            slopFlag = 1;
            valueShakeCnt = 0;
        }
    /***********  去除由于干扰造成的伪拐点**********/
    if(slopFlag == 1 && currentSlop < 0)
        {
            valueShakeCnt++;
        }
    else if(slopFlag == 1 && currentSlop > 0)
        {
            valueShakeCnt = 0;
            slopFlag = 0;
        }

    /***********  取得拐点位置计算对应的PR值 *******/
    if(valueShakeCnt >= VALUE_SHAKE_THRESHOLD)
        {
            if(isFirstPulse == 0)
                {
                    lastBeat = currentBeat;
                    isFirstPulse = 1;
                    slopFlag = 0;
                    valueShakeCnt = 0;
                }
            else
                {

                    int beatDuration = currentBeat - lastBeat;
                    if(beatDuration < 0)
                        {
                            beatDuration += STEP_OVERFLOW_COMPENSATION;
                        }

                    if(debug == 1)
                        {
                            fprintf(stdout,"currentBeat is %d ,lastBeat is %d, beatDuration is %d\n",
                                    currentBeat, lastBeat, beatDuration);
                        }

                    lastBeat = currentBeat;
                    float rawBPM = 0;
                    if(beatDuration > 0)
                        rawBPM = BASE_PR * ppgSample / ((float)beatDuration);
                    if(debug == 1)
                        {
                            resultCnt++;
                            fprintf(stdout,"resultCnt is %d, rawBPM is %f\n", resultCnt, rawBPM);
                        }

                    isFirstPulse = 1;
                    slopFlag = 0;
                    valueShakeCnt = 0;
                    ret = rawBPM;
                }
        }

    preSlop = currentSlop;
    preSensorValue = value;

    return ret;
}

int calulatePr(const int *rawPr, int dataSize)
{
	  int i, j;
	  int sumBPM = 0;
	  int ret = -1;
	  if(rawPr == NULL || dataSize <= 0){
				return ret;
		}
		
		for(i = 0; i < dataSize; i++){
				if(rawPr[i] >= 30 && rawPr[i] <= 250){
						valuesBPM[BPMCnt++] = rawPr[i];
					  int cnt = 0;
					  for(j = 0; j < PULSE_BPM_SAMPLE_SIZE; j++){
								if(valuesBPM[j] != 0){
										sumBPM += valuesBPM[i];
									  cnt++;
								}
						}
					  if(BPMCnt >= PULSE_BPM_SAMPLE_SIZE)
								BPMCnt = 0;
						
						ret = (sumBPM / (float)cnt);
				}
	   }
		 
     if(ret <= 0){
				ret = prePr;
		 }			 
		 
		 prePr = ret;
		 
		 return ret;
}

