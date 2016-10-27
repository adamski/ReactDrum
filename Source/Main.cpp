/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#if JUCE_IOS
#include "iOS/MainWindowIOS.h"
#elif JUCE_ANDROID
#include "MainComponent.h"
namespace juce
{
#include "../JuceModules/juce_core/native/juce_android_JNIHelpers.h"
}
#else
#include "MainWindow.h"
#endif

//==============================================================================
class ReactDrumApplication  : public JUCEApplication
{
public:
    //==============================================================================
    ReactDrumApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

#if JUCE_ANDROID
        // Set up our windows that will be attached to Android views
        container = new ResizableWindow ("MainComponent", true);
        container->setContentOwned (new MainContentComponent(), true);
        container->setUsingNativeTitleBar (true);
        container->setFullScreen (true);
        container->setVisible (true);
#else
        // Instantiate MainWindow
        mainWindow = new MainWindow (getApplicationName());
#endif
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..
#if JUCE_ANDROID
        container = nullptr;
#else
        mainWindow = nullptr; // (deletes our window)
#endif
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

#if JUCE_ANDROID
    void attachOpenGLContext()
    {
        if (! openGLContext.isAttached())
            openGLContext.attachTo (*container);
    }
#endif

private:
#if JUCE_ANDROID
    ScopedPointer<ResizableWindow> container;
#else
    ScopedPointer<MainWindow> mainWindow;
#endif
    OpenGLContext openGLContext;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (ReactDrumApplication)

#if JUCE_ANDROID
JUCE_JNI_CALLBACK (JUCE_ANDROID_ACTIVITY_CLASSNAME, attachOpenGLContext, void, (JNIEnv* env, jclass))
{
    ReactDrumApplication* const app = dynamic_cast<ReactDrumApplication*> (JUCEApplication::getInstance());
    if (app != nullptr)
    {
        app->attachOpenGLContext();
    }
}
#endif