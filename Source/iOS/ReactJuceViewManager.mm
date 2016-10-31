//
//  ReactJuceViewManager.m
//  ReactDrum
//
//  Created by Adam Wilson on 15/10/2016.
//
//

#import "ReactJuceViewManager.h"
#import "ReactJuceView.h"

#include "../MainComponent.h"  // This could be any other component you wish to use

@implementation ReactJuceViewManager

RCT_EXPORT_MODULE();

RCT_EXPORT_VIEW_PROPERTY(dummy, NSString)

- (UIView *)view
{
//    MainContentComponent* mainComponent = new MainContentComponent();
    SharedResourcePointer<MainContentComponent> mainComponent;
    // do stuff with view properties e.g. mainComponent->setPlayButtonColour(<#juce::String colourString#>)
    
    return [[ReactJuceView alloc] initWithJuceComponent:mainComponent];
}

@end
