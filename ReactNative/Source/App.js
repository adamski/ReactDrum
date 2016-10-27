/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 * @flow
 */

import React, { Component } from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View
} from 'react-native';
import {Navigation} from 'react-native-navigation';

import DrumPlayer from './Components/DrumPlayer'

class MainScreen extends Component {
  render() {
    return (
      <View style={styles.container}>
        <Text style={styles.welcome}>
          Welcome to React Native!
        </Text>
        <Text style={styles.instructions}>
          This is where our JUCE Component will go! 
        </Text>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
});


// notice that this is just a simple class, it's not a React component
export default class App {
  constructor() {

    Navigation.registerComponent('reactDrum.MainScreen', () => MainScreen)
    Navigation.registerComponent('reactDrum.DrumPlayer', () => DrumPlayer)

    // setTimeout(() => {
      Navigation.startSingleScreenApp({
        screen: {
          screen: 'reactDrum.DrumPlayer',
          title: 'JUCE + React Native'
        }
      })
    // }, 1000) 

  }
}
