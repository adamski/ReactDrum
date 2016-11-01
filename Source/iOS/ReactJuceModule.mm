/*
  ==============================================================================

    ReactJuceModule.mm
    Created: 30 Oct 2016 8:52:00pm
    Author:  Adam Wilson

  ==============================================================================
*/

#include "ReactJuceModule.h"
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Source/HelperMethods.h"
#include "../Source/MainComponent.h"
#import "RCTLog.h"

@implementation ReactJuceModule

RCT_EXPORT_MODULE();

RCT_REMAP_METHOD(getSampleNames, sampleNamesResolver: (RCTPromiseResolveBlock)resolve
                 sampleNamesRejecter:(RCTPromiseRejectBlock)reject)
{
    NSMutableArray *sampleNames = [NSMutableArray array];
    
    for (int i = 0; i < BinaryData::namedResourceListSize; ++i)
    {
        String processedName = HelperMethods::getSampleNameFromFilename (BinaryData::namedResourceList[i]);
        [sampleNames addObject:[[NSString alloc] initWithUTF8String: (processedName.toRawUTF8())]];
    }
    
    // Resolve with immutable array
    resolve([NSArray arrayWithArray:sampleNames]);
}

RCT_EXPORT_METHOD(selectSample:(NSString *)sampleName)
{
    SharedResourcePointer<MainContentComponent> mainComponent;
    String juceSampleName = CharPointer_UTF8 ([sampleName UTF8String]);
    mainComponent->loadSampleFromName((juceSampleName));
}

@end