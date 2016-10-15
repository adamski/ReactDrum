//
//  ReactJuceViewManager.m
//  ReactDrum
//
//  Created by Adam Wilson on 15/10/2016.
//
//

#import "ReactJuceViewManager.h"
#import "ReactJuceView.h"

@implementation ReactJuceViewManager

RCT_EXPORT_MODULE();

RCT_EXPORT_VIEW_PROPERTY(dummy, NSString)

- (UIView *)view
{
    //   return [[ReactJuceView alloc] init];
    return [[ReactJuceView alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    //    return [ReactJuceView new];
}

@end
