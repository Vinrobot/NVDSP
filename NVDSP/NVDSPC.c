//
//  NVDSP_C.c
//  Everapp
//
//  Created by Artem on 9/9/18.
//  Copyright © 2018 Everappz. All rights reserved.
//

#include "NVDSPC.h"
#include <libkern/OSAtomic.h>
#include <Accelerate/Accelerate.h>
#include <stdio.h>
#include <string.h>



void c_interleave(float *data,float *left,float *right,vDSP_Length length) {
    float zero = 0.0f;
    vDSP_vsadd(left, 1, &zero, data, 2, length);
    vDSP_vsadd(right, 1, &zero, data+1, 2, length);
}

void c_deinterleave(float *data, float *left, float *right, vDSP_Length length) {
    float zero = 0.0f;
    vDSP_vsadd(data, 2, &zero, left, 1, length);
    vDSP_vsadd(data+1, 2, &zero, right, 1, length);
}

void c_filterData(float *data, unsigned int numFrames, unsigned int numChannels, float realTimeCoeffs[5], float *gInputKeepBuffer[2], float *gOutputKeepBuffer[2]){
    if(numChannels==1){
        c_filterContiguousData(data, numFrames, 0, realTimeCoeffs, gInputKeepBuffer, gOutputKeepBuffer);
    }
    else if(numChannels==2){
        float left[numFrames + 2];
        float right[numFrames + 2];
        c_deinterleave(data, left, right, numFrames);
        c_filterContiguousData(left, numFrames, 0, realTimeCoeffs, gInputKeepBuffer, gOutputKeepBuffer);
        c_filterContiguousData(right, numFrames, 1, realTimeCoeffs, gInputKeepBuffer, gOutputKeepBuffer);
        c_interleave(data,left,right,numFrames);
    }
}

void c_filterContiguousData(float *data, unsigned int numFrames, unsigned int channel,float realTimeCoeffs[5],float *gInputKeepBuffer[2],float *gOutputKeepBuffer[2]){
    
    // Provide buffer for processing
    float tInputBuffer[numFrames + 2];
    float tOutputBuffer[numFrames + 2];
    
    // Copy the data
    memcpy(tInputBuffer, gInputKeepBuffer[channel], 2 * sizeof(float));
    memcpy(tOutputBuffer, gOutputKeepBuffer[channel], 2 * sizeof(float));
    memcpy(&(tInputBuffer[2]), data, numFrames * sizeof(float));
    
    // Do the processing
    vDSP_deq22(tInputBuffer, 1, realTimeCoeffs, tOutputBuffer, 1, numFrames);
    
    // Copy the data
    memcpy(data, tOutputBuffer + 2, numFrames * sizeof(float));
    memcpy(gInputKeepBuffer[channel], &(tInputBuffer[numFrames]), 2 * sizeof(float));
    memcpy(gOutputKeepBuffer[channel], &(tOutputBuffer[numFrames]), 2 * sizeof(float));
}

void c_applyGain(float *ioData, float gain, unsigned int numFrames, unsigned int numChannels){
    vDSP_vsmul(ioData, 1, &gain, ioData, 1, numFrames*numChannels);
}
