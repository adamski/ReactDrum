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

@implementation ReactJuceView

- (instancetype)initWithJuceComponent:(Component*)component
{
    self = [super init];
    
    if (self) {
        self.juceComponent = component;
        
        component->addToDesktop (0, self);
        component->setVisible (true);
    }
    return self;
}

- (void)reactSetFrame:(CGRect)frame
{
    [super reactSetFrame: frame];
    
    self.juceComponent->setBounds (frame.origin.x, frame.origin.y,
                                   frame.size.width, frame.size.height);
}



@end
