package com.nodeaudio.reactdrum;

import android.support.annotation.Nullable;
import android.util.Log;
import android.view.ViewGroup;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.common.MapBuilder;
import com.facebook.react.modules.core.DeviceEventManagerModule;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.events.RCTEventEmitter;
import com.juce.JuceBridge;
import com.juce.JuceViewHolder;

import java.util.Map;

public class ReactJuceViewManager extends SimpleViewManager<JuceViewHolder> {

    public static final String REACT_CLASS = "ReactJuceView";
    private final ReactApplicationContext reactContext;

    public ReactJuceViewManager(final ReactApplicationContext reactContext) {
        super();
        this.reactContext = reactContext;

//        JuceBridge juceBridge = JuceBridge.getInstance();
//        juceBridge.onAppInitialised(new Runnable() {
//            @Override
//            public void run()
//            {
//                WritableMap event = Arguments.createMap();
//                Log.d ("test", "About to send event juceAppHasInitialised");
//                reactContext.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class).emit(
//                        "juceAppHasInitialised",
//                        event);
//                reactContext.getReactInstanceManager()
//                        .getDevSupportManager().handleReloadJS();
//            }
//        });
    }

    @Override
    public String getName() {
        return REACT_CLASS;
    }

    @Override
    protected ReactJuceView createViewInstance(ThemedReactContext themedReactContext) {
        JuceBridge juceBridge = JuceBridge.getInstance();
        juceBridge.setActivityContext(themedReactContext);

        ReactJuceView v = new ReactJuceView(themedReactContext);

        JuceBridge.ComponentPeerView componentPeerView = juceBridge.getPeerViewForComponent("MainComponent");
        if (componentPeerView != null) {

            Log.d ("ReactJuceViewManager", "Got componentPeerView");
            ViewGroup parent = (ViewGroup) componentPeerView.getParent();
            if (parent != null) {

                parent.removeView(componentPeerView);
            }
            v.addView(componentPeerView);
            Log.d( "ReactJuceViewManager", "About to attachOpenGlContext");
            MainActivity.attachOpenGLContext("MainComponent");
        }
        else
            Log.d("ReactJuceViewManager", "componentPeerView is null");

        return v;
    }
}