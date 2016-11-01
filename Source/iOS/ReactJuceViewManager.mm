//
//  ReactJuceViewManager.m
//  ReactDrum
//
//  Created by Adam Wilson on 15/10/2016.
//
//

#import "ReactJuceViewManager.h"
#import "ReactDrumView.h"

#include "../MainComponent.h"  // This could be any other component you wish to use

@implementation ReactJuceViewManager

RCT_EXPORT_MODULE();

//RCT_EXPORT_VIEW_PROPERTY(sampleName, NSString)

RCT_CUSTOM_VIEW_PROPERTY(sampleName, NSString, ReactDrumView)
{
    [view selectSample:([RCTConvert NSString:json])];
}

- (UIView *)view
{
    MainContentComponent* mainComponent = new MainContentComponent();
//    SharedResourcePointer<MainContentComponent> mainComponent;
    // do stuff with view properties e.g. mainComponent->setPlayButtonColour(<#juce::String colourString#>)
    
    return [[ReactDrumView alloc] initWithJuceComponent:mainComponent];
}

@end
