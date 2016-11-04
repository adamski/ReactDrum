package com.nodeaudio.reactdrum;

import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;

import android.media.AudioManager;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.uimanager.events.RCTEventEmitter;
import com.juce.JuceBridge;
import com.reactnativenavigation.NavigationApplication;
import com.reactnativenavigation.controllers.SplashActivity;

import java.lang.reflect.Array;
import java.util.ArrayList;

//==============================================================================
public class MainActivity   extends SplashActivity
{
    private JuceBridge juceBridge;

    public static native void attachOpenGLContext (String componentName);
    public static native String[] getSampleNames();
    public static native void selectSample (String sampleName);
    public static native void setBackgroundColour (String colour);
    public static native void setThumbnailForeground (String colour);
    public static native void setThumbnailBackground (String colour);

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        juceBridge = JuceBridge.getInstance();
        juceBridge.setActivityContext(this);
        juceBridge.setScreenSaver(true);

        setVolumeControlStream(AudioManager.STREAM_MUSIC);
        Log.d ("onCreate", "finished");
        String[] sampleNames = getSampleNames();
        for (int i=0; i<sampleNames.length; i++)
        {
            Log.d("test", sampleNames[i]);
        }

    }

    @Override
    public void onStart()
    {
        super.onStart();
        DisplayMetrics metrics = getResources().getDisplayMetrics();
        juceBridge.setScreenSize(metrics.widthPixels, metrics.heightPixels, metrics.densityDpi);
        juceBridge.callAppLauncher();
    }

    @Override
    public void onRequestPermissionsResult (int permissionID, String permissions[], int[] grantResults)
    {
        juceBridge.onRequestPermissionsResult (permissionID, permissions, grantResults);
    }
}
