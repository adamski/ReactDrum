#import "RCTView.h"
#import <UIKit/UIKit.h>

#include "JuceHeader.h"

@interface ReactJuceView : RCTView

- (instancetype)initWithJuceComponent:(Component*)component;

@property (nonatomic, assign) Component* juceComponent;
// TODO: Add colour, and possibly height/width properties

@end
