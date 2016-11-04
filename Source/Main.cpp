/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "HelperMethods.h"

#if JUCE_IOS
#include "iOS/MainWindowIOS.h"
#elif JUCE_ANDROID
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
        ignoreUnused (commandLine);

#if JUCE_ANDROID 
        // For the Android emulator to be as smooth as possible we set it to its max bufferSize
        AudioDeviceManager::AudioDeviceSetup deviceSetup = AudioDeviceManager::AudioDeviceSetup();
        deviceSetup.bufferSize = 7168;
        deviceSetup.sampleRate = 44100;
        String err = deviceManager->initialise(0, 2, nullptr, true, String::empty, &deviceSetup);
#else
        String err = deviceManager->initialiseWithDefaultDevices (0, 2);
#endif
        DBG (err);
        jassert (err.isEmpty());
        int bufferSize = deviceManager->getCurrentAudioDevice()->getCurrentBufferSizeSamples();
        double sampleRate = deviceManager->getCurrentAudioDevice()->getCurrentSampleRate();

        DBG ("bufferSizes:");
        auto availableBufferSizes = deviceManager->getCurrentAudioDevice()->getAvailableBufferSizes();
        for (auto bs : availableBufferSizes)
            DBG (bs);

        DBG ("sampleRates:");
        auto availableSampleRates = deviceManager->getCurrentAudioDevice()->getAvailableSampleRates();
        for (auto sr : availableSampleRates)
                DBG (sr);

        DBG ("bufferSize: " << bufferSize << "; sampleRate: " << sampleRate);



#if JUCE_ANDROID

        mainComponent = new MainContentComponent();

        // Set up our windows that will be attached to Android views
        container = new ResizableWindow ("MainComponent", true);
        container->setContentOwned (mainComponent, true);
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
        DBG ("Attaching to OpenGLContext...");
        if (openGLContext.isAttached())
        {
            openGLContext.detach();
            DBG ("OpenGLContext was already attached");
        }
        openGLContext.attachTo (*container);
    }
#endif
    
    MainContentComponent* getMainComponent()
    {
        return mainComponent.get();
    }

private:
    SharedResourcePointer<AudioDeviceManager> deviceManager;
    ScopedPointer<MainContentComponent> mainComponent;

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

JUCE_JNI_CALLBACK (JUCE_ANDROID_ACTIVITY_CLASSNAME, getSampleNames, jobjectArray, (JNIEnv* env, jclass))
{
    jobjectArray ret;

    ret = (jobjectArray) env->NewObjectArray(BinaryData::namedResourceListSize,
                                           env->FindClass("java/lang/String"),
                                           env->NewStringUTF(""));

    for (int i = 0; i < BinaryData::namedResourceListSize; ++i)
    {
        String processedName = HelperMethods::getSampleNameFromFilename (BinaryData::namedResourceList[i]);
        env->SetObjectArrayElement(
                ret,i,env->NewStringUTF(processedName.toRawUTF8()));
    }

    return ret;
}

JUCE_JNI_CALLBACK (JUCE_ANDROID_ACTIVITY_CLASSNAME, selectSample, void, (JNIEnv* env, jclass, jstring sampleNameJavaString))
{
    ReactDrumApplication* const app = dynamic_cast<ReactDrumApplication*> (JUCEApplication::getInstance());
    if (app != nullptr)
    {
        jassert (app->getMainComponent() != nullptr);
        
        if (sampleNameJavaString != nullptr) {
            const char *sampleName = (env)->GetStringUTFChars (sampleNameJavaString, NULL);
            app->getMainComponent()->loadSampleFromName(sampleName);
        }
        else
        {
            Logger::writeToLog("Null string sent to selectSample");
            // TODO: Notify user; JS callback or JUCE MessageDialog
        }
    }
}

JUCE_JNI_CALLBACK (JUCE_ANDROID_ACTIVITY_CLASSNAME, setBackgroundColour, void, (JNIEnv* env, jclass, jstring colourJavaString))
{
    ReactDrumApplication* const app = dynamic_cast<ReactDrumApplication*> (JUCEApplication::getInstance());
    if (app != nullptr)
    {
        jassert (app->getMainComponent() != nullptr);

        if (colourJavaString != nullptr) {
            const char *colour = (env)->GetStringUTFChars (colourJavaString, NULL);
            app->getMainComponent()->setBackgroundColour (colour);
        }
        else
        {
            Logger::writeToLog("Null string sent to setBackgroundColour");
            // TODO: Notify user; JS callback or JUCE MessageDialog
        }
    }
}

JUCE_JNI_CALLBACK (JUCE_ANDROID_ACTIVITY_CLASSNAME, setThumbnailForeground, void, (JNIEnv* env, jclass, jstring colourJavaString))
{
    ReactDrumApplication* const app = dynamic_cast<ReactDrumApplication*> (JUCEApplication::getInstance());
    if (app != nullptr)
    {
        jassert (app->getMainComponent() != nullptr);

        if (colourJavaString != nullptr) {
            const char *colour = (env)->GetStringUTFChars (colourJavaString, NULL);
            app->getMainComponent()->setThumbnailForeground (colour);
        }
        else
        {
            Logger::writeToLog("Null string sent to setThumbnailForeground");
            // TODO: Notify user; JS callback or JUCE MessageDialog
        }
    }
}


JUCE_JNI_CALLBACK (JUCE_ANDROID_ACTIVITY_CLASSNAME, setThumbnailBackground, void, (JNIEnv* env, jclass, jstring colourJavaString))
{
    ReactDrumApplication* const app = dynamic_cast<ReactDrumApplication*> (JUCEApplication::getInstance());
    if (app != nullptr)
    {
        jassert (app->getMainComponent() != nullptr);

        if (colourJavaString != nullptr) {
            const char *colour = (env)->GetStringUTFChars (colourJavaString, NULL);
            app->getMainComponent()->setThumbnailBackground (colour);
        }
        else
        {
            Logger::writeToLog("Null string sent to setThumbnailBackground");
            // TODO: Notify user; JS callback or JUCE MessageDialog
        }
    }
}

#endif