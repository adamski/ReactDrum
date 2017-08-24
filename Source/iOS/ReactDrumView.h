/*
  ==============================================================================

    ReactDrumView.h
    Created: 1 Nov 2016 10:00:58pm
    Author:  Adam Wilson

  ==============================================================================
*/

#ifndef REACTDRUMVIEW_H_INCLUDED
#define REACTDRUMVIEW_H_INCLUDED

#import "ReactJuceView.h"
#include "../MainComponent.h"

@interface ReactDrumView : ReactJuceView

- (instancetype) initWithJuceComponent : (MainContentComponent*) component;
- (void) selectSample : (NSString*) sampleName;
- (void) setComponentBackgroundColour : (NSString*) colour;
- (void) setThumbnailForeground : (NSString*) colour;
- (void) setThumbnailBackground : (NSString*) colour;


@property (nonatomic, assign) MainContentComponent* juceComponent;
// TODO: Add colour, and possibly height/width properties

@end



#endif  // REACTDRUMVIEW_H_INCLUDED
