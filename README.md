# ReactDrum
### Example project combining JUCE with React Native on iOS and Android

This project was written to accompany a talk presented at the ADC'16 conference.
It demonstrates using JUCE to create a custom view in a React Native app.

It uses React Native Navigation for navigation and MobX for state management. 

## Installation:

Install `podspec-generator`: `npm install -g podspec-generator`

`npm install`

`podspec-generator node_modules/react-native-navigation`

### For iOS:

`cd Builds/iOS`

`pod install`

You must then open the generated workspace project in Xcode. 

### For Android

Replace `node_modules/react-native-navigation/android/app/build.gradle` with https://gist.github.com/adamski/c4da6d390142ce5a6c0e95286c248922

### Run the packager 

The code in this repository was designed to showcase both iOS and Android "Hot Reloading" simultaneously. 
In order the achieve this I put the iOS version on port 8082. So for iOS, please start it like this:
```
npm run start-8082
```
and for Android open up another terminal session and:
```
npm start
```

Now you should be able to run both platforms with Hot Reloading!





