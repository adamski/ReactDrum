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
  View,
  ListView,
  TouchableHighlight,
  NativeModules
} from 'react-native';
import {Navigation} from 'react-native-navigation';

import DrumPlayer from './Components/DrumPlayer'

var ReactJuceModule = NativeModules.ReactJuceModule

class SampleListScreen extends Component {
  constructor() {
    super()
    this.getSampleNames()  
    this.state = {
      dataSource: null
    }
  }

  async getSampleNames() {
    const sampleNames = await ReactJuceModule.getSampleNames()
    console.log(sampleNames)

    const ds = new ListView.DataSource({rowHasChanged: (r1, r2) => r1 !== r2})
    this.setState({
      dataSource: ds.cloneWithRows(sampleNames),
    })
  }

  pressRow(sampleName) {
    ReactJuceModule.selectSample(sampleName)
    this.props.navigator.toggleDrawer({
      side: 'left',
      animated: true,
      to: 'closed'
    });
  }

  render() {
    if (this.state.dataSource !== null)
      return (
        <ListView
          dataSource={this.state.dataSource}
          renderRow={(rowData) => (
            <TouchableHighlight 
              onPress={() => this.pressRow(rowData)} 
              underlayColor="grey">
              <View style={styles.rowContainer}>
                <Text style={styles.title}>{rowData}</Text>
              </View>
            </TouchableHighlight>
          )}
          renderSeparator={(sectionID, rowID) => <View key={`${sectionID}-${rowID}`} style={styles.separator} />}
          style={styles.listView}
        />
      )
    else 
      return <Text>Fetching...</Text>
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

    Navigation.registerComponent('reactDrum.SampleListScreen', () => SampleListScreen)
    Navigation.registerComponent('reactDrum.DrumPlayer', () => DrumPlayer)

    Navigation.startSingleScreenApp({
      screen: {
        screen: 'reactDrum.DrumPlayer',
        title: 'JUCE + React Native'
      },
      drawer: { // optional, add this if you want a side menu drawer in your app
        left: { // optional, define if you want a drawer from the left
          screen: 'reactDrum.SampleListScreen' // unique ID registered with Navigation.registerScreen
        },
      }
    })


  }
}
