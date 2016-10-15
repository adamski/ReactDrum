//
//  ReactJuceViewManager.m
//  ReactDrum
//
//  Created by Adam Wilson on 15/10/2016.
//
//

#import "ReactJuceViewManager.h"
#import "ReactJuceView.h"

#include "../MainComponent.cpp"  // This could be any other component you wish to use
//#include "MainWindowIOS.h"

@implementation ReactJuceViewManager

RCT_EXPORT_MODULE();

RCT_EXPORT_VIEW_PROPERTY(dummy, NSString)

- (UIView *)view
{
//    UIView* view;
//    view = [[UIView alloc] init];
//    MainContentComponent* mainComponent = new MainContentComponent();
//    MainWindow::addComponentToUIView (*mainComponent, view);
//    mainComponent->setBounds(0, 0, view.frame.size.width, view.frame.size.height);
//    return view;
    MainContentComponent* mainComponent = new MainContentComponent();
    
    return [[ReactJuceView alloc] initWithJuceComponent:mainComponent];
    
//    return [[ReactJuceView alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    //    return [ReactJuceView new];
}

@end
