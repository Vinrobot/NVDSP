//
//  NVDSP_C.h
//  Everapp
//
//  Created by Artem on 9/9/18.
//  Copyright © 2018 Everappz. All rights reserved.
//

#include <stdio.h>

void c_filterData(float *data, unsigned int numFrames, unsigned int numChannels, float realTimeCoeffs[5], float *gInputKeepBuffer[2], float *gOutputKeepBuffer[2]);

void c_filterContiguousData(float *data, unsigned int numFrames, unsigned int channel,float realTimeCoeffs[5],float *gInputKeepBuffer[2],float *gOutputKeepBuffer[2]);

void c_applyGain(float *ioData, float gain, unsigned int numFrames, unsigned int numChannels);

