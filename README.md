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

### For Android

Replace `node_modules/react-native-navigation/android/app/build.gradle` with https://gist.github.com/adamski/c4da6d390142ce5a6c0e95286c248922








