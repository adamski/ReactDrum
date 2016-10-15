/*
  ==============================================================================

    MainWindowIOS.h
    Created: 14 Oct 2016 8:25:38pm
    Author:  Adam Wilson

  ==============================================================================
*/

#ifndef MAINWINDOWIOS_H_INCLUDED
#define MAINWINDOWIOS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 This class implements the iOS window to which we can attach a JUCE Component 
 */

class MainWindow    : public DocumentWindow
{
public:
    MainWindow (String name);
    void closeButtonPressed() override;
    static void addComponentToUIView (Component& comp, void* uiView);
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};


#endif  // MAINWINDOWIOS_H_INCLUDED
