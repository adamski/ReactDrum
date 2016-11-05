import React, { Component, PropTypes } from 'react'
import { View, Text, Alert, StyleSheet, NativeModules, requireNativeComponent } from 'react-native'
import { observer } from 'mobx-react/native'
import ReactDrumStore from '../Store'

var styles = StyleSheet.create({
  container: {
    flex: 1,
  }
});

const ReactJuceView = requireNativeComponent('ReactJuceView', JuceComponent, {})

class JuceComponent extends React.Component {

  static propTypes = {
    ...View.propTypes
  }

  constructor(props) {
    super(props)
  }

  render() {
    return <ReactJuceView {...this.props} key="ReactJuceView" ref="ReactJuceView"/>
  }
}

@observer
class DrumPlayerScreen extends Component {
  static navigatorButtons = {
    leftButtons: [{
      icon: require('../../../images/navicon_menu.png'),
      id: 'menu'
    }],
    rightButtons: [
    {
      title: 'Edit',
      id: 'edit'
    },
    {
      icon: require('../../../images/navicon_add.png'),
      id: 'add'
    }
    ]
  }

  static navigatorStyle = {
    drawUnderNavBar: true,
    navBarBackgroundColor: '#4dbce9',
    navBarTextColor: '#ffff00',
    navBarSubtitleTextColor: '#ff0000',
    navBarButtonColor: '#ffffff',
    navigationBarColor: '#4dbce9', // for Android ...
    statusBarTextColorScheme: 'light',
    tabBarBackgroundColor: '#4dbce9',
    tabBarButtonColor: '#ffffff',
    tabBarSelectedButtonColor: '#ffff00'
  }

  constructor(props) {
    super(props);
    // if you want to listen on navigator events, set this up
    this.props.navigator.setOnNavigatorEvent(this.onNavigatorEvent.bind(this))
  }

  onNavigatorEvent(event) {
    if (event.id == 'add') {
      Alert.alert('NavBar', 'Add button pressed');
    } 
    if (event.id === 'menu') {
      this.props.navigator.toggleDrawer({
        side: 'left',
        animated: true
      })
    }
    if (event.id == 'edit') {

      this.props.navigator.push({
        title: "More",
        screen: "reactDrum.PushedScreen"
      });
    }
  }

  render() {
    return (
      <View style={styles.container}>
        <JuceComponent 
          style={{flex: 1}} 
          sampleName={ReactDrumStore.currentSample} 
          backgroundColour="ff000000"
          thumbnailForeground="ff4dbce9"
          thumbnailBackground="ff444444"
          key="JuceComponent"/>
      </View>
    )
  }
}

module.exports = DrumPlayerScreen

