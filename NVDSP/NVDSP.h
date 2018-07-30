//
//  NVDSP.h
//  NVDSP
//
//  Created by Bart Olsthoorn on 13/05/2012.
//  Copyright (c) 2012 - 2014 Bart Olsthoorn
//  MIT licensed, see license.txt
//

#import <Foundation/Foundation.h>
#import <Accelerate/Accelerate.h>

//! Project version number for NVDSP.
FOUNDATION_EXPORT double NVDSPVersionNumber;

//! Project version string for NVDSP.
FOUNDATION_EXPORT const unsigned char NVDSPVersionString[];


#define MAX_CHANNEL_COUNT 2

@interface NVDSP : NSObject {
    float zero, one;

    float samplingRate;

    float *gInputKeepBuffer[2];
    float *gOutputKeepBuffer[2];

    float omega, omegaS, omegaC, alpha;
 
    float realTimeCoeffs[5];
 
    float a0, a1, a2, b0, b1, b2;
    
    int coeffsCopied;
    
@public
    float userCoeffs[5];
    
}

- (id) initWithSamplingRate:(float)sr;

#pragma mark - Setters
- (void) setCoefficients;


#pragma mark - Effects
- (void) filterContiguousData: (float *)data numFrames:(UInt32)numFrames channel:(UInt32)channel;
- (void) filterData:(float *)data numFrames:(UInt32)numFrames numChannels:(UInt32)numChannels;

- (void) applyGain:(float *)data length:(vDSP_Length)length gain:(float)gain;


#pragma mark - Etc
- (void) intermediateVariables: (float)Fc Q: (float)Q;
- (void) deinterleave: (float *)data left: (float*) left right: (float*) right length: (vDSP_Length)length;
- (void) interleave: (float *)data left: (float*) left right: (float*) right length: (vDSP_Length)length;
- (void) mono: (float *)data left: (float*) left right: (float*) right length: (vDSP_Length)length;

#pragma mark - Debug
- (void) logCoefficients;
- (void) stabilityWarning;

@end

void c_filterContiguousData(float *data, UInt32 numFrames, UInt32 channel,float realTimeCoeffs[5],float *gInputKeepBuffer[2],float *gOutputKeepBuffer[2]);


#import <NVDSP/NVClippingDetection.h>
#import <NVDSP/NVSoundLevelMeter.h>
#import <NVDSP/NVBandpassFilter.h>
#import <NVDSP/NVLowShelvingFilter.h>
#import <NVDSP/NVPeakingEQFilter.h>
#import <NVDSP/NVNotchFilter.h>
#import <NVDSP/NVHighpassFilter.h>
#import <NVDSP/NVBandpassQPeakGainFilter.h>
#import <NVDSP/NVHighShelvingFilter.h>
#import <NVDSP/NVLowpassFilter.h>
#import <NVDSP/NVAllpassFilter.h>
