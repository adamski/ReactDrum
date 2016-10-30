#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//#include "SamplePlayerProcessor.h"

#if JUCE_ANDROID
namespace juce
{
#include "../JuceModules/juce_core/native/juce_android_JNIHelpers.h"
}
#endif

class MainContentComponent   : public Component,
                               public AudioSource,
                               public ChangeListener,
                               private ButtonListener,
                               private Timer
{
public:
    MainContentComponent ()
            : state (Stopped),
              timeSliceThread ("Player Thread"),
              thumbnailCache (5),
              thumbnail (512, formatManager, thumbnailCache),
              thumbnailBackground (Colours::white),
              thumbnailForeground (Colours::grey),
              audioPositionColour (Colours::green),
              backgroundColour (Colours::lightcoral)
    {
//        keyboardState.addListener (&processorPlayer.getMidiMessageCollector());

        setLookAndFeel (&lookAndFeel);
        
        addAndMakeVisible (&playButton);
        playButton.setButtonText ("Play");
        playButton.addListener (this);
        playButton.setColour (TextButton::buttonColourId, Colours::green);
        playButton.setEnabled (false);
        playButton.setTriggeredOnMouseDown (true);
        
        setSize (600, 400);
        
        formatManager.registerBasicFormats();
        transportSource.addChangeListener (this);
        thumbnail.addChangeListener (this);

        // TODO: Below to make into React logo ?
//        Path proAudioPath;
//        proAudioPath.loadPathFromData (BinaryData::proaudio_path, BinaryData::proaudio_pathSize);
//        proAudioIcon.setPath (proAudioPath);
//        addAndMakeVisible (proAudioIcon);
//
//        Colour proAudioIconColour = findColour (TextButton::buttonColourId);
//        proAudioIcon.setFill (FillType (proAudioIconColour));

        loadSampleFromName ("Chhhhaah");

        timeSliceThread.startThread(9);
        startTimerHz (25);
    }
    
    ~MainContentComponent()
    {
//        shutdownAudio();
    }
    
    void loadSampleFromName (String name)
    {
        DBG ("loadSampleFromName: " << name);
        int dataSizeInBytes;
        name = name.replace(" ", "_");
        const char* filename = BinaryData::getNamedResource (String (name + "_" + String (audioFormatExtension)).toRawUTF8(), dataSizeInBytes);
        
        loadNewSample (filename, dataSizeInBytes, audioFormatExtension);
    }

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        if (readerSource == nullptr)
        {
            bufferToFill.clearActiveBufferRegion();
            return;
        }

        transportSource.getNextAudioBlock (bufferToFill);
    }

    void releaseResources() override
    {
        transportSource.releaseResources();
    }

    void paint (Graphics& g) override
    {
        g.fillAll (backgroundColour);
        const Rectangle<int> thumbnailBounds (10, 100, getWidth() - 20, getHeight() - 120);
        
        if (thumbnail.getNumChannels() == 0)
            paintIfNoFileLoaded (g, thumbnailBounds);
        else
            paintIfFileLoaded (g, thumbnailBounds);
    }
    
    void resized() override
    {
        playButton.setBounds (10, 10, getWidth() - 20, 80);
    }
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &thumbnail)       thumbnailChanged();
    }
    
    void buttonClicked (Button* button) override
    {
        if (button == &playButton)  playButtonClicked();
    }
    
    void setPlayButtonColour(String colourString)
    {
        playButton.setColour (TextButton::buttonColourId, Colour::fromString (colourString));
    }
    
    void setPlayButtonTextColour(String colourString)
    {
        playButton.setColour (TextButton::textColourOnId, Colour::fromString (colourString));
        playButton.setColour (TextButton::textColourOffId, Colour::fromString (colourString));
    }
    
    void setThumbnailBackground(String colourString)
    {
        thumbnailBackground = Colour::fromString (colourString);
    }
    
    void setThumbnailForeground(String colourString)
    {
        thumbnailForeground = Colour::fromString (colourString);
    }
    
    void setAudioPositionColour(String colourString)
    {
        audioPositionColour = Colour::fromString (colourString);
    }
    
private:
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Stopping
    };
    
    void timerCallback() override
    {
        repaint();
    }
    
    
    void thumbnailChanged()
    {
        repaint();
    }
    
    void paintIfNoFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds)
    {
        g.setColour (Colours::darkgrey);
        g.fillRect (thumbnailBounds);
        g.setColour (Colours::white);
        g.drawFittedText ("No File Loaded", thumbnailBounds, Justification::centred, 1.0f);
    }
    
    void paintIfFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds)
    {
        // TODO: Optimise paint by drawing thumbnail to Image first
        g.setColour (thumbnailBackground);
        g.fillRoundedRectangle (thumbnailBounds.toFloat(), 5.0f);

        g.setColour (thumbnailForeground);                                     // [8]

        const double audioLength (thumbnail.getTotalLength());
        thumbnail.drawChannels (g,                                      // [9]
                                thumbnailBounds,
                                0.0,                                    // start time
                                thumbnail.getTotalLength(),             // end time
                                1.0f);                                  // vertical zoom
        
        g.setColour (audioPositionColour);
        
        const double audioPosition (transportSource.getCurrentPosition());
        const float drawPosition ((audioPosition / audioLength) * thumbnailBounds.getWidth()
                                  + thumbnailBounds.getX());                                        // [13]
        g.drawLine (drawPosition, thumbnailBounds.getY(), drawPosition,
                    thumbnailBounds.getBottom(), 2.0f);
    }
    
    StringArray getSampleNames()
    {
        StringArray list;
        String formatExtensionUnderscore = "_" + String(audioFormatExtension);
        
        for (int i = 0; i < BinaryData::namedResourceListSize; ++i)
        {
            String filename = BinaryData::namedResourceList[i];
            if (filename.endsWith (formatExtensionUnderscore))
                list.add (filename.upToLastOccurrenceOf (formatExtensionUnderscore, false, true));
        }
        return list;
    }
    

    
    void loadNewSample (const void* data, int dataSize, const char* format)
    {

        MemoryInputStream* soundBuffer = new MemoryInputStream (data, static_cast<std::size_t> (dataSize), false);
        
        ScopedPointer<AudioFormatReader> reader = formatManager.findFormatForFileExtension (format)->createReaderFor (soundBuffer, true);
        
        if (reader == nullptr)
        {
            DBG ("loadNewSample: reader == nullptr");
            return;
        }
        
        if ((readerSource = new AudioFormatReaderSource (reader, false)))
        {
#if JUCE_ANDROID
            transportSource.setSource (readerSource, 8192, &timeSliceThread, reader->sampleRate);
#else
            transportSource.setSource (readerSource, 0, nullptr, reader->sampleRate);
#endif
            playButton.setEnabled (true);
            {
                MessageManagerLock mm;
                thumbnail.setReader (reader.release(), generateHashForSample (data, 128));
            }

        }
    }
    
    int generateHashForSample(const void* data, const int upperLimit)
    {
        return (int)(((pointer_sized_uint) data) % ((pointer_sized_uint) upperLimit));
    }
    
    void playButtonClicked()
    {
        transportSource.stop();
        transportSource.setPosition (0.0);
        transportSource.start();
    }
    
    
    //==========================================================================
    TextButton playButton;

    AudioFormatManager formatManager;                    // [3]
    ScopedPointer<AudioFormatReaderSource> readerSource;
    ScopedPointer<AudioFormatReader> formatReader;
    AudioTransportSource transportSource;
    HashMap<String, String> sampleHashMap;
    TransportState state;
    AudioThumbnailCache thumbnailCache;                  // [1]
    AudioThumbnail thumbnail;                            // [2]
    TimeSliceThread timeSliceThread;

//    AudioProcessorPlayer& player;
//    MidiKeyboardState keyboardState;

    LookAndFeel_V3 lookAndFeel;
    Colour thumbnailBackground, thumbnailForeground, audioPositionColour;
    Colour backgroundColour;
    
    const char* audioFormatExtension = "ogg";
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED

