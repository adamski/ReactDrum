package com.nodeaudio.reactdrum;

import android.support.annotation.NonNull;

import com.facebook.react.ReactPackage;
import com.facebook.react.shell.MainReactPackage;
import com.juce.JuceBridge;
import com.reactnativenavigation.NavigationApplication;
import com.reactnativenavigation.bridge.NavigationReactPackage;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class MainApplication extends NavigationApplication {

//    @Override
//    public void onCreate() {
//        super.onCreate();
//        JuceBridge.getInstance().callAppLauncher();
//    }

    @Override
    public boolean isDebug() {
        // Make sure you are using BuildConfig from your own application
        return BuildConfig.DEBUG;
    }

    @NonNull
    @Override
    public List<ReactPackage> createAdditionalReactPackages() {
        // Add the packages you require here.
        // No need to add RnnPackage and MainReactPackage
        return Arrays.asList(
                (ReactPackage) new ReactDrumReactPackage()
        );
    }
}
