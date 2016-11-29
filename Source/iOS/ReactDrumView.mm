/*
  ==============================================================================

    ReactDrumView.cpp
    Created: 1 Nov 2016 10:01:17pm
    Author:  Adam Wilson

  ==============================================================================
*/

#import "ReactDrumView.h"

//#import "RCTEventDispatcher.h"
//#import "RCTRootView.h"
#import "RCTViewManager.h"
#import "RCTLog.h"
#import "UIView+React.h"

@implementation ReactDrumView

- (instancetype)initWithJuceComponent:(MainContentComponent*)component
{
    self = [super initWithJuceComponent:(component)];
    return self;
}

- (void)selectSample:(NSString*)sampleName
{
    String juceSampleName = CharPointer_UTF8 ([sampleName UTF8String]);
    self.juceComponent->loadSampleFromName(juceSampleName);
}

- (void)setComponentBackgroundColour:(NSString*)colour
{
    String juceColour = CharPointer_UTF8 ([colour UTF8String]);
    self.juceComponent->setBackgroundColour(juceColour);
}

- (void)setThumbnailForeground:(NSString*)colour
{
    String juceColour = CharPointer_UTF8 ([colour UTF8String]);
    self.juceComponent->setThumbnailForeground(juceColour);
}

- (void)setThumbnailBackground:(NSString*)colour
{
    String juceColour = CharPointer_UTF8 ([colour UTF8String]);
    self.juceComponent->setThumbnailBackground(juceColour);
}

@end