package com.nodeaudio.reactdrum;

import android.content.Context;
import android.util.Log;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.modules.core.DeviceEventManagerModule;
import com.facebook.react.uimanager.events.RCTEventEmitter;
import com.juce.JuceViewHolder;
import com.juce.JuceBridge;

public class ReactJuceView extends JuceViewHolder {

    public ReactJuceView(Context c)
    {
        super(c);
    }

    // From example at https://facebook.github.io/react-native/docs/native-components-android.html
    public void juceAppHasInitialised() {
        Log.d("ReactJuceView", "juceAppHasInitialised");

        WritableMap event = Arguments.createMap();
        ReactContext reactContext = (ReactContext)getContext();
        reactContext.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class).emit(
                "juceAppHasInitialised",
                event);
    }
}
