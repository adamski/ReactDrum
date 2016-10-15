//
//  ReactJuceView.m
//  ReactDrum
//
//  Created by Adam Wilson on 15/10/2016.
//
//

#import "ReactJuceView.h"

//#import "RCTEventDispatcher.h"
//#import "RCTRootView.h"
#import "RCTViewManager.h"
#import "RCTLog.h"
#import "UIView+React.h"

#include "../MainComponent.cpp"  // This could be any other component you wish to use
#include "MainWindowIOS.h"

@implementation ReactJuceView

- (instancetype)initWithFrame:(CGRect)frame
{
    frame.size.height -= 49 * [[UIScreen mainScreen] scale]; // Hardcoded height of nav bar (!)
    
    self = [super initWithFrame:frame];
    
    if (self) {
        MainContentComponent* mainComponent = new MainContentComponent();
        MainWindow::addComponentToUIView (*mainComponent, self);
    }
    return self;
}

- (void)reactSetFrame:(CGRect)frame
{
    // Do something with frame here
    RCTLogInfo(@"frame set from React, height: %f", frame.size.height);
    DBG ("frame set from React, height" << self.frame.size.height);
    [super reactSetFrame: frame];
}


@end
