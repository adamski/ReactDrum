package com.nodeaudio.reactdrum;

import android.util.Log;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReactSyncHook;
import com.facebook.react.bridge.WritableNativeArray;

import java.util.ArrayList;

/**
 * Created by adamwilson on 01/11/2016.
 */

public class ReactJuceModule extends ReactContextBaseJavaModule {

    public ReactJuceModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @Override
    public String getName() {
        return "ReactJuceModule";
    }

    @ReactMethod
    public void getSampleNames(Promise promise)
    {
        Log.d ("ReactJuceModule", "calling getSampleNames");
        String[] sampleNames = MainActivity.getSampleNames();

        WritableNativeArray sampleNameArray = new WritableNativeArray();
        for (int i = 0; i < sampleNames.length; i++)
            sampleNameArray.pushString(sampleNames[i]);

        promise.resolve(sampleNameArray);
    }

    @ReactMethod
    public void selectSample(String sampleName)
    {
        Log.d ("ReactJuceModule", "calling selectSample...");
        MainActivity.selectSample(sampleName);
    }
}
